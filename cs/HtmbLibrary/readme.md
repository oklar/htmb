# HTMB for C# - Hypertext Markup Builder

A minimalistic C# library for building HTML structures using pure functions.

## Installation

```bash
dotnet add package htmb
```
## Usage
```csharp
using static HTMB.Htmb;

// Basic element (content only)
var div = Div("Hello World");
// -> <div>Hello World</div>

// With attributes (attrs are a literal string, like real HTML)
var container = DivAttr("class='container'",
    H1("Hello World"),
    P("Welcome to HTMB")
);
// -> <div class='container'><h1>Hello World</h1><p>Welcome to HTMB</p></div>
```