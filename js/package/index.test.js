const assert = require("assert");
const htmb = require("./index.cjs.js");

const { div, span, h1, p, img, br, input, a, style } = htmb;

(function runTests() {
  console.log("Running HTMB tests...");

  assert.strictEqual(div(), "<div></div>", "Empty div");
  assert.strictEqual(span(), "<span></span>", "Empty span");
  assert.strictEqual(div("hello"), "<div>hello</div>", "Div with text");
  assert.strictEqual(p("test"), "<p>test</p>", "Paragraph with text");

  assert.strictEqual(
    div({ class: "container" }),
    '<div class="container"></div>',
    "Element with class"
  );
  assert.strictEqual(
    a({ href: "https://example.com" }),
    '<a href="https://example.com"></a>',
    "Link with href"
  );

  assert.strictEqual(
    input({ disabled: true }),
    "<input disabled/>",
    "Input with boolean attribute"
  );
  assert.strictEqual(
    input({ disabled: false }),
    "<input/>",
    "Input with false boolean attribute"
  );

  assert.strictEqual(br(), "<br/>", "Self-closing br");
  assert.strictEqual(
    img({ src: "image.jpg" }),
    '<img src="image.jpg"/>',
    "Self-closing img with src"
  );

  assert.strictEqual(
    div(span("hello")),
    "<div><span>hello</span></div>",
    "Nested elements"
  );
  assert.strictEqual(
    div(h1("title"), p("content")),
    "<div><h1>title</h1><p>content</p></div>",
    "Multiple nested elements"
  );

  assert.strictEqual(
    div({ class: "container" }, h1("title")),
    '<div class="container"><h1>title</h1></div>',
    "Element with attributes and children"
  );

  assert.strictEqual(
    div({ "data-value": 'key="value"' }),
    '<div data-value="key=&quot;value&quot;"></div>',
    "Attribute value escaping"
  );

  assert.strictEqual(
    div(null, "text", undefined),
    "<div>text</div>",
    "Null and undefined children"
  );
  assert.strictEqual(
    div({ class: null, id: undefined, disabled: false }),
    "<div></div>",
    "Null and undefined attributes"
  );

  assert.strictEqual(
    style("body{margin:0}"),
    "<style>body{margin:0}</style>",
    "Style with content"
  );
  assert.strictEqual(style(), "<style></style>", "Empty style");

  console.log("All tests passed!");
})();
