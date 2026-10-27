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

### ES modules and bundlers

```javascript
import { div, h1, p } from "htmb";
// or: import htmb from "htmb";
```

`import` loads `index.mjs`, a plain ES module, so it works in Node and with bundlers such as Vite, webpack and esbuild, including in browser code. Each tag and `escape` is a named export. `var` is a reserved word, so rename it when you import it: `import { var as varTag } from "htmb"`.

Before 1.2.0, `index.mjs` loaded the CommonJS build with Node's `createRequire`, so bundlers failed on it, and it only had a default export.

### TypeScript

The package comes with types, so there's nothing else to install:

```typescript
import { div, input, type Attributes } from "htmb";

const checkbox: Attributes = { type: "checkbox", checked: true };
div({ class: "row" }, input(checkbox), "Remember me");
```

Besides the tag functions and `escape`, it exports the types `Attributes`, `AttributeValue`, `Child` and `TagFunction`.

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

- Optional first argument: attributes object. Values are strings, numbers or booleans: `true` writes a bare attribute like `disabled`, and `false`, `null` and `undefined` leave the attribute out.
- Remaining arguments: children, as strings or numbers. `null` and `undefined` are skipped.

Each function returns the HTML as a string.

### escape(text)

Returns `text` with `&`, `<`, `>`, `"` and `'` replaced by entities. `null` and `undefined` become an empty string.

## Browser Support

Works in all modern browsers. When used in browser, functions are available on the global `htmb` object.

## Testing

```bash
npm test
```

To check the TypeScript types too, install TypeScript first:

```bash
npm install
```

```bash
npm run test:types
```

## Contributing

Contributions are welcome! Please feel free to submit a Pull Request.
