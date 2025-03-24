namespace HTMB;


public static class Htmb
{
    public static string Div() => Tag("div");
    public static string Div(params string[] contents) => Tag("div", contents);
    public static string Div((string key, string? value) attribute) => Tag("div", [attribute]);
    public static string Div((string key, string? value) attribute, params string[] contents) => Tag("div", [attribute], contents);
    public static string Div(List<(string key, string? value)> attributes) => Tag("div", attributes);
    public static string Div(List<(string key, string? value)> attributes, params string[] contents) => Tag("div", attributes, contents);

    public static string Span() => Tag("span");
    public static string Span(params string[] contents) => Tag("span", contents);
    public static string Span((string key, string? value) attribute) => Tag("span", new List<(string, string?)> { attribute });
    public static string Span((string key, string? value) attribute, params string[] contents) => Tag("span", new List<(string, string?)> { attribute }, contents);
    public static string Span(List<(string key, string? value)> attributes) => Tag("span", attributes);
    public static string Span(List<(string key, string? value)> attributes, params string[] contents) => Tag("span", attributes, contents);

    public static string P() => Tag("p");
    public static string P(params string[] contents) => Tag("p", contents);
    public static string P((string key, string? value) attribute) => Tag("p", new List<(string, string?)> { attribute });
    public static string P((string key, string? value) attribute, params string[] contents) => Tag("p", new List<(string, string?)> { attribute }, contents);
    public static string P(List<(string key, string? value)> attributes) => Tag("p", attributes);
    public static string P(List<(string key, string? value)> attributes, params string[] contents) => Tag("p", attributes, contents);

    public static string H1() => Tag("h1");
    public static string H1(params string[] contents) => Tag("h1", contents);
    public static string H1((string key, string? value) attribute) => Tag("h1", new List<(string, string?)> { attribute });
    public static string H1((string key, string? value) attribute, params string[] contents) => Tag("h1", new List<(string, string?)> { attribute }, contents);
    public static string H1(List<(string key, string? value)> attributes) => Tag("h1", attributes);
    public static string H1(List<(string key, string? value)> attributes, params string[] contents) => Tag("h1", attributes, contents);

    public static string H2() => Tag("h2");
    public static string H2(params string[] contents) => Tag("h2", contents);
    public static string H2((string key, string? value) attribute) => Tag("h2", new List<(string, string?)> { attribute });
    public static string H2((string key, string? value) attribute, params string[] contents) => Tag("h2", new List<(string, string?)> { attribute }, contents);
    public static string H2(List<(string key, string? value)> attributes) => Tag("h2", attributes);
    public static string H2(List<(string key, string? value)> attributes, params string[] contents) => Tag("h2", attributes, contents);

    public static string H3() => Tag("h3");
    public static string H3(params string[] contents) => Tag("h3", contents);
    public static string H3((string key, string? value) attribute) => Tag("h3", new List<(string, string?)> { attribute });
    public static string H3((string key, string? value) attribute, params string[] contents) => Tag("h3", new List<(string, string?)> { attribute }, contents);
    public static string H3(List<(string key, string? value)> attributes) => Tag("h3", attributes);
    public static string H3(List<(string key, string? value)> attributes, params string[] contents) => Tag("h3", attributes, contents);

    public static string Section() => Tag("section");
    public static string Section(params string[] contents) => Tag("section", contents);
    public static string Section((string key, string? value) attribute) => Tag("section", new List<(string, string?)> { attribute });
    public static string Section((string key, string? value) attribute, params string[] contents) => Tag("section", new List<(string, string?)> { attribute }, contents);
    public static string Section(List<(string key, string? value)> attributes) => Tag("section", attributes);
    public static string Section(List<(string key, string? value)> attributes, params string[] contents) => Tag("section", attributes, contents);

    public static string Article() => Tag("article");
    public static string Article(params string[] contents) => Tag("article", contents);
    public static string Article((string key, string? value) attribute) => Tag("article", new List<(string, string?)> { attribute });
    public static string Article((string key, string? value) attribute, params string[] contents) => Tag("article", new List<(string, string?)> { attribute }, contents);
    public static string Article(List<(string key, string? value)> attributes) => Tag("article", attributes);
    public static string Article(List<(string key, string? value)> attributes, params string[] contents) => Tag("article", attributes, contents);

