using System.Text;



// https://html.spec.whatwg.org/multipage/syntax.html#void-elements
List<string> tagsVoid = ["area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "source", "track", "wbr"];

// https://html.spec.whatwg.org/dev/indices.html#index
List<string> tags = ["a", "abbr", "address", "article", "aside", "audio", "b", "bdi", "bdo", "blockquote", "body", "button", "canvas", "caption", "cite", "code", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "div", "dl", "dt", "em", "fieldset", "figcaption", "figure", "footer", "form", "h1", "head", "header", "hgroup", "html", "i", "ins", "kbd", "label", "legend", "li", "main", "map", "mark", "menu", "meter", "nav", "noscript", "object", "ol", "optgroup", "option", "output", "p", "picture", "pre", "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "search", "section", "select", "slot", "small", "span", "strong", "style", "sub", "summary", "sup", "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "u", "ul", "var", "video"];
List<string> listedAsEmptyButNotReally = ["iframe", "template"];
// For tags that are listed as empty but can have children.
tags.AddRange(listedAsEmptyButNotReally);

var sb = new StringBuilder();

// Generate overloads for non-void elements
foreach (var tag in tags)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);
    // String attribute overloads
    sb.AppendLine($"public static string {tagPascal}() => Tag(\"{tag}\");");
    sb.AppendLine($"public static string {tagPascal}(params string[] contents) => Tag(\"{tag}\", contents);");
    sb.AppendLine($"public static string {tagPascal}((string key, string? value) attribute) => Tag(\"{tag}\", new List<(string, string?)>{{ attribute }});");
    sb.AppendLine($"public static string {tagPascal}((string key, string? value) attribute, params string[] contents) => Tag(\"{tag}\", new List<(string, string?)>{{ attribute }}, contents);");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, string? value)> attributes) => Tag(\"{tag}\", attributes);");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, string? value)> attributes, params string[] contents) => Tag(\"{tag}\", attributes, contents);");

    // Bool? attribute overloads
    sb.AppendLine($"public static string {tagPascal}((string key, bool? value) attribute) => Tag(\"{tag}\", new List<(string, bool?)>{{ attribute }});");
    sb.AppendLine($"public static string {tagPascal}((string key, bool? value) attribute, params string[] contents) => Tag(\"{tag}\", new List<(string, bool?)>{{ attribute }}, contents);");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, bool? value)> attributes) => Tag(\"{tag}\", attributes);");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, bool? value)> attributes, params string[] contents) => Tag(\"{tag}\", attributes, contents);");
    sb.AppendLine();
}

sb.AppendLine();
sb.AppendLine("// Void elements (TagSingle)");
// Generate overloads for void elements
foreach (var tag in tagsVoid)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);
    // String attribute overloads
    sb.AppendLine($"public static string {tagPascal}() => TagSingle(\"{tag}\");");
    sb.AppendLine($"public static string {tagPascal}((string key, string? value) attribute) => TagSingle(\"{tag}\", new List<(string, string?)>{{ attribute }});");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, string? value)> attributes) => TagSingle(\"{tag}\", attributes);");

    // Bool? attribute overloads
    sb.AppendLine($"public static string {tagPascal}((string key, bool? value) attribute) => TagSingle(\"{tag}\", new List<(string, bool?)>{{ attribute }});");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, bool? value)> attributes) => TagSingle(\"{tag}\", attributes);");
    sb.AppendLine();
}

Console.WriteLine(sb);