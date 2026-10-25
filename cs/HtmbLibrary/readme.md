# HTMB for C# - Hypertext Markup Builder

A minimalistic C# library for building HTML structures using pure functions.

## Installation

```bash
dotnet add package htmb
```
## Usage
```csharp
using static HtmbLibrary.Htmb;

// Basic element (content only)
var div = Div("Hello World");
// -> <div>Hello World</div>

// With attributes (attrs are a literal string, like real HTML)
var container = DivAttr("class='container'",
    H1("Hello World"),
    P("Welcome to HTMB")
);
// -> <div class='container'><h1>Hello World</h1><p>Welcome to HTMB</p></div>

// Void elements close themselves
var field = InputAttr("type='text' disabled");
// -> <input type='text' disabled/>
```

## Escaping

Content and attributes go into the HTML as is, so a string like `<script>` becomes a real tag. Wrap anything that didn't come from your own code, such as form input or a query string, in `Escape()`. It replaces `&`, `<`, `>`, `"` and `'` with entities:

```csharp
var greeting = P("Hello, ", Escape(name));
```