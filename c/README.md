# HTMB for C - Hypertext Markup Builder

A minimalistic C library for building HTML structures using pure functions.

For embedded via PlatformIO Project Configuration File you may include it i.e:
```md
[env:esp12e]
...
lib_deps =
    https://github.com/oklar/htmb.git
...
```
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

```html
<body>
  <header>
    <h1>Welcome to my page</h1>
    <p>This is a simple demo using standard and void HTML tags.</p>
    <hr />
  </header>
  <main>
    <section>
      <h2>Form Elements</h2>
      <form>
        <label form="name">Name:</label
        ><input type="text" id="name" name="name" /><br /><br /><label
          form="email"
          >Email:</label
        ><input type="email" id="email" name="email" /><br /><br /><input
          type="submit"
          value="Submit"
        />
      </form>
    </section>
  </main>
</body>
```
