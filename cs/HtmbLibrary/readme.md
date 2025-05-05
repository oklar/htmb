# HTMB for C# - Hypertext Markup Builder

A minimalistic C# library for building HTML structures using pure functions.

## Installation

```bash
dotnet add package htmb
```

## Usage

```csharp
using HTMB;
using static HtmbLibrary.Htmb;

// Basic elements
var div = Div("Hello World");
// -> '<div>Hello World</div>'

// With attributes
var container = Div(
    [("class", "container")],
    H1("Hello World"),
    P("Welcome to HTMB")
);
// -> '<div class="container"><h1>Hello World</h1><p>Welcome to HTMB</p></div>'

// Creating a list
var list = Ul(
    Li("Apple"),
    Li("Banana"),
    Li("Cherry")
);
// -> '<ul><li>Apple</li><li>Banana</li><li>Cherry</li></ul>'

// Using a single attribute
var element = Div(("id", "my-element"), "Content");
// -> '<div id="my-element">Content</div>'

// Boolean attributes
var required = Div(("required", default));
// -> '<div required></div>'
```

## Core Features

### Pure Functional API

HTMB uses a clean, functional approach where HTML elements are represented by pure functions:

```csharp
// Import all HTML functions
using static HTMB.Htmb;

// Use them directly without prefixes
var result = Div(
    H1("Title"),
    P("Content")
);
```

### Element Functions

All element functions follow a consistent pattern:

```csharp
// Basic element with no content
Element();
// -> '<element></element>'

// Element with content
Element("content");
// -> '<element>content</element>'

// Element with a single attribute
Element(("attr", "value"));
// -> '<element attr="value"></element>'

// Element with a single attribute and content
Element(("attr", "value"), "content");
// -> '<element attr="value">content</element>'

// Element with multiple attributes
Element([("attr1", "value1"), ("attr2", "value2")]);
// -> '<element attr1="value1" attr2="value2"></element>'

// Element with multiple attributes and content
Element([("attr1", "value1"), ("attr2", "value2")], "content");
// -> '<element attr1="value1" attr2="value2">content</element>'

// Element with multiple children
Element(
    Child1(),
    Child2(),
    "Text content"
);
// -> '<element><child1></child1><child2></child2>Text content</element>'

// Element with attributes and multiple children
Element([("attr", "value")],
    Child1(),
    Child2(),
    "Text content"
);
// -> '<element attr="value"><child1></child1><child2></child2>Text content</element>'
```

### Attributes

Attributes are defined using tuples or lists of tuples:

```csharp
// Single attribute
Div(("id", "main"));
// -> '<div id="main"></div>'

// Multiple attributes
Div([
    ("id", "main"),
    ("class", "container")
]);
// -> '<div id="main" class="container"></div>'

// Boolean attributes (using null value)
Div(("required", default));
// -> '<div required></div>'
```