using System.Text;



// https://html.spec.whatwg.org/multipage/syntax.html#void-elements
List<string> tagsVoid = ["area", "base", "br", "col", "embed", "hr", "img", "input", "link", "meta", "source", "track", "wbr"];

// https://html.spec.whatwg.org/dev/indices.html#index
List<string> tags = ["a", "abbr", "address", "article", "aside", "audio", "b", "bdi", "bdo", "blockquote", "body", "button", "canvas", "caption", "cite", "code", "colgroup", "data", "datalist", "dd", "del", "details", "dfn", "dialog", "div", "dl", "dt", "em", "fieldset", "figcaption", "figure", "footer", "form", "h1", "head", "header", "hgroup", "html", "i", "ins", "kbd", "label", "legend", "li", "main", "map", "mark", "menu", "meter", "nav", "noscript", "object", "ol", "optgroup", "option", "output", "p", "picture", "pre", "progress", "q", "rp", "rt", "ruby", "s", "samp", "script", "search", "section", "select", "slot", "small", "span", "strong", "style", "sub", "summary", "sup", "table", "tbody", "td", "textarea", "tfoot", "th", "thead", "time", "title", "tr", "u", "ul", "var", "video",
    "h2", "h3", "h4", "h5", "h6"];
List<string> listedAsEmptyButNotReally = ["iframe", "template"];
// For tags that are listed as empty but can have children.
tags.AddRange(listedAsEmptyButNotReally);

var sb = new StringBuilder();

foreach (var tag in tags)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);

    sb.AppendLine($"public static string {tagPascal}() => Tag(\"{tag}\");");
    sb.AppendLine($"public static string {tagPascal}(params string[] content) => Tag(\"{tag}\", content);");
    sb.AppendLine($"public static string {tagPascal}Attr(string attrs) => Tag(\"{tag}\", attrs);");
    sb.AppendLine($"public static string {tagPascal}Attr(string attrs, params string[] content) => Tag(\"{tag}\", attrs, content);");
    sb.AppendLine();
}

sb.AppendLine("// Void elements (TagSingle)");
foreach (var tag in tagsVoid)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);

    sb.AppendLine($"public static string {tagPascal}() => TagSingle(\"{tag}\");");
    sb.AppendLine($"public static string {tagPascal}Attr(string attrs) => TagSingle(\"{tag}\", attrs);");
    sb.AppendLine();
}

Console.WriteLine(sb);