# HTMB for C - Hypertext Markup Builder

A minimalistic C library for building HTML structures using pure functions.

```c
#include "htmb.b"

int main(void)
{
  char *test =
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

  puts(test);
  free(test);
}
```
