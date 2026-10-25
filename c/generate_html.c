/* Regenerates the tag macros in htmb.h from documentation/html.json:
 *
 *   gcc c/generate_html.c -o generate_html
 *   ./generate_html documentation/html.json c/include/htmb.h
 *
 * Only the lines between the two marker comments in htmb.h are rewritten.
 */
#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

#define MAX_TAGS    256
#define MAX_TAG_LEN 32

static const char *begin_marker = "tags below are generated";
static const char *end_marker   = "end of generated tags";

static void
fail(const char *what, const char *path)
{
    fprintf(stderr, "generate_html: %s: %s\n", path, what);
    exit(1);
}

static char *
read_file(const char *path)
{
    FILE *f = fopen(path, "rb");
    if (!f) fail("can't open", path);
    fseek(f, 0, SEEK_END);
    long n = ftell(f);
    rewind(f);
    char *buf = (char *)malloc(n + 1);
    if (!buf || fread(buf, 1, n, f) != (size_t)n) fail("can't read", path);
    buf[n] = '\0';
    fclose(f);
    return buf;
}

/* Reads the string array that follows "key" in json, e.g. "tags": ["a", "b"]. */
static size_t
read_list(const char *json, const char *path, const char *key, char out[][MAX_TAG_LEN])
{
    char quoted[64];
    snprintf(quoted, sizeof quoted, "\"%s\"", key);
    const char *p = strstr(json, quoted);
    if (!p || !(p = strchr(p, '['))) fail("missing tag list", path);

    size_t n = 0;
    for (p++; *p && *p != ']'; p++) {
        if (*p != '"') continue;
        const char *end = strchr(p + 1, '"');
        if (!end || end - p - 1 >= MAX_TAG_LEN || n == MAX_TAGS) fail("bad tag list", path);
        memcpy(out[n], p + 1, end - p - 1);
        out[n][end - p - 1] = '\0';
        n++;
        p = end;
    }
    return n;
}

static void
capitalize(const char *tag, char *out)
{
    strcpy(out, tag);
    out[0] = toupper((unsigned char)out[0]);
}

int main(int argc, char **argv)
{
    if (argc != 3) {
        fprintf(stderr, "usage: %s documentation/html.json c/include/htmb.h\n", argv[0]);
        return 2;
    }
    const char *json_path = argv[1], *header_path = argv[2];

    static char tags[MAX_TAGS][MAX_TAG_LEN], void_tags[MAX_TAGS][MAX_TAG_LEN];
    char *json = read_file(json_path);
    size_t n_tags = read_list(json, json_path, "tags", tags);
    size_t n_void = read_list(json, json_path, "tagsVoid", void_tags);

    /*— keep everything outside the markers —*/
    char *header = read_file(header_path);
    char *begin = strstr(header, begin_marker);
    char *end = strstr(header, end_marker);
    if (!begin || !end || end < begin) fail("missing generated-tags markers", header_path);
    begin = strchr(begin, '\n');
    if (!begin) fail("missing generated-tags markers", header_path);
    begin++;
    while (end > begin && end[-1] != '\n') end--;

    FILE *out = fopen(header_path, "wb");
    if (!out) fail("can't write", header_path);
    fwrite(header, 1, begin - header, out);

    /* keep the header's own line endings */
    const char *nl = strstr(header, "\r\n") ? "\r\n" : "\n";

    char cap[MAX_TAG_LEN];
    for (size_t i = 0; i < n_tags; i++) {
        capitalize(tags[i], cap);
        fprintf(out, "#define %s(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; "
                     "make_tag(\"%s\", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })%s",
                cap, tags[i], nl);
        fprintf(out, "#define %sAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; "
                     "const char *htmb_k_[] = { NULL, __VA_ARGS__ }; "
                     "make_tag(\"%s\", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })%s",
                cap, tags[i], nl);
    }

    fprintf(out, "/* Void tags (self-closing) */%s", nl);
    for (size_t i = 0; i < n_void; i++) {
        capitalize(void_tags[i], cap);
        fprintf(out, "#define %s() make_void_tag(\"%s\", NULL, 0)%s", cap, void_tags[i], nl);
        fprintf(out, "#define %sAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; "
                     "make_void_tag(\"%s\", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })%s",
                cap, void_tags[i], nl);
    }

    fputs(end, out);
    fclose(out);
    printf("%s: %lu tags, %lu void tags\n", header_path, (unsigned long)n_tags, (unsigned long)n_void);
    return 0;
}
