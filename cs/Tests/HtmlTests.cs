using Xunit;
using static HTMB.Htmb;

namespace HTMB.Tests;

public class HtmlTests
{
    [Fact]
    public void Div_ShouldReturnEmptyDiv_WhenNoArgumentsProvided()
    {
        var result = Div();
        Assert.Equal("<div></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithContent_WhenContentProvided()
    {
        var result = Div("Hello World");
        Assert.Equal("<div>Hello World</div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithAttributes_WhenAttributesProvided()
    {
        var result = Div([
            ("class", "my-class"),
            ("class", "my-class2")
        ]);
        Assert.Equal("<div class=\"my-class\" class=\"my-class2\"></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithBooleanAttribute_WhenValueIsNull()
    {
        var result = Div(("required", default));
        Assert.Equal("<div required></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithSingleAttribute_WhenSingleAttributeProvided()
    {
        var result = Div(("class", "my-class"));
        Assert.Equal("<div class=\"my-class\"></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithMixedContent_WhenAttributesAndMultipleContentProvided()
    {
        var result = Div(("class", "my-class"), "Hello", Div("World"));
        Assert.Equal("<div class=\"my-class\">Hello<div>World</div></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithChildDiv_WhenChildContentProvided()
    {
        var result = Div(Div("Hello World"));
        Assert.Equal("<div><div>Hello World</div></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithAttributesAndContent_WhenBothProvided()
    {
        var result = Div(
        [
            ("class", "my-class"),
            ("class", "my-class2")
        ], "Hello World");
        Assert.Equal("<div class=\"my-class\" class=\"my-class2\">Hello World</div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithAttributesAndChildDiv_WhenBothProvided()
    {
        var result = Div(
        [
            ("class", "my-class")
        ], Div("Hello World"));
        Assert.Equal("<div class=\"my-class\"><div>Hello World</div></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithAttributesAndMixedContent_WhenAllProvided()
    {
        var result = Div(
        [
            ("class", "my-class")
        ], "Hello World", Div("Hello World"), "Hello World");
        Assert.Equal("<div class=\"my-class\">Hello World<div>Hello World</div>Hello World</div>", result);
    }
}
