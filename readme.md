# HTMB (Hypertext Markdown Builder)

HTMB is a lightweight library for building HTML structures using functions. It provides a simple and intuitive way to create HTML elements programmatically across different programming languages.

## Overview

HTMB allows you to create HTML elements using function calls instead of writing raw HTML strings. Each function represents an HTML element and can accept various parameters to define attributes, content, and nested elements.

## Implementation

Each language folder contains its own implementation of the HTMB concept.

### JavaScript Implementation

The JavaScript implementation provides functions that generate HTML strings. Each HTML element is represented by a function that can be called in multiple ways:

```javascript
// Basic element with no content
div(); // -> "<div></div>"

// Element with inner text
div("hello world!"); // -> "<div>hello world!</div>"

// Element with attributes
div({ class: "text-green-500" }); // -> "<div class="text-green-500"></div>"

// Element with attributes and content
div({ class: "text-green-500" }, "hello world!"); // -> "<div class="text-green-500">hello world!</div>"

// Element with nested elements
div(span(), h1()); // -> "<div><span></span><h1></h1></div>"

// Element with attributes, text, and nested elements
div({ class: "text-green-500" }, "hello world!", span(), h1());
// -> "<div class="text-green-500">hello world!<span></span><h1></h1></div>"
```

### Special Cases

- Self-closing tags (like `img`, `br`, `input`) cannot contain child elements
- All HTML elements are supported through corresponding functions
- Multiple children can be passed as separate arguments

## Testing

Each implementation includes a test suite to verify:

- Basic element creation
- Attribute handling
- Nested elements
- Self-closing tags
- Mixed content (text and elements)
- Edge cases

## Future Enhancements

- Custom component support
- Additional language implementations
- Template support
- Style utilities

## Contributing

Feel free to contribute by:

1. Adding new language implementations
2. Improving existing implementations
3. Adding new features
4. Writing documentation
5. Creating examples

## License

...
