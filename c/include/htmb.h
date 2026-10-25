#ifndef HTMB_H
#define HTMB_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/*— tag macros put a NULL first in each list, so an empty list is still a valid array —*/
#define HTMB_UNPAREN(...) __VA_ARGS__
#define HTMB_COUNT(a) (sizeof (a) / sizeof *(a))

/*— arena: every string built lives here until htmb_reset() —*/
#ifndef HTMB_ARENA_SIZE
#define HTMB_ARENA_SIZE 4096
#endif

static char   htmb_arena[HTMB_ARENA_SIZE];
static size_t htmb_arena_used;
static int    htmb_arena_full;

/* Releases every string built since the last reset. */
static inline void htmb_reset(void)
{
    htmb_arena_used = 0;
    htmb_arena_full = 0;
}

/* Bytes in use, for picking HTMB_ARENA_SIZE. */
static inline size_t htmb_used(void)
{
    return htmb_arena_used;
}

static char *
htmb_alloc(size_t n)
{
    /* stays full until reset, so the outermost tag returns NULL too */
    if (htmb_arena_full || n > HTMB_ARENA_SIZE - htmb_arena_used) {
        htmb_arena_full = 1;
        return NULL;
    }
    char *p = htmb_arena + htmb_arena_used;
    htmb_arena_used += n;
    return p;
}

/* Copies text with & < > " ' replaced by entities, so it can't be read as markup. */
static inline char *
htmb_escape(const char *text)
{
    if (!text) return NULL;

    size_t n = 1;
    for (const char *c = text; *c; c++) {
        switch (*c) {
        case '&':  n += 5; break;  /* &amp;  */
        case '<':  n += 4; break;  /* &lt;   */
        case '>':  n += 4; break;  /* &gt;   */
        case '"':  n += 6; break;  /* &quot; */
        case '\'': n += 5; break;  /* &#39;  */
        default:   n += 1;
        }
    }

    char *out = htmb_alloc(n);
    if (!out) return NULL;

    char *p = out;
    for (const char *c = text; *c; c++) {
        const char *entity = NULL;
        switch (*c) {
        case '&':  entity = "&amp;";  break;
        case '<':  entity = "&lt;";   break;
        case '>':  entity = "&gt;";   break;
        case '"':  entity = "&quot;"; break;
        case '\'': entity = "&#39;";  break;
        }
        if (entity) {
            size_t len = strlen(entity);
            memcpy(p, entity, len);
            p += len;
        } else {
            *p++ = *c;
        }
    }
    *p = '\0';
    return out;
}

/*— attrs: name=value becomes name="value", outer single-quotes stripped —*/
static size_t
attrs_len(const char **attrs, size_t attr_count)
{
    size_t alen = 0;
    for (size_t i = 0; i < attr_count; i++) {
        const char *s = attrs[i];
        const char *eq = strchr(s, '=');
        if (eq) {
            const char *val = eq + 1;
            size_t vlen = strlen(val);
            if (vlen >= 2 && val[0] == '\'' && val[vlen-1] == '\'')
                vlen -= 2;
            alen += (eq - s) + 3 + vlen;  /* name + ="" + stripped */
        } else {
            alen += strlen(s);
        }
        if (i + 1 < attr_count) alen += 1;  /* space */
    }
    return alen;
}

static char *
attrs_write(char *p, const char **attrs, size_t attr_count)
{
    for (size_t i = 0; i < attr_count; i++) {
        const char *s = attrs[i];
        const char *eq = strchr(s, '=');
        if (eq) {
            memcpy(p, s, eq - s);
            p += eq - s;
            *p++ = '=';
            *p++ = '"';

            const char *val = eq + 1;
            size_t vlen = strlen(val);
            if (vlen >= 2 && val[0] == '\'' && val[vlen-1] == '\'') {
                val += 1;
                vlen -= 2;
            }
            memcpy(p, val, vlen);
            p += vlen;
            *p++ = '"';
        } else {
            size_t n = strlen(s);
            memcpy(p, s, n);
            p += n;
        }
        if (i + 1 < attr_count) *p++ = ' ';
    }
    return p;
}

