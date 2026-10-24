/* Tests for htmb.h; exits non-zero if any check fails. */
#include "htmb.h"

static int failures;

static void
expect(const char *name, char *got, const char *want)
{
    if (got && strcmp(got, want) == 0) {
        printf("ok   %s\n", name);
    } else {
        printf("FAIL %s\n     got:  %s\n     want: %s\n", name, got ? got : "(null)", want);
        failures++;
    }
    htmb_reset();
}

static void
check(const char *name, int ok)
{
    printf(ok ? "ok   %s\n" : "FAIL %s\n", name);
    if (!ok) failures++;
}

static char *
page(void)
{
    return
    Body(
      Header(
        H1("Welcome to my page"),
        P("This is a simple demo using standard and void HTML tags."),
        Hr()
      ),
      Main(
        Section(
          H2("Form Elements"),
          Form(
            LabelAttr(("form=name"), "Name:"),
            InputAttr(("type=text", "id=name", "name=name")),
            Br(),
            Br(),
            LabelAttr(("form=email"), "Email:"),
            InputAttr(("type=email", "id=email", "name=email")),
            Br(),
            Br(),
            InputAttr(("type=submit", "value=Submit"))
          )
        )
      )
    );
}

int main(void)
{
    /*— output —*/
    expect("text child", Div("hello"), "<div>hello</div>");
    expect("empty text child", Div(""), "<div></div>");
    expect("several children", Div("a", "b", "c"), "<div>abc</div>");
    expect("NULL child is skipped", Div(NULL, "after"), "<div>after</div>");
    expect("nesting", Ul(Li("one"), Li(A("two"))), "<ul><li>one</li><li><a>two</a></li></ul>");
    expect("attributes", DivAttr(("id=main", "class=card"), "x"), "<div id=\"main\" class=\"card\">x</div>");
    expect("single-quoted value", DivAttr(("class='card big'"), "x"), "<div class=\"card big\">x</div>");
    expect("bare attribute", ButtonAttr(("disabled", "type=button"), "Go"), "<button disabled type=\"button\">Go</button>");
    expect("void tag", Br(), "<br/>");
    expect("void tag with attributes", ImgAttr(("src=a.png", "alt='a cat'")), "<img src=\"a.png\" alt=\"a cat\"/>");
    expect("README page", page(),
        "<body><header><h1>Welcome to my page</h1>"
        "<p>This is a simple demo using standard and void HTML tags.</p><hr/></header>"
        "<main><section><h2>Form Elements</h2><form>"
        "<label form=\"name\">Name:</label><input type=\"text\" id=\"name\" name=\"name\"/><br/><br/>"
        "<label form=\"email\">Email:</label><input type=\"email\" id=\"email\" name=\"email\"/><br/><br/>"
        "<input type=\"submit\" value=\"Submit\"/>"
        "</form></section></main></body>");

    /*— arena —*/
    check("arena starts empty", htmb_used() == 0);

    page();
    size_t used = htmb_used();
    check("building uses the arena", used > 0);
    htmb_reset();
    check("reset empties the arena", htmb_used() == 0);

    page();
    check("same page uses the same bytes after reset", htmb_used() == used);
    htmb_reset();

    int built = 0;
    while (built < HTMB_ARENA_SIZE && page() != NULL)
        built++;
    check("full arena returns NULL", built < HTMB_ARENA_SIZE);
    htmb_reset();

    /* the child can't fit; its parent must not come back without it */
    static char big[HTMB_ARENA_SIZE];
    memset(big, 'x', sizeof big - 1);
    check("a child that doesn't fit makes its parent NULL", Div(P(big)) == NULL);
    htmb_reset();
    expect("arena works again after reset", Div("ok"), "<div>ok</div>");

    printf(failures ? "%d failed\n" : "all passed\n", failures);
    return failures != 0;
}
