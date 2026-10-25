using System.Text.Json;
using HtmbLibrary;

namespace HtmbTests;

// The cases in documentation/test-cases.json and every tag in documentation/html.json,
// shared with the C and JavaScript tests.
public class SharedCaseTests
{
    private static JsonElement Load(string file) =>
        JsonDocument.Parse(File.ReadAllText(Path.Combine(AppContext.BaseDirectory, file))).RootElement;

    private static readonly JsonElement[] cases = Load("test-cases.json").GetProperty("cases").EnumerateArray().ToArray();
    private static readonly JsonElement html = Load("html.json");

    public static IEnumerable<object[]> CaseNames() =>
        cases.Select(c => new object[] { c.GetProperty("name").GetString()! });

    public static IEnumerable<object[]> Tags() =>
        html.GetProperty("tags").EnumerateArray().Select(t => new object[] { t.GetString()!, false })
            .Concat(html.GetProperty("tagsVoid").EnumerateArray().Select(t => new object[] { t.GetString()!, true }));

    [Theory]
    [MemberData(nameof(CaseNames))]
    public void Case(string name)
    {
        var c = cases.Single(c => c.GetProperty("name").GetString() == name);
        Assert.Equal(c.GetProperty("html").GetString(), Build(c));
    }

    [Theory]
    [MemberData(nameof(Tags))]
    public void EveryTag(string tag, bool isVoid)
    {
        Assert.Equal(isVoid ? $"<{tag}/>" : $"<{tag}></{tag}>", Call(Pascal(tag)));
    }

    private static string Build(JsonElement c)
    {
        if (c.TryGetProperty("escape", out var text))
        {
            return Htmb.Escape(text.GetString());
        }

        var name = Pascal(c.GetProperty("tag").GetString()!);
        var children = c.TryGetProperty("children", out var kids)
            ? kids.EnumerateArray().Select(k => k.GetString()!).ToArray()
            : [];
        bool isVoid = html.GetProperty("tagsVoid").EnumerateArray().Any(t => t.GetString() == c.GetProperty("tag").GetString());

        if (!c.TryGetProperty("attrs", out var attrList))
        {
            return isVoid ? Call(name) : Call(name, (object)children);
        }

        // C# takes attributes as one raw string, like you'd write them in HTML
        var attrs = string.Join(" ", attrList.EnumerateArray().Select(a =>
            a.GetArrayLength() == 1 ? a[0].GetString() : $"{a[0].GetString()}=\"{a[1].GetString()}\""));
        return isVoid ? Call(name + "Attr", attrs) : Call(name + "Attr", attrs, children);
    }

    private static string Call(string method, params object[] args)
    {
        var types = args.Select(a => a.GetType()).ToArray();
        var info = typeof(Htmb).GetMethod(method, types)
            ?? throw new MissingMethodException(nameof(Htmb), method);
        return (string)info.Invoke(null, args)!;
    }

    private static string Pascal(string tag) => char.ToUpper(tag[0]) + tag[1..];
}