static char *
make_tag(const char *tag,
         const char **attrs, size_t attr_count,
         const char **kids,  size_t kid_count)
{
    size_t tlen = strlen(tag);
    size_t alen = attrs_len(attrs, attr_count);
    size_t clen = 0;
    for (size_t i = 0; i < kid_count; i++)
        if (kids[i]) clen += strlen(kids[i]);

    /* '<' + tag + (space+attrs?) + '>' + content + "</" + tag + '>' + NUL */
    char *out = htmb_alloc(1 + tlen + (alen ? 1 + alen : 0) + 1 + clen + 2 + tlen + 1 + 1);
    if (!out) return NULL;

    char *p = out;
    *p++ = '<';
    memcpy(p, tag, tlen);
    p += tlen;
    if (alen) {
        *p++ = ' ';
        p = attrs_write(p, attrs, attr_count);
    }
    *p++ = '>';

    for (size_t i = 0; i < kid_count; i++) {
        if (!kids[i]) continue;
        size_t n = strlen(kids[i]);
        memcpy(p, kids[i], n);
        p += n;
    }

    *p++ = '<';
    *p++ = '/';
    memcpy(p, tag, tlen);
    p += tlen;
    *p++ = '>';
    *p = '\0';
    return out;
}

static char *
make_void_tag(const char *tag,
              const char **attrs, size_t attr_count)
{
    size_t tlen = strlen(tag);
    size_t alen = attrs_len(attrs, attr_count);

    /* '<' + tag + (space+attrs?) + "/>" + NUL, e.g. <img src="x"/> */
    char *out = htmb_alloc(1 + tlen + (alen ? 1 + alen : 0) + 2 + 1);
    if (!out) return NULL;

    char *p = out;
    *p++ = '<';
    memcpy(p, tag, tlen);
    p += tlen;
    if (alen) {
        *p++ = ' ';
        p = attrs_write(p, attrs, attr_count);
    }
    *p++ = '/';
    *p++ = '>';
    *p = '\0';
    return out;
}