    public static string Header() => Tag("header");
    public static string Header(params string[] contents) => Tag("header", contents);
    public static string Header((string key, string? value) attribute) => Tag("header", new List<(string, string?)> { attribute });
    public static string Header((string key, string? value) attribute, params string[] contents) => Tag("header", new List<(string, string?)> { attribute }, contents);
    public static string Header(List<(string key, string? value)> attributes) => Tag("header", attributes);
    public static string Header(List<(string key, string? value)> attributes, params string[] contents) => Tag("header", attributes, contents);

    public static string Footer() => Tag("footer");
    public static string Footer(params string[] contents) => Tag("footer", contents);
    public static string Footer((string key, string? value) attribute) => Tag("footer", new List<(string, string?)> { attribute });
    public static string Footer((string key, string? value) attribute, params string[] contents) => Tag("footer", new List<(string, string?)> { attribute }, contents);
    public static string Footer(List<(string key, string? value)> attributes) => Tag("footer", attributes);
    public static string Footer(List<(string key, string? value)> attributes, params string[] contents) => Tag("footer", attributes, contents);

    public static string Nav() => Tag("nav");
    public static string Nav(params string[] contents) => Tag("nav", contents);
    public static string Nav((string key, string? value) attribute) => Tag("nav", new List<(string, string?)> { attribute });
    public static string Nav((string key, string? value) attribute, params string[] contents) => Tag("nav", new List<(string, string?)> { attribute }, contents);
    public static string Nav(List<(string key, string? value)> attributes) => Tag("nav", attributes);
    public static string Nav(List<(string key, string? value)> attributes, params string[] contents) => Tag("nav", attributes, contents);

    public static string Main() => Tag("main");
    public static string Main(params string[] contents) => Tag("main", contents);
    public static string Main((string key, string? value) attribute) => Tag("main", new List<(string, string?)> { attribute });
    public static string Main((string key, string? value) attribute, params string[] contents) => Tag("main", new List<(string, string?)> { attribute }, contents);
    public static string Main(List<(string key, string? value)> attributes) => Tag("main", attributes);
    public static string Main(List<(string key, string? value)> attributes, params string[] contents) => Tag("main", attributes, contents);

    public static string Aside() => Tag("aside");
    public static string Aside(params string[] contents) => Tag("aside", contents);
    public static string Aside((string key, string? value) attribute) => Tag("aside", new List<(string, string?)> { attribute });
    public static string Aside((string key, string? value) attribute, params string[] contents) => Tag("aside", new List<(string, string?)> { attribute }, contents);
    public static string Aside(List<(string key, string? value)> attributes) => Tag("aside", attributes);
    public static string Aside(List<(string key, string? value)> attributes, params string[] contents) => Tag("aside", attributes, contents);

    public static string Ul() => Tag("ul");
    public static string Ul(params string[] contents) => Tag("ul", contents);
    public static string Ul((string key, string? value) attribute) => Tag("ul", new List<(string, string?)> { attribute });
    public static string Ul((string key, string? value) attribute, params string[] contents) => Tag("ul", new List<(string, string?)> { attribute }, contents);
    public static string Ul(List<(string key, string? value)> attributes) => Tag("ul", attributes);
    public static string Ul(List<(string key, string? value)> attributes, params string[] contents) => Tag("ul", attributes, contents);

    public static string Li() => Tag("li");
    public static string Li(params string[] contents) => Tag("li", contents);
    public static string Li((string key, string? value) attribute) => Tag("li", new List<(string, string?)> { attribute });
    public static string Li((string key, string? value) attribute, params string[] contents) => Tag("li", new List<(string, string?)> { attribute }, contents);
    public static string Li(List<(string key, string? value)> attributes) => Tag("li", attributes);
    public static string Li(List<(string key, string? value)> attributes, params string[] contents) => Tag("li", attributes, contents);

    private static string Tag(string tagName)
    {
        return $"<{tagName}></{tagName}>";
    }

    private static string Tag(string tagName, List<(string key, string? value)> attributes)
    {
        return $"<{tagName}{GetAttributes(attributes)}></{tagName}>";
    }

    private static string Tag(string tagName, params string[] content)
    {
        return $"<{tagName}>{GetContent(content)}</{tagName}>";
    }

    private static string Tag(string tagName, List<(string key, string? value)> attributes, params string[] content)
    {
        return $"<{tagName}{GetAttributes(attributes)}>{GetContent(content)}</{tagName}>";
    }

    private static string GetContent(params string[] content)
    {
        return string.Join("", content);
    }

    private static string GetAttributes(List<(string key, string? value)> attributes)
    {
        string result = "";
        foreach ((string key, string? value) in attributes)
        {
            if (value is null)
            {
                result += $" {key}";
                continue;
            }
            result += $" {key}=\"{value}\"";
        }

        return result;
    }
}