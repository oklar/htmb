# HTMB for C - Hypertext Markup Builder

A minimalistic C library for building HTML structures using pure functions.

For embedded via PlatformIO Project Configuration File you may include it i.e:
```ini
[env:esp12e]
...
lib_deps =
    https://github.com/oklar/htmb.git#c-v2.0.1
...
```

Pin a tag like `#c-v2.0.1` so a change on `main` can't change your build. `c-v1.0.0` is the older version that used `malloc` and `free()`. [examples/platformio](examples/platformio) is a complete ESP-12E project, and CI builds it with the real ESP8266 toolchain.

It's a single header that works in C and C++, including Arduino sketches, with GCC or Clang. The tag macros use `({ ... })` statement expressions, which MSVC doesn't support.
```c
#include "htmb.h"

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

  if (test)
    puts(test);
  htmb_reset(); /* frees every string built above */
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

## Memory

HTMB never calls `malloc`. Every tag is built in one fixed buffer (the arena), and `htmb_reset()` frees all of it at once, for example after sending each response. Don't call `free()` on HTMB strings.

The arena keeps every nested tag until the reset, not just the final page, so it needs a few times the page's length: the example above is 402 characters and uses 1,623 bytes. The default is 4096 bytes. If a page doesn't fit, the outermost tag returns `NULL`, and `htmb_used()` tells you how many bytes a page took. To change the size, define it before including the header or pass a build flag:

```c
#define HTMB_ARENA_SIZE 8192
#include "htmb.h"
```

```ini
[env:esp12e]
build_flags = -DHTMB_ARENA_SIZE=8192
```

Each source file that includes `htmb.h` gets its own arena, and the arena isn't thread-safe.

## Escaping

Text goes into the HTML as is, so a string like `<script>` in a child becomes a real tag. Wrap anything that didn't come from your own code, such as form input or a query string, in `htmb_escape()`. It replaces `&`, `<`, `>`, `"` and `'` with entities:

```c
char *html = P("Hello, ", htmb_escape(name));
```

The escaped copy lives in the arena like every other string.

## Changing the tags

The tag macros at the bottom of `htmb.h` are generated from `documentation/html.json`. See [documentation/readme.md](../documentation/readme.md) for how to regenerate them.
