# HTMB - Hypertext Markup Builder

A minimalistic library for building HTML structures using pure functions. HTMB provides a clean, simple API for generating HTML for as many programming languages as possible.


## Implementations

HTMB is available in multiple languages:

- [C](c/)
- [C#](cs/HtmbLibrary/)
- [JavaScript](js/)
- [...?](https://github.com/oklar/htmb/pulls)

## Core Concept

HTMB uses a functional approach to HTML generation, representing elements as function calls:

```
// Pseudocode example
div(
  h1("Hello World"),
  p("Welcome to HTMB")
)
```

This produces HTML like:

```html
<div>
  <h1>Hello World</h1>
  <p>Welcome to HTMB</p>
</div>
```

## License

MIT
