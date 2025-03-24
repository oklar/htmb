using System.Text;

var tags = new List<string>
{
    "div",
    "span",
    "p",
    "h1",
    "h2",
    "h3",
    "section",
    "article",
    "header",
    "footer",
    "nav",
    "main",
    "aside",
    "ul",
    "li"
};

var sb = new StringBuilder();

foreach (var tag in tags)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);
    sb.AppendLine($"public static string {tagPascal}() => Tag(\"{tag}\");");
    sb.AppendLine($"public static string {tagPascal}(params string[] contents) => Tag(\"{tag}\", contents);");
    sb.AppendLine($"public static string {tagPascal}((string key, string? value) attribute) => Tag(\"{tag}\", new List<(string, string?)>{{ attribute }});");
    sb.AppendLine($"public static string {tagPascal}((string key, string? value) attribute, params string[] contents) => Tag(\"{tag}\", new List<(string, string?)>{{ attribute }}, contents);");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, string? value)> attributes) => Tag(\"{tag}\", attributes);");
    sb.AppendLine($"public static string {tagPascal}(List<(string key, string? value)> attributes, params string[] contents) => Tag(\"{tag}\", attributes, contents);");
    sb.AppendLine();
}

Console.WriteLine(sb);