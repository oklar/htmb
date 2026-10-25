# HTMB - Hypertext Markup Builder

A lightweight JavaScript library for building HTML structures using functions.

## Installation

```bash
npm install htmb
```

## Usage

### Node.js

```javascript
const { div, h1, p } = require("htmb");

// Basic elements
div({ class: "container" }, h1("Hello World"), p("Welcome to HTMB"));
// -> '<div class="container"><h1>Hello World</h1><p>Welcome to HTMB</p></div>'
```

### Browser

```html
<script src="htmb.umd.js"></script>
<script>
  const { div, h1, p } = htmb;

  document.body.innerHTML = div(
    { class: "container" },
    h1("Hello World"),
    p("Welcome to HTMB")
  );
</script>
```

## Core Features

### Elements

```javascript
// Basic element
div("Hello");
// -> '<div>Hello</div>'

// With attributes
div({ class: "container", id: "main" }, "Hello");
// -> '<div class="container" id="main">Hello</div>'

// Boolean attributes
input({ disabled: true });
// -> '<input disabled/>'

// Nested elements
div({ class: "card" }, h2("Title"), p("Content"));
// -> '<div class="card"><h2>Title</h2><p>Content</p></div>'
```

### Escaping

Children go into the HTML as is, so a string like `<script>` becomes a real tag. Attribute values only have `"` escaped. Wrap anything that didn't come from your own code, such as form input or a query string, in `escape()`. It replaces `&`, `<`, `>`, `"` and `'` with entities:

```javascript
const { p, escape } = require("htmb");

p("Hello, ", escape(name));
// name = "<b>Bob</b>" -> '<p>Hello, &lt;b&gt;Bob&lt;/b&gt;</p>'
```

## API

### Element Functions

All HTML elements are available as functions that accept:

- Optional first argument: attributes object
- Remaining arguments: child content

### escape(text)

Returns `text` with `&`, `<`, `>`, `"` and `'` replaced by entities. `null` and `undefined` become an empty string.

## Browser Support

Works in all modern browsers. When used in browser, functions are available on the global `htmb` object.

## Testing

```bash
npm test
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
