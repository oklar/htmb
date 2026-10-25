using System.Text;
using System.Text.Json;

// Regenerates the tag methods in Htmb.cs from documentation/html.json:
//
//   dotnet run --project cs/HtmbSolution -- documentation/html.json cs/HtmbLibrary/Htmb.cs
//
// Only the lines between the two marker comments in Htmb.cs are rewritten.

const string beginMarker = "// tags below are generated";
const string endMarker = "// end of generated tags";

if (args.Length != 2)
{
    Console.Error.WriteLine("usage: dotnet run --project cs/HtmbSolution -- documentation/html.json cs/HtmbLibrary/Htmb.cs");
    return 2;
}
var (jsonPath, codePath) = (args[0], args[1]);

using var json = JsonDocument.Parse(File.ReadAllText(jsonPath));
List<string> Read(string key) =>
    json.RootElement.GetProperty(key).EnumerateArray().Select(t => t.GetString()!).ToList();

// https://html.spec.whatwg.org/dev/indices.html#index
var tags = Read("tags");
// https://html.spec.whatwg.org/multipage/syntax.html#void-elements
var tagsVoid = Read("tagsVoid");

var sb = new StringBuilder();

foreach (var tag in tags)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);

    sb.Append($"    public static string {tagPascal}() => Tag(\"{tag}\");\n");
    sb.Append($"    public static string {tagPascal}(params string[] content) => Tag(\"{tag}\", content);\n");
    sb.Append($"    public static string {tagPascal}Attr(string attrs) => Tag(\"{tag}\", attrs);\n");
    sb.Append($"    public static string {tagPascal}Attr(string attrs, params string[] content) => Tag(\"{tag}\", attrs, content);\n");
    sb.Append('\n');
}

sb.Append("    // Void elements (TagSingle)\n");
foreach (var tag in tagsVoid)
{
    var tagPascal = char.ToUpper(tag[0]) + tag.Substring(1);

    sb.Append($"    public static string {tagPascal}() => TagSingle(\"{tag}\");\n");
    sb.Append($"    public static string {tagPascal}Attr(string attrs) => TagSingle(\"{tag}\", attrs);\n");
    sb.Append('\n');
}

var code = File.ReadAllText(codePath);
int begin = code.IndexOf(beginMarker);
int end = code.IndexOf(endMarker);
if (begin < 0 || end < begin)
{
    Console.Error.WriteLine($"{codePath}: missing generated-tags markers");
    return 1;
}
begin = code.IndexOf('\n', begin) + 1;
end = code.LastIndexOf('\n', end) + 1;

// keep the file's own line endings
var generated = code.Contains("\r\n") ? sb.ToString().Replace("\n", "\r\n") : sb.ToString();
File.WriteAllText(codePath, code[..begin] + generated + code[end..], new UTF8Encoding(true));
Console.WriteLine($"{codePath}: {tags.Count} tags, {tagsVoid.Count} void tags");
return 0;
