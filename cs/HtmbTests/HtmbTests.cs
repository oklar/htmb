using static HtmbLibrary.Htmb;

namespace HtmbTests;

public class HtmbTests
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
        var result = DivAttr("class=\"my-class\" class=\"my-class2\"");
        Assert.Equal("<div class=\"my-class\" class=\"my-class2\"></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithMixedContent_WhenAttributesAndMultipleContentProvided()
    {
        var result = DivAttr("class=\"my-class\"", "Hello", Div("World"));
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
        var result = DivAttr("class=\"my-class\" class=\"my-class2\"", "Hello World");
        Assert.Equal("<div class=\"my-class\" class=\"my-class2\">Hello World</div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithAttributesAndChildDiv_WhenBothProvided()
    {
        var result = DivAttr("class=\"my-class\"", Div("Hello World"));
        Assert.Equal("<div class=\"my-class\"><div>Hello World</div></div>", result);
    }

    [Fact]
    public void Div_ShouldReturnDivWithAttributesAndMixedContent_WhenAllProvided()
    {
        var result = DivAttr("class=\"my-class\"", "Hello World", Div("Hello World"), "Hello World");
        Assert.Equal("<div class=\"my-class\">Hello World<div>Hello World</div>Hello World</div>", result);
    }


    [Fact]
    public void Input_ShouldReturnEmptyInput_WhenNoArgumentsProvided()
    {
        var result = Input();
        Assert.Equal("<input>", result);
    }

    [Fact]
    public void Input_ShouldReturnInputWithSingleAttribute_WhenSingleAttributeProvided()
    {
        var result = InputAttr("type=\"text\"");
        Assert.Equal("<input type=\"text\">", result);
    }

    [Fact]
    public void Input_ShouldReturnInputWithMultipleAttributes_WhenMultipleAttributesProvided()
    {
        var result = InputAttr("type=\"text\" name=\"username\" placeholder=\"Enter your username\"");
        Assert.Equal("<input type=\"text\" name=\"username\" placeholder=\"Enter your username\">", result);
    }

    [Fact]
    public void Input_ShouldReturnInputWithMixedAttributes_WhenAttributesProvided()
    {
        var result = InputAttr("type=\"checkbox\" checked name=\"subscribe\"");
        Assert.Equal("<input type=\"checkbox\" checked name=\"subscribe\">", result);
    }
}