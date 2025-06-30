#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stddef.h>

static const char *normal_tags[] = {
   "a", "abbr", "address", "article", "aside", "audio", "b", "bdi", "bdo", "blockquote", "body", "button", "canvas", "caption", "cite", "code", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "div", "dl", "dt", "em", "fieldset", "figcaption", "figure", "footer", "form", "h1", "head", "header", "hgroup", "html", "i", "ins", "kbd", "label", "legend", "li", "main", "map", "mark", "menu", "meter", "nav", "noscript", "object", "ol", "optgroup", "option", "output", "p", "picture", "pre", "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "search", "section", "select", "slot", "small", "span", "strong", "style", "sub", "summary", "sup", "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "u", "ul", "var", "video",
   "h2", "h3", "h4", "h5", "h6", "iframe", "template"
};
static const size_t n_normal = sizeof normal_tags / sizeof *normal_tags;

static const char *void_tags[] = {
    "area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "source", "track", "wbr"
};
// For tags that are listed as empty but can have children: ("iframe", "template")


static const size_t n_void = sizeof void_tags / sizeof *void_tags;

void capitalize(const char *tag, char *out) {
    out[0] = toupper((unsigned char)tag[0]);
    for (size_t i = 1; tag[i]; ++i) out[i] = tag[i];
    out[strlen(tag)] = '\0';
}

int main(void) {
    printf("#ifndef HTMB_H\n");
    printf("#define HTMB_H\n");

    /* Normal (container) tags */
    for (size_t i = 0; i < n_normal; i++) {
        const char *tag = normal_tags[i];
        char cap[32];
        capitalize(tag, cap);

        // no-attr macro
        printf("#define %s(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag(\"%s\", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })\n", cap, tag);
        // attr macro
        char capAttr[32];
        snprintf(capAttr, sizeof capAttr, "%sAttr", cap);
        printf("#define %s(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag(\"%s\", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })\n", capAttr, tag);
    }

    /* Void (self-closing) tags */
    printf("/* Void tags (self-closing) */\n");
    for (size_t i = 0; i < n_void; i++) {
        const char *tag = void_tags[i];
        char cap[32];
        capitalize(tag, cap);

        // no-attr void
        printf("#define %s() make_void_tag(\"%s\", NULL, 0)\n", cap, tag);

        // attr void
        char capAttr[32];
        snprintf(capAttr, sizeof capAttr, "%sAttr", cap);
        printf("#define %s(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag(\"%s\", al.a, al.n); })\n", capAttr, tag);
    }

    printf("#endif // HTMB_H\n");
    return 0;
}