/*— tags below are generated by c/generate_html.c from documentation/html.json —*/
#define A(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("a", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define AAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("a", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Abbr(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("abbr", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define AbbrAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("abbr", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Address(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("address", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define AddressAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("address", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Article(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("article", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ArticleAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("article", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Aside(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("aside", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define AsideAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("aside", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Audio(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("audio", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define AudioAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("audio", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define B(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("b", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define BAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("b", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Bdi(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("bdi", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define BdiAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("bdi", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Bdo(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("bdo", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define BdoAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("bdo", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Blockquote(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("blockquote", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define BlockquoteAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("blockquote", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Body(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("body", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define BodyAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("body", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Button(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("button", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ButtonAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("button", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Canvas(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("canvas", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define CanvasAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("canvas", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Caption(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("caption", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define CaptionAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("caption", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Cite(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("cite", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define CiteAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("cite", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Code(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("code", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define CodeAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("code", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Colgroup(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("colgroup", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ColgroupAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("colgroup", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Data(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("data", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DataAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("data", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Datalist(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("datalist", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DatalistAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("datalist", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Dd(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dd", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DdAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dd", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Del(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("del", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DelAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("del", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Details(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("details", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DetailsAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("details", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Dfn(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dfn", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DfnAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dfn", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Dialog(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dialog", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DialogAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dialog", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Div(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("div", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DivAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("div", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Dl(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dl", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DlAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dl", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Dt(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dt", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define DtAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("dt", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Em(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("em", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define EmAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("em", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Fieldset(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("fieldset", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define FieldsetAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("fieldset", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Figcaption(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("figcaption", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define FigcaptionAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("figcaption", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Figure(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("figure", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define FigureAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("figure", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Footer(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("footer", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define FooterAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("footer", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Form(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("form", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define FormAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("form", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H1(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h1", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H1Attr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h1", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Head(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("head", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define HeadAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("head", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Header(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("header", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define HeaderAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("header", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Hgroup(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("hgroup", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define HgroupAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("hgroup", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Html(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("html", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define HtmlAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("html", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define I(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("i", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define IAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("i", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Ins(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ins", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define InsAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ins", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Kbd(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("kbd", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define KbdAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("kbd", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Label(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("label", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define LabelAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("label", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Legend(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("legend", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define LegendAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("legend", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Li(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("li", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define LiAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("li", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Main(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("main", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define MainAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("main", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Map(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("map", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define MapAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("map", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Mark(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("mark", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define MarkAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("mark", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Menu(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("menu", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define MenuAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("menu", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Meter(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("meter", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define MeterAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("meter", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Nav(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("nav", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define NavAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("nav", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Noscript(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("noscript", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define NoscriptAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("noscript", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Object(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("object", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ObjectAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("object", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Ol(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ol", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define OlAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ol", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Optgroup(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("optgroup", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define OptgroupAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("optgroup", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Option(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("option", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define OptionAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("option", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Output(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("output", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define OutputAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("output", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define P(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("p", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define PAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("p", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Picture(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("picture", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define PictureAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("picture", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Pre(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("pre", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define PreAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("pre", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Progress(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("progress", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ProgressAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("progress", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Q(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("q", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define QAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("q", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Rp(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("rp", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define RpAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("rp", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Rt(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("rt", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define RtAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("rt", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Ruby(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ruby", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define RubyAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ruby", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define S(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("s", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("s", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Samp(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("samp", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SampAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("samp", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Script(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("script", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ScriptAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("script", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Search(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("search", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SearchAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("search", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Section(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("section", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SectionAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("section", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Select(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("select", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SelectAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("select", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Slot(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("slot", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SlotAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("slot", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Small(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("small", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SmallAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("small", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Span(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("span", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SpanAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("span", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Strong(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("strong", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define StrongAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("strong", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Style(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("style", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define StyleAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("style", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Sub(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("sub", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SubAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("sub", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Summary(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("summary", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SummaryAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("summary", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Sup(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("sup", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define SupAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("sup", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Table(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("table", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TableAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("table", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Tbody(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("tbody", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TbodyAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("tbody", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Td(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("td", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TdAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("td", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Textarea(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("textarea", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TextareaAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("textarea", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Tfoot(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("tfoot", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TfootAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("tfoot", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Th(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("th", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define ThAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("th", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Thead(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("thead", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TheadAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("thead", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Time(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("time", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TimeAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("time", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Title(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("title", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TitleAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("title", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Tr(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("tr", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TrAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("tr", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define U(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("u", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define UAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("u", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Ul(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ul", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define UlAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("ul", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Var(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("var", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define VarAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("var", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Video(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("video", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define VideoAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("video", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H2(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h2", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H2Attr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h2", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H3(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h3", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H3Attr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h3", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H4(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h4", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H4Attr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h4", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H5(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h5", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H5Attr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h5", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H6(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h6", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define H6Attr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("h6", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Iframe(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("iframe", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define IframeAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("iframe", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define Template(...) ({ const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("template", NULL, 0, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
#define TemplateAttr(ATTRS_LIST, ...) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; const char *htmb_k_[] = { NULL, __VA_ARGS__ }; make_tag("template", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1, htmb_k_ + 1, HTMB_COUNT(htmb_k_) - 1); })
/* Void tags (self-closing) */
#define Area() make_void_tag("area", NULL, 0)
#define AreaAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("area", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Base() make_void_tag("base", NULL, 0)
#define BaseAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("base", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Br() make_void_tag("br", NULL, 0)
#define BrAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("br", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Col() make_void_tag("col", NULL, 0)
#define ColAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("col", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Embed() make_void_tag("embed", NULL, 0)
#define EmbedAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("embed", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Hr() make_void_tag("hr", NULL, 0)
#define HrAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("hr", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Img() make_void_tag("img", NULL, 0)
#define ImgAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("img", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Input() make_void_tag("input", NULL, 0)
#define InputAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("input", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Link() make_void_tag("link", NULL, 0)
#define LinkAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("link", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Meta() make_void_tag("meta", NULL, 0)
#define MetaAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("meta", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Source() make_void_tag("source", NULL, 0)
#define SourceAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("source", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Track() make_void_tag("track", NULL, 0)
#define TrackAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("track", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
#define Wbr() make_void_tag("wbr", NULL, 0)
#define WbrAttr(ATTRS_LIST) ({ const char *htmb_a_[] = { NULL, HTMB_UNPAREN ATTRS_LIST }; make_void_tag("wbr", htmb_a_ + 1, HTMB_COUNT(htmb_a_) - 1); })
/*— end of generated tags —*/

#endif // HTMB_H
