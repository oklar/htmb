#ifndef HTMB_H
#define HTMB_H

#include <stdio.h>
#include <ctype.h>
#include <string.h>
#include <stdlib.h>
#include <stddef.h>

/*— argument-counting macro —*/
#define _ARG_N( \
     _1,  _2,  _3,  _4,  _5,  _6,  _7,  _8, \
     _9, _10, _11, _12, _13, _14, _15, _16, _17, _18, _19, _20, N, ...) N
#define _RSEQ_N() 20,19,18,17,16,15,14,13,12,11,10,9,8,7,6,5,4,3,2,1,0
#define PP_NARG_(...) _ARG_N(__VA_ARGS__)
#define PP_NARG(...)  PP_NARG_(__VA_ARGS__, _RSEQ_N())

typedef struct { const char **a; size_t n; } attr_list_t;
#define ATTRS(...)  ((attr_list_t){ (const char*[]){ __VA_ARGS__ }, PP_NARG(__VA_ARGS__) })

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


#define A(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("a", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define AAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("a", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Abbr(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("abbr", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define AbbrAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("abbr", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Address(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("address", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define AddressAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("address", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Article(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("article", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ArticleAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("article", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Aside(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("aside", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define AsideAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("aside", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Audio(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("audio", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define AudioAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("audio", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define B(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("b", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define BAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("b", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Bdi(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("bdi", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define BdiAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("bdi", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Bdo(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("bdo", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define BdoAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("bdo", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Blockquote(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("blockquote", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define BlockquoteAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("blockquote", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Body(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("body", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define BodyAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("body", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Button(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("button", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ButtonAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("button", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Canvas(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("canvas", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define CanvasAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("canvas", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Caption(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("caption", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define CaptionAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("caption", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Cite(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("cite", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define CiteAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("cite", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Code(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("code", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define CodeAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("code", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Colgroup(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("colgroup", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ColgroupAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("colgroup", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Data(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("data", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DataAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("data", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Datalist(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("datalist", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DatalistAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("datalist", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Dd(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("dd", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DdAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("dd", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Del(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("del", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DelAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("del", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Details(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("details", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DetailsAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("details", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Dfn(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("dfn", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DfnAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("dfn", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Dialog(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("dialog", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DialogAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("dialog", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Div(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("div", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DivAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("div", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Dl(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("dl", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DlAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("dl", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Dt(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("dt", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define DtAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("dt", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Em(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("em", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define EmAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("em", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Fieldset(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("fieldset", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define FieldsetAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("fieldset", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Figcaption(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("figcaption", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define FigcaptionAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("figcaption", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Figure(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("figure", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define FigureAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("figure", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Footer(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("footer", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define FooterAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("footer", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Form(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("form", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define FormAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("form", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define H1(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("h1", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define H1Attr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("h1", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Head(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("head", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define HeadAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("head", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Header(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("header", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define HeaderAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("header", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Hgroup(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("hgroup", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define HgroupAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("hgroup", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Html(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("html", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define HtmlAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("html", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define I(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("i", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define IAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("i", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Ins(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("ins", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define InsAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("ins", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Kbd(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("kbd", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define KbdAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("kbd", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Label(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("label", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define LabelAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("label", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Legend(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("legend", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define LegendAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("legend", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Li(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("li", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define LiAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("li", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Main(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("main", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define MainAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("main", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Map(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("map", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define MapAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("map", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Mark(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("mark", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define MarkAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("mark", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Menu(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("menu", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define MenuAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("menu", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Meter(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("meter", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define MeterAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("meter", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Nav(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("nav", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define NavAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("nav", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Noscript(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("noscript", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define NoscriptAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("noscript", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Object(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("object", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ObjectAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("object", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Ol(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("ol", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define OlAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("ol", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Optgroup(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("optgroup", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define OptgroupAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("optgroup", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Option(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("option", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define OptionAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("option", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Output(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("output", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define OutputAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("output", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define P(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("p", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define PAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("p", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Picture(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("picture", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define PictureAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("picture", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Pre(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("pre", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define PreAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("pre", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Progress(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("progress", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ProgressAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("progress", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Q(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("q", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define QAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("q", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Rp(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("rp", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define RpAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("rp", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Rt(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("rt", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define RtAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("rt", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Ruby(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("ruby", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define RubyAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("ruby", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define S(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("s", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("s", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Samp(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("samp", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SampAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("samp", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Script(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("script", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ScriptAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("script", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Search(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("search", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SearchAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("search", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Section(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("section", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SectionAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("section", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Select(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("select", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SelectAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("select", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Slot(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("slot", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SlotAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("slot", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Small(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("small", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SmallAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("small", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Span(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("span", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SpanAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("span", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Strong(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("strong", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define StrongAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("strong", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Style(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("style", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define StyleAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("style", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Sub(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("sub", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SubAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("sub", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Summary(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("summary", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SummaryAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("summary", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Sup(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("sup", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define SupAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("sup", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Table(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("table", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TableAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("table", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Tbody(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("tbody", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TbodyAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("tbody", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Td(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("td", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TdAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("td", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Textarea(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("textarea", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TextareaAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("textarea", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Tfoot(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("tfoot", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TfootAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("tfoot", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Th(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("th", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define ThAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("th", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Thead(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("thead", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TheadAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("thead", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Time(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("time", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TimeAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("time", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Title(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("title", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TitleAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("title", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Tr(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("tr", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TrAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("tr", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define U(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("u", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define UAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("u", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Ul(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("ul", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define UlAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("ul", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Var(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("var", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define VarAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("var", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Video(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("video", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define VideoAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("video", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define H2(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("h2", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define H2Attr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("h2", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define H3(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("h3", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define H3Attr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("h3", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define H4(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("h4", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define H4Attr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("h4", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define H5(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("h5", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define H5Attr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("h5", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define H6(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("h6", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define H6Attr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("h6", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Iframe(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("iframe", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define IframeAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("iframe", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
#define Template(...) ({ const char *kids[] = { __VA_ARGS__ }; make_tag("template", NULL, 0, kids, PP_NARG(__VA_ARGS__)); })
#define TemplateAttr(ATTRS_LIST, ...) ({ attr_list_t al = ATTRS ATTRS_LIST; const char *kids[] = { __VA_ARGS__ }; make_tag("template", al.a, al.n, kids, PP_NARG(__VA_ARGS__)); })
/* Void tags (self-closing) */
#define Area() make_void_tag("area", NULL, 0)
#define AreaAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("area", al.a, al.n); })
#define Base() make_void_tag("base", NULL, 0)
#define BaseAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("base", al.a, al.n); })
#define Br() make_void_tag("br", NULL, 0)
#define BrAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("br", al.a, al.n); })
#define Col() make_void_tag("col", NULL, 0)
#define ColAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("col", al.a, al.n); })
#define Embed() make_void_tag("embed", NULL, 0)
#define EmbedAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("embed", al.a, al.n); })
#define Hr() make_void_tag("hr", NULL, 0)
#define HrAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("hr", al.a, al.n); })
#define Img() make_void_tag("img", NULL, 0)
#define ImgAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("img", al.a, al.n); })
#define Input() make_void_tag("input", NULL, 0)
#define InputAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("input", al.a, al.n); })
#define Link() make_void_tag("link", NULL, 0)
#define LinkAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("link", al.a, al.n); })
#define Meta() make_void_tag("meta", NULL, 0)
#define MetaAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("meta", al.a, al.n); })
#define Source() make_void_tag("source", NULL, 0)
#define SourceAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("source", al.a, al.n); })
#define Track() make_void_tag("track", NULL, 0)
#define TrackAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("track", al.a, al.n); })
#define Wbr() make_void_tag("wbr", NULL, 0)
#define WbrAttr(ATTRS_LIST) ({ attr_list_t al = ATTRS ATTRS_LIST; make_void_tag("wbr", al.a, al.n); })

#endif // HTMB_H