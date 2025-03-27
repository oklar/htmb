namespace HTMB;


public static class Htmb
{
    public static string A() => Tag("a");
    public static string A(params string[] contents) => Tag("a", contents);
    public static string A((string key, string? value) attribute) => Tag("a", new List<(string, string?)> { attribute });
    public static string A((string key, string? value) attribute, params string[] contents) => Tag("a", new List<(string, string?)> { attribute }, contents);
    public static string A(List<(string key, string? value)> attributes) => Tag("a", attributes);
    public static string A(List<(string key, string? value)> attributes, params string[] contents) => Tag("a", attributes, contents);
    public static string A((string key, bool? value) attribute) => Tag("a", new List<(string, bool?)> { attribute });
    public static string A((string key, bool? value) attribute, params string[] contents) => Tag("a", new List<(string, bool?)> { attribute }, contents);
    public static string A(List<(string key, bool? value)> attributes) => Tag("a", attributes);
    public static string A(List<(string key, bool? value)> attributes, params string[] contents) => Tag("a", attributes, contents);

    public static string Abbr() => Tag("abbr");
    public static string Abbr(params string[] contents) => Tag("abbr", contents);
    public static string Abbr((string key, string? value) attribute) => Tag("abbr", new List<(string, string?)> { attribute });
    public static string Abbr((string key, string? value) attribute, params string[] contents) => Tag("abbr", new List<(string, string?)> { attribute }, contents);
    public static string Abbr(List<(string key, string? value)> attributes) => Tag("abbr", attributes);
    public static string Abbr(List<(string key, string? value)> attributes, params string[] contents) => Tag("abbr", attributes, contents);
    public static string Abbr((string key, bool? value) attribute) => Tag("abbr", new List<(string, bool?)> { attribute });
    public static string Abbr((string key, bool? value) attribute, params string[] contents) => Tag("abbr", new List<(string, bool?)> { attribute }, contents);
    public static string Abbr(List<(string key, bool? value)> attributes) => Tag("abbr", attributes);
    public static string Abbr(List<(string key, bool? value)> attributes, params string[] contents) => Tag("abbr", attributes, contents);

    public static string Address() => Tag("address");
    public static string Address(params string[] contents) => Tag("address", contents);
    public static string Address((string key, string? value) attribute) => Tag("address", new List<(string, string?)> { attribute });
    public static string Address((string key, string? value) attribute, params string[] contents) => Tag("address", new List<(string, string?)> { attribute }, contents);
    public static string Address(List<(string key, string? value)> attributes) => Tag("address", attributes);
    public static string Address(List<(string key, string? value)> attributes, params string[] contents) => Tag("address", attributes, contents);
    public static string Address((string key, bool? value) attribute) => Tag("address", new List<(string, bool?)> { attribute });
    public static string Address((string key, bool? value) attribute, params string[] contents) => Tag("address", new List<(string, bool?)> { attribute }, contents);
    public static string Address(List<(string key, bool? value)> attributes) => Tag("address", attributes);
    public static string Address(List<(string key, bool? value)> attributes, params string[] contents) => Tag("address", attributes, contents);

    public static string Article() => Tag("article");
    public static string Article(params string[] contents) => Tag("article", contents);
    public static string Article((string key, string? value) attribute) => Tag("article", new List<(string, string?)> { attribute });
    public static string Article((string key, string? value) attribute, params string[] contents) => Tag("article", new List<(string, string?)> { attribute }, contents);
    public static string Article(List<(string key, string? value)> attributes) => Tag("article", attributes);
    public static string Article(List<(string key, string? value)> attributes, params string[] contents) => Tag("article", attributes, contents);
    public static string Article((string key, bool? value) attribute) => Tag("article", new List<(string, bool?)> { attribute });
    public static string Article((string key, bool? value) attribute, params string[] contents) => Tag("article", new List<(string, bool?)> { attribute }, contents);
    public static string Article(List<(string key, bool? value)> attributes) => Tag("article", attributes);
    public static string Article(List<(string key, bool? value)> attributes, params string[] contents) => Tag("article", attributes, contents);

    public static string Aside() => Tag("aside");
    public static string Aside(params string[] contents) => Tag("aside", contents);
    public static string Aside((string key, string? value) attribute) => Tag("aside", new List<(string, string?)> { attribute });
    public static string Aside((string key, string? value) attribute, params string[] contents) => Tag("aside", new List<(string, string?)> { attribute }, contents);
    public static string Aside(List<(string key, string? value)> attributes) => Tag("aside", attributes);
    public static string Aside(List<(string key, string? value)> attributes, params string[] contents) => Tag("aside", attributes, contents);
    public static string Aside((string key, bool? value) attribute) => Tag("aside", new List<(string, bool?)> { attribute });
    public static string Aside((string key, bool? value) attribute, params string[] contents) => Tag("aside", new List<(string, bool?)> { attribute }, contents);
    public static string Aside(List<(string key, bool? value)> attributes) => Tag("aside", attributes);
    public static string Aside(List<(string key, bool? value)> attributes, params string[] contents) => Tag("aside", attributes, contents);

    public static string Audio() => Tag("audio");
    public static string Audio(params string[] contents) => Tag("audio", contents);
    public static string Audio((string key, string? value) attribute) => Tag("audio", new List<(string, string?)> { attribute });
    public static string Audio((string key, string? value) attribute, params string[] contents) => Tag("audio", new List<(string, string?)> { attribute }, contents);
    public static string Audio(List<(string key, string? value)> attributes) => Tag("audio", attributes);
    public static string Audio(List<(string key, string? value)> attributes, params string[] contents) => Tag("audio", attributes, contents);
    public static string Audio((string key, bool? value) attribute) => Tag("audio", new List<(string, bool?)> { attribute });
    public static string Audio((string key, bool? value) attribute, params string[] contents) => Tag("audio", new List<(string, bool?)> { attribute }, contents);
    public static string Audio(List<(string key, bool? value)> attributes) => Tag("audio", attributes);
    public static string Audio(List<(string key, bool? value)> attributes, params string[] contents) => Tag("audio", attributes, contents);

    public static string B() => Tag("b");
    public static string B(params string[] contents) => Tag("b", contents);
    public static string B((string key, string? value) attribute) => Tag("b", new List<(string, string?)> { attribute });
    public static string B((string key, string? value) attribute, params string[] contents) => Tag("b", new List<(string, string?)> { attribute }, contents);
    public static string B(List<(string key, string? value)> attributes) => Tag("b", attributes);
    public static string B(List<(string key, string? value)> attributes, params string[] contents) => Tag("b", attributes, contents);
    public static string B((string key, bool? value) attribute) => Tag("b", new List<(string, bool?)> { attribute });
    public static string B((string key, bool? value) attribute, params string[] contents) => Tag("b", new List<(string, bool?)> { attribute }, contents);
    public static string B(List<(string key, bool? value)> attributes) => Tag("b", attributes);
    public static string B(List<(string key, bool? value)> attributes, params string[] contents) => Tag("b", attributes, contents);

    public static string Bdi() => Tag("bdi");
    public static string Bdi(params string[] contents) => Tag("bdi", contents);
    public static string Bdi((string key, string? value) attribute) => Tag("bdi", new List<(string, string?)> { attribute });
    public static string Bdi((string key, string? value) attribute, params string[] contents) => Tag("bdi", new List<(string, string?)> { attribute }, contents);
    public static string Bdi(List<(string key, string? value)> attributes) => Tag("bdi", attributes);
    public static string Bdi(List<(string key, string? value)> attributes, params string[] contents) => Tag("bdi", attributes, contents);
    public static string Bdi((string key, bool? value) attribute) => Tag("bdi", new List<(string, bool?)> { attribute });
    public static string Bdi((string key, bool? value) attribute, params string[] contents) => Tag("bdi", new List<(string, bool?)> { attribute }, contents);
    public static string Bdi(List<(string key, bool? value)> attributes) => Tag("bdi", attributes);
    public static string Bdi(List<(string key, bool? value)> attributes, params string[] contents) => Tag("bdi", attributes, contents);

    public static string Bdo() => Tag("bdo");
    public static string Bdo(params string[] contents) => Tag("bdo", contents);
    public static string Bdo((string key, string? value) attribute) => Tag("bdo", new List<(string, string?)> { attribute });
    public static string Bdo((string key, string? value) attribute, params string[] contents) => Tag("bdo", new List<(string, string?)> { attribute }, contents);
    public static string Bdo(List<(string key, string? value)> attributes) => Tag("bdo", attributes);
    public static string Bdo(List<(string key, string? value)> attributes, params string[] contents) => Tag("bdo", attributes, contents);
    public static string Bdo((string key, bool? value) attribute) => Tag("bdo", new List<(string, bool?)> { attribute });
    public static string Bdo((string key, bool? value) attribute, params string[] contents) => Tag("bdo", new List<(string, bool?)> { attribute }, contents);
    public static string Bdo(List<(string key, bool? value)> attributes) => Tag("bdo", attributes);
    public static string Bdo(List<(string key, bool? value)> attributes, params string[] contents) => Tag("bdo", attributes, contents);

    public static string Blockquote() => Tag("blockquote");
    public static string Blockquote(params string[] contents) => Tag("blockquote", contents);
    public static string Blockquote((string key, string? value) attribute) => Tag("blockquote", new List<(string, string?)> { attribute });
    public static string Blockquote((string key, string? value) attribute, params string[] contents) => Tag("blockquote", new List<(string, string?)> { attribute }, contents);
    public static string Blockquote(List<(string key, string? value)> attributes) => Tag("blockquote", attributes);
    public static string Blockquote(List<(string key, string? value)> attributes, params string[] contents) => Tag("blockquote", attributes, contents);
    public static string Blockquote((string key, bool? value) attribute) => Tag("blockquote", new List<(string, bool?)> { attribute });
    public static string Blockquote((string key, bool? value) attribute, params string[] contents) => Tag("blockquote", new List<(string, bool?)> { attribute }, contents);
    public static string Blockquote(List<(string key, bool? value)> attributes) => Tag("blockquote", attributes);
    public static string Blockquote(List<(string key, bool? value)> attributes, params string[] contents) => Tag("blockquote", attributes, contents);

    public static string Body() => Tag("body");
    public static string Body(params string[] contents) => Tag("body", contents);
    public static string Body((string key, string? value) attribute) => Tag("body", new List<(string, string?)> { attribute });
    public static string Body((string key, string? value) attribute, params string[] contents) => Tag("body", new List<(string, string?)> { attribute }, contents);
    public static string Body(List<(string key, string? value)> attributes) => Tag("body", attributes);
    public static string Body(List<(string key, string? value)> attributes, params string[] contents) => Tag("body", attributes, contents);
    public static string Body((string key, bool? value) attribute) => Tag("body", new List<(string, bool?)> { attribute });
    public static string Body((string key, bool? value) attribute, params string[] contents) => Tag("body", new List<(string, bool?)> { attribute }, contents);
    public static string Body(List<(string key, bool? value)> attributes) => Tag("body", attributes);
    public static string Body(List<(string key, bool? value)> attributes, params string[] contents) => Tag("body", attributes, contents);

    public static string Button() => Tag("button");
    public static string Button(params string[] contents) => Tag("button", contents);
    public static string Button((string key, string? value) attribute) => Tag("button", new List<(string, string?)> { attribute });
    public static string Button((string key, string? value) attribute, params string[] contents) => Tag("button", new List<(string, string?)> { attribute }, contents);
    public static string Button(List<(string key, string? value)> attributes) => Tag("button", attributes);
    public static string Button(List<(string key, string? value)> attributes, params string[] contents) => Tag("button", attributes, contents);
    public static string Button((string key, bool? value) attribute) => Tag("button", new List<(string, bool?)> { attribute });
    public static string Button((string key, bool? value) attribute, params string[] contents) => Tag("button", new List<(string, bool?)> { attribute }, contents);
    public static string Button(List<(string key, bool? value)> attributes) => Tag("button", attributes);
    public static string Button(List<(string key, bool? value)> attributes, params string[] contents) => Tag("button", attributes, contents);

    public static string Canvas() => Tag("canvas");
    public static string Canvas(params string[] contents) => Tag("canvas", contents);
    public static string Canvas((string key, string? value) attribute) => Tag("canvas", new List<(string, string?)> { attribute });
    public static string Canvas((string key, string? value) attribute, params string[] contents) => Tag("canvas", new List<(string, string?)> { attribute }, contents);
    public static string Canvas(List<(string key, string? value)> attributes) => Tag("canvas", attributes);
    public static string Canvas(List<(string key, string? value)> attributes, params string[] contents) => Tag("canvas", attributes, contents);
    public static string Canvas((string key, bool? value) attribute) => Tag("canvas", new List<(string, bool?)> { attribute });
    public static string Canvas((string key, bool? value) attribute, params string[] contents) => Tag("canvas", new List<(string, bool?)> { attribute }, contents);
    public static string Canvas(List<(string key, bool? value)> attributes) => Tag("canvas", attributes);
    public static string Canvas(List<(string key, bool? value)> attributes, params string[] contents) => Tag("canvas", attributes, contents);

    public static string Caption() => Tag("caption");
    public static string Caption(params string[] contents) => Tag("caption", contents);
    public static string Caption((string key, string? value) attribute) => Tag("caption", new List<(string, string?)> { attribute });
    public static string Caption((string key, string? value) attribute, params string[] contents) => Tag("caption", new List<(string, string?)> { attribute }, contents);
    public static string Caption(List<(string key, string? value)> attributes) => Tag("caption", attributes);
    public static string Caption(List<(string key, string? value)> attributes, params string[] contents) => Tag("caption", attributes, contents);
    public static string Caption((string key, bool? value) attribute) => Tag("caption", new List<(string, bool?)> { attribute });
    public static string Caption((string key, bool? value) attribute, params string[] contents) => Tag("caption", new List<(string, bool?)> { attribute }, contents);
    public static string Caption(List<(string key, bool? value)> attributes) => Tag("caption", attributes);
    public static string Caption(List<(string key, bool? value)> attributes, params string[] contents) => Tag("caption", attributes, contents);

    public static string Cite() => Tag("cite");
    public static string Cite(params string[] contents) => Tag("cite", contents);
    public static string Cite((string key, string? value) attribute) => Tag("cite", new List<(string, string?)> { attribute });
    public static string Cite((string key, string? value) attribute, params string[] contents) => Tag("cite", new List<(string, string?)> { attribute }, contents);
    public static string Cite(List<(string key, string? value)> attributes) => Tag("cite", attributes);
    public static string Cite(List<(string key, string? value)> attributes, params string[] contents) => Tag("cite", attributes, contents);
    public static string Cite((string key, bool? value) attribute) => Tag("cite", new List<(string, bool?)> { attribute });
    public static string Cite((string key, bool? value) attribute, params string[] contents) => Tag("cite", new List<(string, bool?)> { attribute }, contents);
    public static string Cite(List<(string key, bool? value)> attributes) => Tag("cite", attributes);
    public static string Cite(List<(string key, bool? value)> attributes, params string[] contents) => Tag("cite", attributes, contents);

    public static string Code() => Tag("code");
    public static string Code(params string[] contents) => Tag("code", contents);
    public static string Code((string key, string? value) attribute) => Tag("code", new List<(string, string?)> { attribute });
    public static string Code((string key, string? value) attribute, params string[] contents) => Tag("code", new List<(string, string?)> { attribute }, contents);
    public static string Code(List<(string key, string? value)> attributes) => Tag("code", attributes);
    public static string Code(List<(string key, string? value)> attributes, params string[] contents) => Tag("code", attributes, contents);
    public static string Code((string key, bool? value) attribute) => Tag("code", new List<(string, bool?)> { attribute });
    public static string Code((string key, bool? value) attribute, params string[] contents) => Tag("code", new List<(string, bool?)> { attribute }, contents);
    public static string Code(List<(string key, bool? value)> attributes) => Tag("code", attributes);
    public static string Code(List<(string key, bool? value)> attributes, params string[] contents) => Tag("code", attributes, contents);

    public static string Colgroup() => Tag("colgroup");
    public static string Colgroup(params string[] contents) => Tag("colgroup", contents);
    public static string Colgroup((string key, string? value) attribute) => Tag("colgroup", new List<(string, string?)> { attribute });
    public static string Colgroup((string key, string? value) attribute, params string[] contents) => Tag("colgroup", new List<(string, string?)> { attribute }, contents);
    public static string Colgroup(List<(string key, string? value)> attributes) => Tag("colgroup", attributes);
    public static string Colgroup(List<(string key, string? value)> attributes, params string[] contents) => Tag("colgroup", attributes, contents);
    public static string Colgroup((string key, bool? value) attribute) => Tag("colgroup", new List<(string, bool?)> { attribute });
    public static string Colgroup((string key, bool? value) attribute, params string[] contents) => Tag("colgroup", new List<(string, bool?)> { attribute }, contents);
    public static string Colgroup(List<(string key, bool? value)> attributes) => Tag("colgroup", attributes);
    public static string Colgroup(List<(string key, bool? value)> attributes, params string[] contents) => Tag("colgroup", attributes, contents);

    public static string Data() => Tag("data");
    public static string Data(params string[] contents) => Tag("data", contents);
    public static string Data((string key, string? value) attribute) => Tag("data", new List<(string, string?)> { attribute });
    public static string Data((string key, string? value) attribute, params string[] contents) => Tag("data", new List<(string, string?)> { attribute }, contents);
    public static string Data(List<(string key, string? value)> attributes) => Tag("data", attributes);
    public static string Data(List<(string key, string? value)> attributes, params string[] contents) => Tag("data", attributes, contents);
    public static string Data((string key, bool? value) attribute) => Tag("data", new List<(string, bool?)> { attribute });
    public static string Data((string key, bool? value) attribute, params string[] contents) => Tag("data", new List<(string, bool?)> { attribute }, contents);
    public static string Data(List<(string key, bool? value)> attributes) => Tag("data", attributes);
    public static string Data(List<(string key, bool? value)> attributes, params string[] contents) => Tag("data", attributes, contents);

    public static string Datalist() => Tag("datalist");
    public static string Datalist(params string[] contents) => Tag("datalist", contents);
    public static string Datalist((string key, string? value) attribute) => Tag("datalist", new List<(string, string?)> { attribute });
    public static string Datalist((string key, string? value) attribute, params string[] contents) => Tag("datalist", new List<(string, string?)> { attribute }, contents);
    public static string Datalist(List<(string key, string? value)> attributes) => Tag("datalist", attributes);
    public static string Datalist(List<(string key, string? value)> attributes, params string[] contents) => Tag("datalist", attributes, contents);
    public static string Datalist((string key, bool? value) attribute) => Tag("datalist", new List<(string, bool?)> { attribute });
    public static string Datalist((string key, bool? value) attribute, params string[] contents) => Tag("datalist", new List<(string, bool?)> { attribute }, contents);
    public static string Datalist(List<(string key, bool? value)> attributes) => Tag("datalist", attributes);
    public static string Datalist(List<(string key, bool? value)> attributes, params string[] contents) => Tag("datalist", attributes, contents);

    public static string Dd() => Tag("dd");
    public static string Dd(params string[] contents) => Tag("dd", contents);
    public static string Dd((string key, string? value) attribute) => Tag("dd", new List<(string, string?)> { attribute });
    public static string Dd((string key, string? value) attribute, params string[] contents) => Tag("dd", new List<(string, string?)> { attribute }, contents);
    public static string Dd(List<(string key, string? value)> attributes) => Tag("dd", attributes);
    public static string Dd(List<(string key, string? value)> attributes, params string[] contents) => Tag("dd", attributes, contents);
    public static string Dd((string key, bool? value) attribute) => Tag("dd", new List<(string, bool?)> { attribute });
    public static string Dd((string key, bool? value) attribute, params string[] contents) => Tag("dd", new List<(string, bool?)> { attribute }, contents);
    public static string Dd(List<(string key, bool? value)> attributes) => Tag("dd", attributes);
    public static string Dd(List<(string key, bool? value)> attributes, params string[] contents) => Tag("dd", attributes, contents);

    public static string Del() => Tag("del");
    public static string Del(params string[] contents) => Tag("del", contents);
    public static string Del((string key, string? value) attribute) => Tag("del", new List<(string, string?)> { attribute });
    public static string Del((string key, string? value) attribute, params string[] contents) => Tag("del", new List<(string, string?)> { attribute }, contents);
    public static string Del(List<(string key, string? value)> attributes) => Tag("del", attributes);
    public static string Del(List<(string key, string? value)> attributes, params string[] contents) => Tag("del", attributes, contents);
    public static string Del((string key, bool? value) attribute) => Tag("del", new List<(string, bool?)> { attribute });
    public static string Del((string key, bool? value) attribute, params string[] contents) => Tag("del", new List<(string, bool?)> { attribute }, contents);
    public static string Del(List<(string key, bool? value)> attributes) => Tag("del", attributes);
    public static string Del(List<(string key, bool? value)> attributes, params string[] contents) => Tag("del", attributes, contents);

    public static string Details() => Tag("details");
    public static string Details(params string[] contents) => Tag("details", contents);
    public static string Details((string key, string? value) attribute) => Tag("details", new List<(string, string?)> { attribute });
    public static string Details((string key, string? value) attribute, params string[] contents) => Tag("details", new List<(string, string?)> { attribute }, contents);
    public static string Details(List<(string key, string? value)> attributes) => Tag("details", attributes);
    public static string Details(List<(string key, string? value)> attributes, params string[] contents) => Tag("details", attributes, contents);
    public static string Details((string key, bool? value) attribute) => Tag("details", new List<(string, bool?)> { attribute });
    public static string Details((string key, bool? value) attribute, params string[] contents) => Tag("details", new List<(string, bool?)> { attribute }, contents);
    public static string Details(List<(string key, bool? value)> attributes) => Tag("details", attributes);
    public static string Details(List<(string key, bool? value)> attributes, params string[] contents) => Tag("details", attributes, contents);

    public static string Dfn() => Tag("dfn");
    public static string Dfn(params string[] contents) => Tag("dfn", contents);
    public static string Dfn((string key, string? value) attribute) => Tag("dfn", new List<(string, string?)> { attribute });
    public static string Dfn((string key, string? value) attribute, params string[] contents) => Tag("dfn", new List<(string, string?)> { attribute }, contents);
    public static string Dfn(List<(string key, string? value)> attributes) => Tag("dfn", attributes);
    public static string Dfn(List<(string key, string? value)> attributes, params string[] contents) => Tag("dfn", attributes, contents);
    public static string Dfn((string key, bool? value) attribute) => Tag("dfn", new List<(string, bool?)> { attribute });
    public static string Dfn((string key, bool? value) attribute, params string[] contents) => Tag("dfn", new List<(string, bool?)> { attribute }, contents);
    public static string Dfn(List<(string key, bool? value)> attributes) => Tag("dfn", attributes);
    public static string Dfn(List<(string key, bool? value)> attributes, params string[] contents) => Tag("dfn", attributes, contents);

    public static string Dialog() => Tag("dialog");
    public static string Dialog(params string[] contents) => Tag("dialog", contents);
    public static string Dialog((string key, string? value) attribute) => Tag("dialog", new List<(string, string?)> { attribute });
    public static string Dialog((string key, string? value) attribute, params string[] contents) => Tag("dialog", new List<(string, string?)> { attribute }, contents);
    public static string Dialog(List<(string key, string? value)> attributes) => Tag("dialog", attributes);
    public static string Dialog(List<(string key, string? value)> attributes, params string[] contents) => Tag("dialog", attributes, contents);
    public static string Dialog((string key, bool? value) attribute) => Tag("dialog", new List<(string, bool?)> { attribute });
    public static string Dialog((string key, bool? value) attribute, params string[] contents) => Tag("dialog", new List<(string, bool?)> { attribute }, contents);
    public static string Dialog(List<(string key, bool? value)> attributes) => Tag("dialog", attributes);
    public static string Dialog(List<(string key, bool? value)> attributes, params string[] contents) => Tag("dialog", attributes, contents);

    public static string Div() => Tag("div");
    public static string Div(params string[] contents) => Tag("div", contents);
    public static string Div((string key, string? value) attribute) => Tag("div", new List<(string, string?)> { attribute });
    public static string Div((string key, string? value) attribute, params string[] contents) => Tag("div", new List<(string, string?)> { attribute }, contents);
    public static string Div(List<(string key, string? value)> attributes) => Tag("div", attributes);
    public static string Div(List<(string key, string? value)> attributes, params string[] contents) => Tag("div", attributes, contents);
    public static string Div((string key, bool? value) attribute) => Tag("div", new List<(string, bool?)> { attribute });
    public static string Div((string key, bool? value) attribute, params string[] contents) => Tag("div", new List<(string, bool?)> { attribute }, contents);
    public static string Div(List<(string key, bool? value)> attributes) => Tag("div", attributes);
    public static string Div(List<(string key, bool? value)> attributes, params string[] contents) => Tag("div", attributes, contents);

    public static string Dl() => Tag("dl");
    public static string Dl(params string[] contents) => Tag("dl", contents);
    public static string Dl((string key, string? value) attribute) => Tag("dl", new List<(string, string?)> { attribute });
    public static string Dl((string key, string? value) attribute, params string[] contents) => Tag("dl", new List<(string, string?)> { attribute }, contents);
    public static string Dl(List<(string key, string? value)> attributes) => Tag("dl", attributes);
    public static string Dl(List<(string key, string? value)> attributes, params string[] contents) => Tag("dl", attributes, contents);
    public static string Dl((string key, bool? value) attribute) => Tag("dl", new List<(string, bool?)> { attribute });
    public static string Dl((string key, bool? value) attribute, params string[] contents) => Tag("dl", new List<(string, bool?)> { attribute }, contents);
    public static string Dl(List<(string key, bool? value)> attributes) => Tag("dl", attributes);
    public static string Dl(List<(string key, bool? value)> attributes, params string[] contents) => Tag("dl", attributes, contents);

    public static string Dt() => Tag("dt");
    public static string Dt(params string[] contents) => Tag("dt", contents);
    public static string Dt((string key, string? value) attribute) => Tag("dt", new List<(string, string?)> { attribute });
    public static string Dt((string key, string? value) attribute, params string[] contents) => Tag("dt", new List<(string, string?)> { attribute }, contents);
    public static string Dt(List<(string key, string? value)> attributes) => Tag("dt", attributes);
    public static string Dt(List<(string key, string? value)> attributes, params string[] contents) => Tag("dt", attributes, contents);
    public static string Dt((string key, bool? value) attribute) => Tag("dt", new List<(string, bool?)> { attribute });
    public static string Dt((string key, bool? value) attribute, params string[] contents) => Tag("dt", new List<(string, bool?)> { attribute }, contents);
    public static string Dt(List<(string key, bool? value)> attributes) => Tag("dt", attributes);
    public static string Dt(List<(string key, bool? value)> attributes, params string[] contents) => Tag("dt", attributes, contents);

    public static string Em() => Tag("em");
    public static string Em(params string[] contents) => Tag("em", contents);
    public static string Em((string key, string? value) attribute) => Tag("em", new List<(string, string?)> { attribute });
    public static string Em((string key, string? value) attribute, params string[] contents) => Tag("em", new List<(string, string?)> { attribute }, contents);
    public static string Em(List<(string key, string? value)> attributes) => Tag("em", attributes);
    public static string Em(List<(string key, string? value)> attributes, params string[] contents) => Tag("em", attributes, contents);
    public static string Em((string key, bool? value) attribute) => Tag("em", new List<(string, bool?)> { attribute });
    public static string Em((string key, bool? value) attribute, params string[] contents) => Tag("em", new List<(string, bool?)> { attribute }, contents);
    public static string Em(List<(string key, bool? value)> attributes) => Tag("em", attributes);
    public static string Em(List<(string key, bool? value)> attributes, params string[] contents) => Tag("em", attributes, contents);

    public static string Fieldset() => Tag("fieldset");
    public static string Fieldset(params string[] contents) => Tag("fieldset", contents);
    public static string Fieldset((string key, string? value) attribute) => Tag("fieldset", new List<(string, string?)> { attribute });
    public static string Fieldset((string key, string? value) attribute, params string[] contents) => Tag("fieldset", new List<(string, string?)> { attribute }, contents);
    public static string Fieldset(List<(string key, string? value)> attributes) => Tag("fieldset", attributes);
    public static string Fieldset(List<(string key, string? value)> attributes, params string[] contents) => Tag("fieldset", attributes, contents);
    public static string Fieldset((string key, bool? value) attribute) => Tag("fieldset", new List<(string, bool?)> { attribute });
    public static string Fieldset((string key, bool? value) attribute, params string[] contents) => Tag("fieldset", new List<(string, bool?)> { attribute }, contents);
    public static string Fieldset(List<(string key, bool? value)> attributes) => Tag("fieldset", attributes);
    public static string Fieldset(List<(string key, bool? value)> attributes, params string[] contents) => Tag("fieldset", attributes, contents);

    public static string Figcaption() => Tag("figcaption");
    public static string Figcaption(params string[] contents) => Tag("figcaption", contents);
    public static string Figcaption((string key, string? value) attribute) => Tag("figcaption", new List<(string, string?)> { attribute });
    public static string Figcaption((string key, string? value) attribute, params string[] contents) => Tag("figcaption", new List<(string, string?)> { attribute }, contents);
    public static string Figcaption(List<(string key, string? value)> attributes) => Tag("figcaption", attributes);
    public static string Figcaption(List<(string key, string? value)> attributes, params string[] contents) => Tag("figcaption", attributes, contents);
    public static string Figcaption((string key, bool? value) attribute) => Tag("figcaption", new List<(string, bool?)> { attribute });
    public static string Figcaption((string key, bool? value) attribute, params string[] contents) => Tag("figcaption", new List<(string, bool?)> { attribute }, contents);
    public static string Figcaption(List<(string key, bool? value)> attributes) => Tag("figcaption", attributes);
    public static string Figcaption(List<(string key, bool? value)> attributes, params string[] contents) => Tag("figcaption", attributes, contents);

    public static string Figure() => Tag("figure");
    public static string Figure(params string[] contents) => Tag("figure", contents);
    public static string Figure((string key, string? value) attribute) => Tag("figure", new List<(string, string?)> { attribute });
    public static string Figure((string key, string? value) attribute, params string[] contents) => Tag("figure", new List<(string, string?)> { attribute }, contents);
    public static string Figure(List<(string key, string? value)> attributes) => Tag("figure", attributes);
    public static string Figure(List<(string key, string? value)> attributes, params string[] contents) => Tag("figure", attributes, contents);
    public static string Figure((string key, bool? value) attribute) => Tag("figure", new List<(string, bool?)> { attribute });
    public static string Figure((string key, bool? value) attribute, params string[] contents) => Tag("figure", new List<(string, bool?)> { attribute }, contents);
    public static string Figure(List<(string key, bool? value)> attributes) => Tag("figure", attributes);
    public static string Figure(List<(string key, bool? value)> attributes, params string[] contents) => Tag("figure", attributes, contents);

    public static string Footer() => Tag("footer");
    public static string Footer(params string[] contents) => Tag("footer", contents);
    public static string Footer((string key, string? value) attribute) => Tag("footer", new List<(string, string?)> { attribute });
    public static string Footer((string key, string? value) attribute, params string[] contents) => Tag("footer", new List<(string, string?)> { attribute }, contents);
    public static string Footer(List<(string key, string? value)> attributes) => Tag("footer", attributes);
    public static string Footer(List<(string key, string? value)> attributes, params string[] contents) => Tag("footer", attributes, contents);
    public static string Footer((string key, bool? value) attribute) => Tag("footer", new List<(string, bool?)> { attribute });
    public static string Footer((string key, bool? value) attribute, params string[] contents) => Tag("footer", new List<(string, bool?)> { attribute }, contents);
    public static string Footer(List<(string key, bool? value)> attributes) => Tag("footer", attributes);
    public static string Footer(List<(string key, bool? value)> attributes, params string[] contents) => Tag("footer", attributes, contents);

    public static string Form() => Tag("form");
    public static string Form(params string[] contents) => Tag("form", contents);
    public static string Form((string key, string? value) attribute) => Tag("form", new List<(string, string?)> { attribute });
    public static string Form((string key, string? value) attribute, params string[] contents) => Tag("form", new List<(string, string?)> { attribute }, contents);
    public static string Form(List<(string key, string? value)> attributes) => Tag("form", attributes);
    public static string Form(List<(string key, string? value)> attributes, params string[] contents) => Tag("form", attributes, contents);
    public static string Form((string key, bool? value) attribute) => Tag("form", new List<(string, bool?)> { attribute });
    public static string Form((string key, bool? value) attribute, params string[] contents) => Tag("form", new List<(string, bool?)> { attribute }, contents);
    public static string Form(List<(string key, bool? value)> attributes) => Tag("form", attributes);
    public static string Form(List<(string key, bool? value)> attributes, params string[] contents) => Tag("form", attributes, contents);

    public static string H1() => Tag("h1");
    public static string H1(params string[] contents) => Tag("h1", contents);
    public static string H1((string key, string? value) attribute) => Tag("h1", new List<(string, string?)> { attribute });
    public static string H1((string key, string? value) attribute, params string[] contents) => Tag("h1", new List<(string, string?)> { attribute }, contents);
    public static string H1(List<(string key, string? value)> attributes) => Tag("h1", attributes);
    public static string H1(List<(string key, string? value)> attributes, params string[] contents) => Tag("h1", attributes, contents);
    public static string H1((string key, bool? value) attribute) => Tag("h1", new List<(string, bool?)> { attribute });
    public static string H1((string key, bool? value) attribute, params string[] contents) => Tag("h1", new List<(string, bool?)> { attribute }, contents);
    public static string H1(List<(string key, bool? value)> attributes) => Tag("h1", attributes);
    public static string H1(List<(string key, bool? value)> attributes, params string[] contents) => Tag("h1", attributes, contents);

    public static string Head() => Tag("head");
    public static string Head(params string[] contents) => Tag("head", contents);
    public static string Head((string key, string? value) attribute) => Tag("head", new List<(string, string?)> { attribute });
    public static string Head((string key, string? value) attribute, params string[] contents) => Tag("head", new List<(string, string?)> { attribute }, contents);
    public static string Head(List<(string key, string? value)> attributes) => Tag("head", attributes);
    public static string Head(List<(string key, string? value)> attributes, params string[] contents) => Tag("head", attributes, contents);
    public static string Head((string key, bool? value) attribute) => Tag("head", new List<(string, bool?)> { attribute });
    public static string Head((string key, bool? value) attribute, params string[] contents) => Tag("head", new List<(string, bool?)> { attribute }, contents);
    public static string Head(List<(string key, bool? value)> attributes) => Tag("head", attributes);
    public static string Head(List<(string key, bool? value)> attributes, params string[] contents) => Tag("head", attributes, contents);

    public static string Header() => Tag("header");
    public static string Header(params string[] contents) => Tag("header", contents);
    public static string Header((string key, string? value) attribute) => Tag("header", new List<(string, string?)> { attribute });
    public static string Header((string key, string? value) attribute, params string[] contents) => Tag("header", new List<(string, string?)> { attribute }, contents);
    public static string Header(List<(string key, string? value)> attributes) => Tag("header", attributes);
    public static string Header(List<(string key, string? value)> attributes, params string[] contents) => Tag("header", attributes, contents);
    public static string Header((string key, bool? value) attribute) => Tag("header", new List<(string, bool?)> { attribute });
    public static string Header((string key, bool? value) attribute, params string[] contents) => Tag("header", new List<(string, bool?)> { attribute }, contents);
    public static string Header(List<(string key, bool? value)> attributes) => Tag("header", attributes);
    public static string Header(List<(string key, bool? value)> attributes, params string[] contents) => Tag("header", attributes, contents);

    public static string Hgroup() => Tag("hgroup");
    public static string Hgroup(params string[] contents) => Tag("hgroup", contents);
    public static string Hgroup((string key, string? value) attribute) => Tag("hgroup", new List<(string, string?)> { attribute });
    public static string Hgroup((string key, string? value) attribute, params string[] contents) => Tag("hgroup", new List<(string, string?)> { attribute }, contents);
    public static string Hgroup(List<(string key, string? value)> attributes) => Tag("hgroup", attributes);
    public static string Hgroup(List<(string key, string? value)> attributes, params string[] contents) => Tag("hgroup", attributes, contents);
    public static string Hgroup((string key, bool? value) attribute) => Tag("hgroup", new List<(string, bool?)> { attribute });
    public static string Hgroup((string key, bool? value) attribute, params string[] contents) => Tag("hgroup", new List<(string, bool?)> { attribute }, contents);
    public static string Hgroup(List<(string key, bool? value)> attributes) => Tag("hgroup", attributes);
    public static string Hgroup(List<(string key, bool? value)> attributes, params string[] contents) => Tag("hgroup", attributes, contents);

    public static string Html() => Tag("html");
    public static string Html(params string[] contents) => Tag("html", contents);
    public static string Html((string key, string? value) attribute) => Tag("html", new List<(string, string?)> { attribute });
    public static string Html((string key, string? value) attribute, params string[] contents) => Tag("html", new List<(string, string?)> { attribute }, contents);
    public static string Html(List<(string key, string? value)> attributes) => Tag("html", attributes);
    public static string Html(List<(string key, string? value)> attributes, params string[] contents) => Tag("html", attributes, contents);
    public static string Html((string key, bool? value) attribute) => Tag("html", new List<(string, bool?)> { attribute });
    public static string Html((string key, bool? value) attribute, params string[] contents) => Tag("html", new List<(string, bool?)> { attribute }, contents);
    public static string Html(List<(string key, bool? value)> attributes) => Tag("html", attributes);
    public static string Html(List<(string key, bool? value)> attributes, params string[] contents) => Tag("html", attributes, contents);

    public static string I() => Tag("i");
    public static string I(params string[] contents) => Tag("i", contents);
    public static string I((string key, string? value) attribute) => Tag("i", new List<(string, string?)> { attribute });
    public static string I((string key, string? value) attribute, params string[] contents) => Tag("i", new List<(string, string?)> { attribute }, contents);
    public static string I(List<(string key, string? value)> attributes) => Tag("i", attributes);
    public static string I(List<(string key, string? value)> attributes, params string[] contents) => Tag("i", attributes, contents);
    public static string I((string key, bool? value) attribute) => Tag("i", new List<(string, bool?)> { attribute });
    public static string I((string key, bool? value) attribute, params string[] contents) => Tag("i", new List<(string, bool?)> { attribute }, contents);
    public static string I(List<(string key, bool? value)> attributes) => Tag("i", attributes);
    public static string I(List<(string key, bool? value)> attributes, params string[] contents) => Tag("i", attributes, contents);

    public static string Ins() => Tag("ins");
    public static string Ins(params string[] contents) => Tag("ins", contents);
    public static string Ins((string key, string? value) attribute) => Tag("ins", new List<(string, string?)> { attribute });
    public static string Ins((string key, string? value) attribute, params string[] contents) => Tag("ins", new List<(string, string?)> { attribute }, contents);
    public static string Ins(List<(string key, string? value)> attributes) => Tag("ins", attributes);
    public static string Ins(List<(string key, string? value)> attributes, params string[] contents) => Tag("ins", attributes, contents);
    public static string Ins((string key, bool? value) attribute) => Tag("ins", new List<(string, bool?)> { attribute });
    public static string Ins((string key, bool? value) attribute, params string[] contents) => Tag("ins", new List<(string, bool?)> { attribute }, contents);
    public static string Ins(List<(string key, bool? value)> attributes) => Tag("ins", attributes);
    public static string Ins(List<(string key, bool? value)> attributes, params string[] contents) => Tag("ins", attributes, contents);

    public static string Kbd() => Tag("kbd");
    public static string Kbd(params string[] contents) => Tag("kbd", contents);
    public static string Kbd((string key, string? value) attribute) => Tag("kbd", new List<(string, string?)> { attribute });
    public static string Kbd((string key, string? value) attribute, params string[] contents) => Tag("kbd", new List<(string, string?)> { attribute }, contents);
    public static string Kbd(List<(string key, string? value)> attributes) => Tag("kbd", attributes);
    public static string Kbd(List<(string key, string? value)> attributes, params string[] contents) => Tag("kbd", attributes, contents);
    public static string Kbd((string key, bool? value) attribute) => Tag("kbd", new List<(string, bool?)> { attribute });
    public static string Kbd((string key, bool? value) attribute, params string[] contents) => Tag("kbd", new List<(string, bool?)> { attribute }, contents);
    public static string Kbd(List<(string key, bool? value)> attributes) => Tag("kbd", attributes);
    public static string Kbd(List<(string key, bool? value)> attributes, params string[] contents) => Tag("kbd", attributes, contents);

    public static string Label() => Tag("label");
    public static string Label(params string[] contents) => Tag("label", contents);
    public static string Label((string key, string? value) attribute) => Tag("label", new List<(string, string?)> { attribute });
    public static string Label((string key, string? value) attribute, params string[] contents) => Tag("label", new List<(string, string?)> { attribute }, contents);
    public static string Label(List<(string key, string? value)> attributes) => Tag("label", attributes);
    public static string Label(List<(string key, string? value)> attributes, params string[] contents) => Tag("label", attributes, contents);
    public static string Label((string key, bool? value) attribute) => Tag("label", new List<(string, bool?)> { attribute });
    public static string Label((string key, bool? value) attribute, params string[] contents) => Tag("label", new List<(string, bool?)> { attribute }, contents);
    public static string Label(List<(string key, bool? value)> attributes) => Tag("label", attributes);
    public static string Label(List<(string key, bool? value)> attributes, params string[] contents) => Tag("label", attributes, contents);

    public static string Legend() => Tag("legend");
    public static string Legend(params string[] contents) => Tag("legend", contents);
    public static string Legend((string key, string? value) attribute) => Tag("legend", new List<(string, string?)> { attribute });
    public static string Legend((string key, string? value) attribute, params string[] contents) => Tag("legend", new List<(string, string?)> { attribute }, contents);
    public static string Legend(List<(string key, string? value)> attributes) => Tag("legend", attributes);
    public static string Legend(List<(string key, string? value)> attributes, params string[] contents) => Tag("legend", attributes, contents);
    public static string Legend((string key, bool? value) attribute) => Tag("legend", new List<(string, bool?)> { attribute });
    public static string Legend((string key, bool? value) attribute, params string[] contents) => Tag("legend", new List<(string, bool?)> { attribute }, contents);
    public static string Legend(List<(string key, bool? value)> attributes) => Tag("legend", attributes);
    public static string Legend(List<(string key, bool? value)> attributes, params string[] contents) => Tag("legend", attributes, contents);

    public static string Li() => Tag("li");
    public static string Li(params string[] contents) => Tag("li", contents);
    public static string Li((string key, string? value) attribute) => Tag("li", new List<(string, string?)> { attribute });
    public static string Li((string key, string? value) attribute, params string[] contents) => Tag("li", new List<(string, string?)> { attribute }, contents);
    public static string Li(List<(string key, string? value)> attributes) => Tag("li", attributes);
    public static string Li(List<(string key, string? value)> attributes, params string[] contents) => Tag("li", attributes, contents);
    public static string Li((string key, bool? value) attribute) => Tag("li", new List<(string, bool?)> { attribute });
    public static string Li((string key, bool? value) attribute, params string[] contents) => Tag("li", new List<(string, bool?)> { attribute }, contents);
    public static string Li(List<(string key, bool? value)> attributes) => Tag("li", attributes);
    public static string Li(List<(string key, bool? value)> attributes, params string[] contents) => Tag("li", attributes, contents);

    public static string Main() => Tag("main");
    public static string Main(params string[] contents) => Tag("main", contents);
    public static string Main((string key, string? value) attribute) => Tag("main", new List<(string, string?)> { attribute });
    public static string Main((string key, string? value) attribute, params string[] contents) => Tag("main", new List<(string, string?)> { attribute }, contents);
    public static string Main(List<(string key, string? value)> attributes) => Tag("main", attributes);
    public static string Main(List<(string key, string? value)> attributes, params string[] contents) => Tag("main", attributes, contents);
    public static string Main((string key, bool? value) attribute) => Tag("main", new List<(string, bool?)> { attribute });
    public static string Main((string key, bool? value) attribute, params string[] contents) => Tag("main", new List<(string, bool?)> { attribute }, contents);
    public static string Main(List<(string key, bool? value)> attributes) => Tag("main", attributes);
    public static string Main(List<(string key, bool? value)> attributes, params string[] contents) => Tag("main", attributes, contents);

    public static string Map() => Tag("map");
    public static string Map(params string[] contents) => Tag("map", contents);
    public static string Map((string key, string? value) attribute) => Tag("map", new List<(string, string?)> { attribute });
    public static string Map((string key, string? value) attribute, params string[] contents) => Tag("map", new List<(string, string?)> { attribute }, contents);
    public static string Map(List<(string key, string? value)> attributes) => Tag("map", attributes);
    public static string Map(List<(string key, string? value)> attributes, params string[] contents) => Tag("map", attributes, contents);
    public static string Map((string key, bool? value) attribute) => Tag("map", new List<(string, bool?)> { attribute });
    public static string Map((string key, bool? value) attribute, params string[] contents) => Tag("map", new List<(string, bool?)> { attribute }, contents);
    public static string Map(List<(string key, bool? value)> attributes) => Tag("map", attributes);
    public static string Map(List<(string key, bool? value)> attributes, params string[] contents) => Tag("map", attributes, contents);

    public static string Mark() => Tag("mark");
    public static string Mark(params string[] contents) => Tag("mark", contents);
    public static string Mark((string key, string? value) attribute) => Tag("mark", new List<(string, string?)> { attribute });
    public static string Mark((string key, string? value) attribute, params string[] contents) => Tag("mark", new List<(string, string?)> { attribute }, contents);
    public static string Mark(List<(string key, string? value)> attributes) => Tag("mark", attributes);
    public static string Mark(List<(string key, string? value)> attributes, params string[] contents) => Tag("mark", attributes, contents);
    public static string Mark((string key, bool? value) attribute) => Tag("mark", new List<(string, bool?)> { attribute });
    public static string Mark((string key, bool? value) attribute, params string[] contents) => Tag("mark", new List<(string, bool?)> { attribute }, contents);
    public static string Mark(List<(string key, bool? value)> attributes) => Tag("mark", attributes);
    public static string Mark(List<(string key, bool? value)> attributes, params string[] contents) => Tag("mark", attributes, contents);

    public static string Menu() => Tag("menu");
    public static string Menu(params string[] contents) => Tag("menu", contents);
    public static string Menu((string key, string? value) attribute) => Tag("menu", new List<(string, string?)> { attribute });
    public static string Menu((string key, string? value) attribute, params string[] contents) => Tag("menu", new List<(string, string?)> { attribute }, contents);
    public static string Menu(List<(string key, string? value)> attributes) => Tag("menu", attributes);
    public static string Menu(List<(string key, string? value)> attributes, params string[] contents) => Tag("menu", attributes, contents);
    public static string Menu((string key, bool? value) attribute) => Tag("menu", new List<(string, bool?)> { attribute });
    public static string Menu((string key, bool? value) attribute, params string[] contents) => Tag("menu", new List<(string, bool?)> { attribute }, contents);
    public static string Menu(List<(string key, bool? value)> attributes) => Tag("menu", attributes);
    public static string Menu(List<(string key, bool? value)> attributes, params string[] contents) => Tag("menu", attributes, contents);

    public static string Meter() => Tag("meter");
    public static string Meter(params string[] contents) => Tag("meter", contents);
    public static string Meter((string key, string? value) attribute) => Tag("meter", new List<(string, string?)> { attribute });
    public static string Meter((string key, string? value) attribute, params string[] contents) => Tag("meter", new List<(string, string?)> { attribute }, contents);
    public static string Meter(List<(string key, string? value)> attributes) => Tag("meter", attributes);
    public static string Meter(List<(string key, string? value)> attributes, params string[] contents) => Tag("meter", attributes, contents);
    public static string Meter((string key, bool? value) attribute) => Tag("meter", new List<(string, bool?)> { attribute });
    public static string Meter((string key, bool? value) attribute, params string[] contents) => Tag("meter", new List<(string, bool?)> { attribute }, contents);
    public static string Meter(List<(string key, bool? value)> attributes) => Tag("meter", attributes);
    public static string Meter(List<(string key, bool? value)> attributes, params string[] contents) => Tag("meter", attributes, contents);

    public static string Nav() => Tag("nav");
    public static string Nav(params string[] contents) => Tag("nav", contents);
    public static string Nav((string key, string? value) attribute) => Tag("nav", new List<(string, string?)> { attribute });
    public static string Nav((string key, string? value) attribute, params string[] contents) => Tag("nav", new List<(string, string?)> { attribute }, contents);
    public static string Nav(List<(string key, string? value)> attributes) => Tag("nav", attributes);
    public static string Nav(List<(string key, string? value)> attributes, params string[] contents) => Tag("nav", attributes, contents);
    public static string Nav((string key, bool? value) attribute) => Tag("nav", new List<(string, bool?)> { attribute });
    public static string Nav((string key, bool? value) attribute, params string[] contents) => Tag("nav", new List<(string, bool?)> { attribute }, contents);
    public static string Nav(List<(string key, bool? value)> attributes) => Tag("nav", attributes);
    public static string Nav(List<(string key, bool? value)> attributes, params string[] contents) => Tag("nav", attributes, contents);

    public static string Noscript() => Tag("noscript");
    public static string Noscript(params string[] contents) => Tag("noscript", contents);
    public static string Noscript((string key, string? value) attribute) => Tag("noscript", new List<(string, string?)> { attribute });
    public static string Noscript((string key, string? value) attribute, params string[] contents) => Tag("noscript", new List<(string, string?)> { attribute }, contents);
    public static string Noscript(List<(string key, string? value)> attributes) => Tag("noscript", attributes);
    public static string Noscript(List<(string key, string? value)> attributes, params string[] contents) => Tag("noscript", attributes, contents);
    public static string Noscript((string key, bool? value) attribute) => Tag("noscript", new List<(string, bool?)> { attribute });
    public static string Noscript((string key, bool? value) attribute, params string[] contents) => Tag("noscript", new List<(string, bool?)> { attribute }, contents);
    public static string Noscript(List<(string key, bool? value)> attributes) => Tag("noscript", attributes);
    public static string Noscript(List<(string key, bool? value)> attributes, params string[] contents) => Tag("noscript", attributes, contents);

    public static string Object() => Tag("object");
    public static string Object(params string[] contents) => Tag("object", contents);
    public static string Object((string key, string? value) attribute) => Tag("object", new List<(string, string?)> { attribute });
    public static string Object((string key, string? value) attribute, params string[] contents) => Tag("object", new List<(string, string?)> { attribute }, contents);
    public static string Object(List<(string key, string? value)> attributes) => Tag("object", attributes);
    public static string Object(List<(string key, string? value)> attributes, params string[] contents) => Tag("object", attributes, contents);
    public static string Object((string key, bool? value) attribute) => Tag("object", new List<(string, bool?)> { attribute });
    public static string Object((string key, bool? value) attribute, params string[] contents) => Tag("object", new List<(string, bool?)> { attribute }, contents);
    public static string Object(List<(string key, bool? value)> attributes) => Tag("object", attributes);
    public static string Object(List<(string key, bool? value)> attributes, params string[] contents) => Tag("object", attributes, contents);

    public static string Ol() => Tag("ol");
    public static string Ol(params string[] contents) => Tag("ol", contents);
    public static string Ol((string key, string? value) attribute) => Tag("ol", new List<(string, string?)> { attribute });
    public static string Ol((string key, string? value) attribute, params string[] contents) => Tag("ol", new List<(string, string?)> { attribute }, contents);
    public static string Ol(List<(string key, string? value)> attributes) => Tag("ol", attributes);
    public static string Ol(List<(string key, string? value)> attributes, params string[] contents) => Tag("ol", attributes, contents);
    public static string Ol((string key, bool? value) attribute) => Tag("ol", new List<(string, bool?)> { attribute });
    public static string Ol((string key, bool? value) attribute, params string[] contents) => Tag("ol", new List<(string, bool?)> { attribute }, contents);
    public static string Ol(List<(string key, bool? value)> attributes) => Tag("ol", attributes);
    public static string Ol(List<(string key, bool? value)> attributes, params string[] contents) => Tag("ol", attributes, contents);

    public static string Optgroup() => Tag("optgroup");
    public static string Optgroup(params string[] contents) => Tag("optgroup", contents);
    public static string Optgroup((string key, string? value) attribute) => Tag("optgroup", new List<(string, string?)> { attribute });
    public static string Optgroup((string key, string? value) attribute, params string[] contents) => Tag("optgroup", new List<(string, string?)> { attribute }, contents);
    public static string Optgroup(List<(string key, string? value)> attributes) => Tag("optgroup", attributes);
    public static string Optgroup(List<(string key, string? value)> attributes, params string[] contents) => Tag("optgroup", attributes, contents);
    public static string Optgroup((string key, bool? value) attribute) => Tag("optgroup", new List<(string, bool?)> { attribute });
    public static string Optgroup((string key, bool? value) attribute, params string[] contents) => Tag("optgroup", new List<(string, bool?)> { attribute }, contents);
    public static string Optgroup(List<(string key, bool? value)> attributes) => Tag("optgroup", attributes);
    public static string Optgroup(List<(string key, bool? value)> attributes, params string[] contents) => Tag("optgroup", attributes, contents);

    public static string Option() => Tag("option");
    public static string Option(params string[] contents) => Tag("option", contents);
    public static string Option((string key, string? value) attribute) => Tag("option", new List<(string, string?)> { attribute });
    public static string Option((string key, string? value) attribute, params string[] contents) => Tag("option", new List<(string, string?)> { attribute }, contents);
    public static string Option(List<(string key, string? value)> attributes) => Tag("option", attributes);
    public static string Option(List<(string key, string? value)> attributes, params string[] contents) => Tag("option", attributes, contents);
    public static string Option((string key, bool? value) attribute) => Tag("option", new List<(string, bool?)> { attribute });
    public static string Option((string key, bool? value) attribute, params string[] contents) => Tag("option", new List<(string, bool?)> { attribute }, contents);
    public static string Option(List<(string key, bool? value)> attributes) => Tag("option", attributes);
    public static string Option(List<(string key, bool? value)> attributes, params string[] contents) => Tag("option", attributes, contents);

    public static string Output() => Tag("output");
    public static string Output(params string[] contents) => Tag("output", contents);
    public static string Output((string key, string? value) attribute) => Tag("output", new List<(string, string?)> { attribute });
    public static string Output((string key, string? value) attribute, params string[] contents) => Tag("output", new List<(string, string?)> { attribute }, contents);
    public static string Output(List<(string key, string? value)> attributes) => Tag("output", attributes);
    public static string Output(List<(string key, string? value)> attributes, params string[] contents) => Tag("output", attributes, contents);
    public static string Output((string key, bool? value) attribute) => Tag("output", new List<(string, bool?)> { attribute });
    public static string Output((string key, bool? value) attribute, params string[] contents) => Tag("output", new List<(string, bool?)> { attribute }, contents);
    public static string Output(List<(string key, bool? value)> attributes) => Tag("output", attributes);
    public static string Output(List<(string key, bool? value)> attributes, params string[] contents) => Tag("output", attributes, contents);

    public static string P() => Tag("p");
    public static string P(params string[] contents) => Tag("p", contents);
    public static string P((string key, string? value) attribute) => Tag("p", new List<(string, string?)> { attribute });
    public static string P((string key, string? value) attribute, params string[] contents) => Tag("p", new List<(string, string?)> { attribute }, contents);
    public static string P(List<(string key, string? value)> attributes) => Tag("p", attributes);
    public static string P(List<(string key, string? value)> attributes, params string[] contents) => Tag("p", attributes, contents);
    public static string P((string key, bool? value) attribute) => Tag("p", new List<(string, bool?)> { attribute });
    public static string P((string key, bool? value) attribute, params string[] contents) => Tag("p", new List<(string, bool?)> { attribute }, contents);
    public static string P(List<(string key, bool? value)> attributes) => Tag("p", attributes);
    public static string P(List<(string key, bool? value)> attributes, params string[] contents) => Tag("p", attributes, contents);

    public static string Picture() => Tag("picture");
    public static string Picture(params string[] contents) => Tag("picture", contents);
    public static string Picture((string key, string? value) attribute) => Tag("picture", new List<(string, string?)> { attribute });
    public static string Picture((string key, string? value) attribute, params string[] contents) => Tag("picture", new List<(string, string?)> { attribute }, contents);
    public static string Picture(List<(string key, string? value)> attributes) => Tag("picture", attributes);
    public static string Picture(List<(string key, string? value)> attributes, params string[] contents) => Tag("picture", attributes, contents);
    public static string Picture((string key, bool? value) attribute) => Tag("picture", new List<(string, bool?)> { attribute });
    public static string Picture((string key, bool? value) attribute, params string[] contents) => Tag("picture", new List<(string, bool?)> { attribute }, contents);
    public static string Picture(List<(string key, bool? value)> attributes) => Tag("picture", attributes);
    public static string Picture(List<(string key, bool? value)> attributes, params string[] contents) => Tag("picture", attributes, contents);

    public static string Pre() => Tag("pre");
    public static string Pre(params string[] contents) => Tag("pre", contents);
    public static string Pre((string key, string? value) attribute) => Tag("pre", new List<(string, string?)> { attribute });
    public static string Pre((string key, string? value) attribute, params string[] contents) => Tag("pre", new List<(string, string?)> { attribute }, contents);
    public static string Pre(List<(string key, string? value)> attributes) => Tag("pre", attributes);
    public static string Pre(List<(string key, string? value)> attributes, params string[] contents) => Tag("pre", attributes, contents);
    public static string Pre((string key, bool? value) attribute) => Tag("pre", new List<(string, bool?)> { attribute });
    public static string Pre((string key, bool? value) attribute, params string[] contents) => Tag("pre", new List<(string, bool?)> { attribute }, contents);
    public static string Pre(List<(string key, bool? value)> attributes) => Tag("pre", attributes);
    public static string Pre(List<(string key, bool? value)> attributes, params string[] contents) => Tag("pre", attributes, contents);

    public static string Progress() => Tag("progress");
    public static string Progress(params string[] contents) => Tag("progress", contents);
    public static string Progress((string key, string? value) attribute) => Tag("progress", new List<(string, string?)> { attribute });
    public static string Progress((string key, string? value) attribute, params string[] contents) => Tag("progress", new List<(string, string?)> { attribute }, contents);
    public static string Progress(List<(string key, string? value)> attributes) => Tag("progress", attributes);
    public static string Progress(List<(string key, string? value)> attributes, params string[] contents) => Tag("progress", attributes, contents);
    public static string Progress((string key, bool? value) attribute) => Tag("progress", new List<(string, bool?)> { attribute });
    public static string Progress((string key, bool? value) attribute, params string[] contents) => Tag("progress", new List<(string, bool?)> { attribute }, contents);
    public static string Progress(List<(string key, bool? value)> attributes) => Tag("progress", attributes);
    public static string Progress(List<(string key, bool? value)> attributes, params string[] contents) => Tag("progress", attributes, contents);

    public static string Q() => Tag("q");
    public static string Q(params string[] contents) => Tag("q", contents);
    public static string Q((string key, string? value) attribute) => Tag("q", new List<(string, string?)> { attribute });
    public static string Q((string key, string? value) attribute, params string[] contents) => Tag("q", new List<(string, string?)> { attribute }, contents);
    public static string Q(List<(string key, string? value)> attributes) => Tag("q", attributes);
    public static string Q(List<(string key, string? value)> attributes, params string[] contents) => Tag("q", attributes, contents);
    public static string Q((string key, bool? value) attribute) => Tag("q", new List<(string, bool?)> { attribute });
    public static string Q((string key, bool? value) attribute, params string[] contents) => Tag("q", new List<(string, bool?)> { attribute }, contents);
    public static string Q(List<(string key, bool? value)> attributes) => Tag("q", attributes);
    public static string Q(List<(string key, bool? value)> attributes, params string[] contents) => Tag("q", attributes, contents);

    public static string Rp() => Tag("rp");
    public static string Rp(params string[] contents) => Tag("rp", contents);
    public static string Rp((string key, string? value) attribute) => Tag("rp", new List<(string, string?)> { attribute });
    public static string Rp((string key, string? value) attribute, params string[] contents) => Tag("rp", new List<(string, string?)> { attribute }, contents);
    public static string Rp(List<(string key, string? value)> attributes) => Tag("rp", attributes);
    public static string Rp(List<(string key, string? value)> attributes, params string[] contents) => Tag("rp", attributes, contents);
    public static string Rp((string key, bool? value) attribute) => Tag("rp", new List<(string, bool?)> { attribute });
    public static string Rp((string key, bool? value) attribute, params string[] contents) => Tag("rp", new List<(string, bool?)> { attribute }, contents);
    public static string Rp(List<(string key, bool? value)> attributes) => Tag("rp", attributes);
    public static string Rp(List<(string key, bool? value)> attributes, params string[] contents) => Tag("rp", attributes, contents);

    public static string Rt() => Tag("rt");
    public static string Rt(params string[] contents) => Tag("rt", contents);
    public static string Rt((string key, string? value) attribute) => Tag("rt", new List<(string, string?)> { attribute });
    public static string Rt((string key, string? value) attribute, params string[] contents) => Tag("rt", new List<(string, string?)> { attribute }, contents);
    public static string Rt(List<(string key, string? value)> attributes) => Tag("rt", attributes);
    public static string Rt(List<(string key, string? value)> attributes, params string[] contents) => Tag("rt", attributes, contents);
    public static string Rt((string key, bool? value) attribute) => Tag("rt", new List<(string, bool?)> { attribute });
    public static string Rt((string key, bool? value) attribute, params string[] contents) => Tag("rt", new List<(string, bool?)> { attribute }, contents);
    public static string Rt(List<(string key, bool? value)> attributes) => Tag("rt", attributes);
    public static string Rt(List<(string key, bool? value)> attributes, params string[] contents) => Tag("rt", attributes, contents);

    public static string Ruby() => Tag("ruby");
    public static string Ruby(params string[] contents) => Tag("ruby", contents);
    public static string Ruby((string key, string? value) attribute) => Tag("ruby", new List<(string, string?)> { attribute });
    public static string Ruby((string key, string? value) attribute, params string[] contents) => Tag("ruby", new List<(string, string?)> { attribute }, contents);
    public static string Ruby(List<(string key, string? value)> attributes) => Tag("ruby", attributes);
    public static string Ruby(List<(string key, string? value)> attributes, params string[] contents) => Tag("ruby", attributes, contents);
    public static string Ruby((string key, bool? value) attribute) => Tag("ruby", new List<(string, bool?)> { attribute });
    public static string Ruby((string key, bool? value) attribute, params string[] contents) => Tag("ruby", new List<(string, bool?)> { attribute }, contents);
    public static string Ruby(List<(string key, bool? value)> attributes) => Tag("ruby", attributes);
    public static string Ruby(List<(string key, bool? value)> attributes, params string[] contents) => Tag("ruby", attributes, contents);

    public static string S() => Tag("s");
    public static string S(params string[] contents) => Tag("s", contents);
    public static string S((string key, string? value) attribute) => Tag("s", new List<(string, string?)> { attribute });
    public static string S((string key, string? value) attribute, params string[] contents) => Tag("s", new List<(string, string?)> { attribute }, contents);
    public static string S(List<(string key, string? value)> attributes) => Tag("s", attributes);
    public static string S(List<(string key, string? value)> attributes, params string[] contents) => Tag("s", attributes, contents);
    public static string S((string key, bool? value) attribute) => Tag("s", new List<(string, bool?)> { attribute });
    public static string S((string key, bool? value) attribute, params string[] contents) => Tag("s", new List<(string, bool?)> { attribute }, contents);
    public static string S(List<(string key, bool? value)> attributes) => Tag("s", attributes);
    public static string S(List<(string key, bool? value)> attributes, params string[] contents) => Tag("s", attributes, contents);

    public static string Samp() => Tag("samp");
    public static string Samp(params string[] contents) => Tag("samp", contents);
    public static string Samp((string key, string? value) attribute) => Tag("samp", new List<(string, string?)> { attribute });
    public static string Samp((string key, string? value) attribute, params string[] contents) => Tag("samp", new List<(string, string?)> { attribute }, contents);
    public static string Samp(List<(string key, string? value)> attributes) => Tag("samp", attributes);
    public static string Samp(List<(string key, string? value)> attributes, params string[] contents) => Tag("samp", attributes, contents);
    public static string Samp((string key, bool? value) attribute) => Tag("samp", new List<(string, bool?)> { attribute });
    public static string Samp((string key, bool? value) attribute, params string[] contents) => Tag("samp", new List<(string, bool?)> { attribute }, contents);
    public static string Samp(List<(string key, bool? value)> attributes) => Tag("samp", attributes);
    public static string Samp(List<(string key, bool? value)> attributes, params string[] contents) => Tag("samp", attributes, contents);

    public static string Script() => Tag("script");
    public static string Script(params string[] contents) => Tag("script", contents);
    public static string Script((string key, string? value) attribute) => Tag("script", new List<(string, string?)> { attribute });
    public static string Script((string key, string? value) attribute, params string[] contents) => Tag("script", new List<(string, string?)> { attribute }, contents);
    public static string Script(List<(string key, string? value)> attributes) => Tag("script", attributes);
    public static string Script(List<(string key, string? value)> attributes, params string[] contents) => Tag("script", attributes, contents);
    public static string Script((string key, bool? value) attribute) => Tag("script", new List<(string, bool?)> { attribute });
    public static string Script((string key, bool? value) attribute, params string[] contents) => Tag("script", new List<(string, bool?)> { attribute }, contents);
    public static string Script(List<(string key, bool? value)> attributes) => Tag("script", attributes);
    public static string Script(List<(string key, bool? value)> attributes, params string[] contents) => Tag("script", attributes, contents);

    public static string Search() => Tag("search");
    public static string Search(params string[] contents) => Tag("search", contents);
    public static string Search((string key, string? value) attribute) => Tag("search", new List<(string, string?)> { attribute });
    public static string Search((string key, string? value) attribute, params string[] contents) => Tag("search", new List<(string, string?)> { attribute }, contents);
    public static string Search(List<(string key, string? value)> attributes) => Tag("search", attributes);
    public static string Search(List<(string key, string? value)> attributes, params string[] contents) => Tag("search", attributes, contents);
    public static string Search((string key, bool? value) attribute) => Tag("search", new List<(string, bool?)> { attribute });
    public static string Search((string key, bool? value) attribute, params string[] contents) => Tag("search", new List<(string, bool?)> { attribute }, contents);
    public static string Search(List<(string key, bool? value)> attributes) => Tag("search", attributes);
    public static string Search(List<(string key, bool? value)> attributes, params string[] contents) => Tag("search", attributes, contents);

    public static string Section() => Tag("section");
    public static string Section(params string[] contents) => Tag("section", contents);
    public static string Section((string key, string? value) attribute) => Tag("section", new List<(string, string?)> { attribute });
    public static string Section((string key, string? value) attribute, params string[] contents) => Tag("section", new List<(string, string?)> { attribute }, contents);
    public static string Section(List<(string key, string? value)> attributes) => Tag("section", attributes);
    public static string Section(List<(string key, string? value)> attributes, params string[] contents) => Tag("section", attributes, contents);
    public static string Section((string key, bool? value) attribute) => Tag("section", new List<(string, bool?)> { attribute });
    public static string Section((string key, bool? value) attribute, params string[] contents) => Tag("section", new List<(string, bool?)> { attribute }, contents);
    public static string Section(List<(string key, bool? value)> attributes) => Tag("section", attributes);
    public static string Section(List<(string key, bool? value)> attributes, params string[] contents) => Tag("section", attributes, contents);

    public static string Select() => Tag("select");
    public static string Select(params string[] contents) => Tag("select", contents);
    public static string Select((string key, string? value) attribute) => Tag("select", new List<(string, string?)> { attribute });
    public static string Select((string key, string? value) attribute, params string[] contents) => Tag("select", new List<(string, string?)> { attribute }, contents);
    public static string Select(List<(string key, string? value)> attributes) => Tag("select", attributes);
    public static string Select(List<(string key, string? value)> attributes, params string[] contents) => Tag("select", attributes, contents);
    public static string Select((string key, bool? value) attribute) => Tag("select", new List<(string, bool?)> { attribute });
    public static string Select((string key, bool? value) attribute, params string[] contents) => Tag("select", new List<(string, bool?)> { attribute }, contents);
    public static string Select(List<(string key, bool? value)> attributes) => Tag("select", attributes);
    public static string Select(List<(string key, bool? value)> attributes, params string[] contents) => Tag("select", attributes, contents);

    public static string Slot() => Tag("slot");
    public static string Slot(params string[] contents) => Tag("slot", contents);
    public static string Slot((string key, string? value) attribute) => Tag("slot", new List<(string, string?)> { attribute });
    public static string Slot((string key, string? value) attribute, params string[] contents) => Tag("slot", new List<(string, string?)> { attribute }, contents);
    public static string Slot(List<(string key, string? value)> attributes) => Tag("slot", attributes);
    public static string Slot(List<(string key, string? value)> attributes, params string[] contents) => Tag("slot", attributes, contents);
    public static string Slot((string key, bool? value) attribute) => Tag("slot", new List<(string, bool?)> { attribute });
    public static string Slot((string key, bool? value) attribute, params string[] contents) => Tag("slot", new List<(string, bool?)> { attribute }, contents);
    public static string Slot(List<(string key, bool? value)> attributes) => Tag("slot", attributes);
    public static string Slot(List<(string key, bool? value)> attributes, params string[] contents) => Tag("slot", attributes, contents);

    public static string Small() => Tag("small");
    public static string Small(params string[] contents) => Tag("small", contents);
    public static string Small((string key, string? value) attribute) => Tag("small", new List<(string, string?)> { attribute });
    public static string Small((string key, string? value) attribute, params string[] contents) => Tag("small", new List<(string, string?)> { attribute }, contents);
    public static string Small(List<(string key, string? value)> attributes) => Tag("small", attributes);
    public static string Small(List<(string key, string? value)> attributes, params string[] contents) => Tag("small", attributes, contents);
    public static string Small((string key, bool? value) attribute) => Tag("small", new List<(string, bool?)> { attribute });
    public static string Small((string key, bool? value) attribute, params string[] contents) => Tag("small", new List<(string, bool?)> { attribute }, contents);
    public static string Small(List<(string key, bool? value)> attributes) => Tag("small", attributes);
    public static string Small(List<(string key, bool? value)> attributes, params string[] contents) => Tag("small", attributes, contents);

    public static string Span() => Tag("span");
    public static string Span(params string[] contents) => Tag("span", contents);
    public static string Span((string key, string? value) attribute) => Tag("span", new List<(string, string?)> { attribute });
    public static string Span((string key, string? value) attribute, params string[] contents) => Tag("span", new List<(string, string?)> { attribute }, contents);
    public static string Span(List<(string key, string? value)> attributes) => Tag("span", attributes);
    public static string Span(List<(string key, string? value)> attributes, params string[] contents) => Tag("span", attributes, contents);
    public static string Span((string key, bool? value) attribute) => Tag("span", new List<(string, bool?)> { attribute });
    public static string Span((string key, bool? value) attribute, params string[] contents) => Tag("span", new List<(string, bool?)> { attribute }, contents);
    public static string Span(List<(string key, bool? value)> attributes) => Tag("span", attributes);
    public static string Span(List<(string key, bool? value)> attributes, params string[] contents) => Tag("span", attributes, contents);

    public static string Strong() => Tag("strong");
    public static string Strong(params string[] contents) => Tag("strong", contents);
    public static string Strong((string key, string? value) attribute) => Tag("strong", new List<(string, string?)> { attribute });
    public static string Strong((string key, string? value) attribute, params string[] contents) => Tag("strong", new List<(string, string?)> { attribute }, contents);
    public static string Strong(List<(string key, string? value)> attributes) => Tag("strong", attributes);
    public static string Strong(List<(string key, string? value)> attributes, params string[] contents) => Tag("strong", attributes, contents);
    public static string Strong((string key, bool? value) attribute) => Tag("strong", new List<(string, bool?)> { attribute });
    public static string Strong((string key, bool? value) attribute, params string[] contents) => Tag("strong", new List<(string, bool?)> { attribute }, contents);
    public static string Strong(List<(string key, bool? value)> attributes) => Tag("strong", attributes);
    public static string Strong(List<(string key, bool? value)> attributes, params string[] contents) => Tag("strong", attributes, contents);

    public static string Style() => Tag("style");
    public static string Style(params string[] contents) => Tag("style", contents);
    public static string Style((string key, string? value) attribute) => Tag("style", new List<(string, string?)> { attribute });
    public static string Style((string key, string? value) attribute, params string[] contents) => Tag("style", new List<(string, string?)> { attribute }, contents);
    public static string Style(List<(string key, string? value)> attributes) => Tag("style", attributes);
    public static string Style(List<(string key, string? value)> attributes, params string[] contents) => Tag("style", attributes, contents);
    public static string Style((string key, bool? value) attribute) => Tag("style", new List<(string, bool?)> { attribute });
    public static string Style((string key, bool? value) attribute, params string[] contents) => Tag("style", new List<(string, bool?)> { attribute }, contents);
    public static string Style(List<(string key, bool? value)> attributes) => Tag("style", attributes);
    public static string Style(List<(string key, bool? value)> attributes, params string[] contents) => Tag("style", attributes, contents);

    public static string Sub() => Tag("sub");
    public static string Sub(params string[] contents) => Tag("sub", contents);
    public static string Sub((string key, string? value) attribute) => Tag("sub", new List<(string, string?)> { attribute });
    public static string Sub((string key, string? value) attribute, params string[] contents) => Tag("sub", new List<(string, string?)> { attribute }, contents);
    public static string Sub(List<(string key, string? value)> attributes) => Tag("sub", attributes);
    public static string Sub(List<(string key, string? value)> attributes, params string[] contents) => Tag("sub", attributes, contents);
    public static string Sub((string key, bool? value) attribute) => Tag("sub", new List<(string, bool?)> { attribute });
    public static string Sub((string key, bool? value) attribute, params string[] contents) => Tag("sub", new List<(string, bool?)> { attribute }, contents);
    public static string Sub(List<(string key, bool? value)> attributes) => Tag("sub", attributes);
    public static string Sub(List<(string key, bool? value)> attributes, params string[] contents) => Tag("sub", attributes, contents);

    public static string Summary() => Tag("summary");
    public static string Summary(params string[] contents) => Tag("summary", contents);
    public static string Summary((string key, string? value) attribute) => Tag("summary", new List<(string, string?)> { attribute });
    public static string Summary((string key, string? value) attribute, params string[] contents) => Tag("summary", new List<(string, string?)> { attribute }, contents);
    public static string Summary(List<(string key, string? value)> attributes) => Tag("summary", attributes);
    public static string Summary(List<(string key, string? value)> attributes, params string[] contents) => Tag("summary", attributes, contents);
    public static string Summary((string key, bool? value) attribute) => Tag("summary", new List<(string, bool?)> { attribute });
    public static string Summary((string key, bool? value) attribute, params string[] contents) => Tag("summary", new List<(string, bool?)> { attribute }, contents);
    public static string Summary(List<(string key, bool? value)> attributes) => Tag("summary", attributes);
    public static string Summary(List<(string key, bool? value)> attributes, params string[] contents) => Tag("summary", attributes, contents);

    public static string Sup() => Tag("sup");
    public static string Sup(params string[] contents) => Tag("sup", contents);
    public static string Sup((string key, string? value) attribute) => Tag("sup", new List<(string, string?)> { attribute });
    public static string Sup((string key, string? value) attribute, params string[] contents) => Tag("sup", new List<(string, string?)> { attribute }, contents);
    public static string Sup(List<(string key, string? value)> attributes) => Tag("sup", attributes);
    public static string Sup(List<(string key, string? value)> attributes, params string[] contents) => Tag("sup", attributes, contents);
    public static string Sup((string key, bool? value) attribute) => Tag("sup", new List<(string, bool?)> { attribute });
    public static string Sup((string key, bool? value) attribute, params string[] contents) => Tag("sup", new List<(string, bool?)> { attribute }, contents);
    public static string Sup(List<(string key, bool? value)> attributes) => Tag("sup", attributes);
    public static string Sup(List<(string key, bool? value)> attributes, params string[] contents) => Tag("sup", attributes, contents);

    public static string Table() => Tag("table");
    public static string Table(params string[] contents) => Tag("table", contents);
    public static string Table((string key, string? value) attribute) => Tag("table", new List<(string, string?)> { attribute });
    public static string Table((string key, string? value) attribute, params string[] contents) => Tag("table", new List<(string, string?)> { attribute }, contents);
    public static string Table(List<(string key, string? value)> attributes) => Tag("table", attributes);
    public static string Table(List<(string key, string? value)> attributes, params string[] contents) => Tag("table", attributes, contents);
    public static string Table((string key, bool? value) attribute) => Tag("table", new List<(string, bool?)> { attribute });
    public static string Table((string key, bool? value) attribute, params string[] contents) => Tag("table", new List<(string, bool?)> { attribute }, contents);
    public static string Table(List<(string key, bool? value)> attributes) => Tag("table", attributes);
    public static string Table(List<(string key, bool? value)> attributes, params string[] contents) => Tag("table", attributes, contents);

    public static string Tbody() => Tag("tbody");
    public static string Tbody(params string[] contents) => Tag("tbody", contents);
    public static string Tbody((string key, string? value) attribute) => Tag("tbody", new List<(string, string?)> { attribute });
    public static string Tbody((string key, string? value) attribute, params string[] contents) => Tag("tbody", new List<(string, string?)> { attribute }, contents);
    public static string Tbody(List<(string key, string? value)> attributes) => Tag("tbody", attributes);
    public static string Tbody(List<(string key, string? value)> attributes, params string[] contents) => Tag("tbody", attributes, contents);
    public static string Tbody((string key, bool? value) attribute) => Tag("tbody", new List<(string, bool?)> { attribute });
    public static string Tbody((string key, bool? value) attribute, params string[] contents) => Tag("tbody", new List<(string, bool?)> { attribute }, contents);
    public static string Tbody(List<(string key, bool? value)> attributes) => Tag("tbody", attributes);
    public static string Tbody(List<(string key, bool? value)> attributes, params string[] contents) => Tag("tbody", attributes, contents);

    public static string Td() => Tag("td");
    public static string Td(params string[] contents) => Tag("td", contents);
    public static string Td((string key, string? value) attribute) => Tag("td", new List<(string, string?)> { attribute });
    public static string Td((string key, string? value) attribute, params string[] contents) => Tag("td", new List<(string, string?)> { attribute }, contents);
    public static string Td(List<(string key, string? value)> attributes) => Tag("td", attributes);
    public static string Td(List<(string key, string? value)> attributes, params string[] contents) => Tag("td", attributes, contents);
    public static string Td((string key, bool? value) attribute) => Tag("td", new List<(string, bool?)> { attribute });
    public static string Td((string key, bool? value) attribute, params string[] contents) => Tag("td", new List<(string, bool?)> { attribute }, contents);
    public static string Td(List<(string key, bool? value)> attributes) => Tag("td", attributes);
    public static string Td(List<(string key, bool? value)> attributes, params string[] contents) => Tag("td", attributes, contents);

    public static string Textarea() => Tag("textarea");
    public static string Textarea(params string[] contents) => Tag("textarea", contents);
    public static string Textarea((string key, string? value) attribute) => Tag("textarea", new List<(string, string?)> { attribute });
    public static string Textarea((string key, string? value) attribute, params string[] contents) => Tag("textarea", new List<(string, string?)> { attribute }, contents);
    public static string Textarea(List<(string key, string? value)> attributes) => Tag("textarea", attributes);
    public static string Textarea(List<(string key, string? value)> attributes, params string[] contents) => Tag("textarea", attributes, contents);
    public static string Textarea((string key, bool? value) attribute) => Tag("textarea", new List<(string, bool?)> { attribute });
    public static string Textarea((string key, bool? value) attribute, params string[] contents) => Tag("textarea", new List<(string, bool?)> { attribute }, contents);
    public static string Textarea(List<(string key, bool? value)> attributes) => Tag("textarea", attributes);
    public static string Textarea(List<(string key, bool? value)> attributes, params string[] contents) => Tag("textarea", attributes, contents);

    public static string Tfoot() => Tag("tfoot");
    public static string Tfoot(params string[] contents) => Tag("tfoot", contents);
    public static string Tfoot((string key, string? value) attribute) => Tag("tfoot", new List<(string, string?)> { attribute });
    public static string Tfoot((string key, string? value) attribute, params string[] contents) => Tag("tfoot", new List<(string, string?)> { attribute }, contents);
    public static string Tfoot(List<(string key, string? value)> attributes) => Tag("tfoot", attributes);
    public static string Tfoot(List<(string key, string? value)> attributes, params string[] contents) => Tag("tfoot", attributes, contents);
    public static string Tfoot((string key, bool? value) attribute) => Tag("tfoot", new List<(string, bool?)> { attribute });
    public static string Tfoot((string key, bool? value) attribute, params string[] contents) => Tag("tfoot", new List<(string, bool?)> { attribute }, contents);
    public static string Tfoot(List<(string key, bool? value)> attributes) => Tag("tfoot", attributes);
    public static string Tfoot(List<(string key, bool? value)> attributes, params string[] contents) => Tag("tfoot", attributes, contents);

    public static string Th() => Tag("th");
    public static string Th(params string[] contents) => Tag("th", contents);
    public static string Th((string key, string? value) attribute) => Tag("th", new List<(string, string?)> { attribute });
    public static string Th((string key, string? value) attribute, params string[] contents) => Tag("th", new List<(string, string?)> { attribute }, contents);
    public static string Th(List<(string key, string? value)> attributes) => Tag("th", attributes);
    public static string Th(List<(string key, string? value)> attributes, params string[] contents) => Tag("th", attributes, contents);
    public static string Th((string key, bool? value) attribute) => Tag("th", new List<(string, bool?)> { attribute });
    public static string Th((string key, bool? value) attribute, params string[] contents) => Tag("th", new List<(string, bool?)> { attribute }, contents);
    public static string Th(List<(string key, bool? value)> attributes) => Tag("th", attributes);
    public static string Th(List<(string key, bool? value)> attributes, params string[] contents) => Tag("th", attributes, contents);

    public static string Thead() => Tag("thead");
    public static string Thead(params string[] contents) => Tag("thead", contents);
    public static string Thead((string key, string? value) attribute) => Tag("thead", new List<(string, string?)> { attribute });
    public static string Thead((string key, string? value) attribute, params string[] contents) => Tag("thead", new List<(string, string?)> { attribute }, contents);
    public static string Thead(List<(string key, string? value)> attributes) => Tag("thead", attributes);
    public static string Thead(List<(string key, string? value)> attributes, params string[] contents) => Tag("thead", attributes, contents);
    public static string Thead((string key, bool? value) attribute) => Tag("thead", new List<(string, bool?)> { attribute });
    public static string Thead((string key, bool? value) attribute, params string[] contents) => Tag("thead", new List<(string, bool?)> { attribute }, contents);
    public static string Thead(List<(string key, bool? value)> attributes) => Tag("thead", attributes);
    public static string Thead(List<(string key, bool? value)> attributes, params string[] contents) => Tag("thead", attributes, contents);

    public static string Time() => Tag("time");
    public static string Time(params string[] contents) => Tag("time", contents);
    public static string Time((string key, string? value) attribute) => Tag("time", new List<(string, string?)> { attribute });
    public static string Time((string key, string? value) attribute, params string[] contents) => Tag("time", new List<(string, string?)> { attribute }, contents);
    public static string Time(List<(string key, string? value)> attributes) => Tag("time", attributes);
    public static string Time(List<(string key, string? value)> attributes, params string[] contents) => Tag("time", attributes, contents);
    public static string Time((string key, bool? value) attribute) => Tag("time", new List<(string, bool?)> { attribute });
    public static string Time((string key, bool? value) attribute, params string[] contents) => Tag("time", new List<(string, bool?)> { attribute }, contents);
    public static string Time(List<(string key, bool? value)> attributes) => Tag("time", attributes);
    public static string Time(List<(string key, bool? value)> attributes, params string[] contents) => Tag("time", attributes, contents);

    public static string Title() => Tag("title");
    public static string Title(params string[] contents) => Tag("title", contents);
    public static string Title((string key, string? value) attribute) => Tag("title", new List<(string, string?)> { attribute });
    public static string Title((string key, string? value) attribute, params string[] contents) => Tag("title", new List<(string, string?)> { attribute }, contents);
    public static string Title(List<(string key, string? value)> attributes) => Tag("title", attributes);
    public static string Title(List<(string key, string? value)> attributes, params string[] contents) => Tag("title", attributes, contents);
    public static string Title((string key, bool? value) attribute) => Tag("title", new List<(string, bool?)> { attribute });
    public static string Title((string key, bool? value) attribute, params string[] contents) => Tag("title", new List<(string, bool?)> { attribute }, contents);
    public static string Title(List<(string key, bool? value)> attributes) => Tag("title", attributes);
    public static string Title(List<(string key, bool? value)> attributes, params string[] contents) => Tag("title", attributes, contents);

    public static string Tr() => Tag("tr");
    public static string Tr(params string[] contents) => Tag("tr", contents);
    public static string Tr((string key, string? value) attribute) => Tag("tr", new List<(string, string?)> { attribute });
    public static string Tr((string key, string? value) attribute, params string[] contents) => Tag("tr", new List<(string, string?)> { attribute }, contents);
    public static string Tr(List<(string key, string? value)> attributes) => Tag("tr", attributes);
    public static string Tr(List<(string key, string? value)> attributes, params string[] contents) => Tag("tr", attributes, contents);
    public static string Tr((string key, bool? value) attribute) => Tag("tr", new List<(string, bool?)> { attribute });
    public static string Tr((string key, bool? value) attribute, params string[] contents) => Tag("tr", new List<(string, bool?)> { attribute }, contents);
    public static string Tr(List<(string key, bool? value)> attributes) => Tag("tr", attributes);
    public static string Tr(List<(string key, bool? value)> attributes, params string[] contents) => Tag("tr", attributes, contents);

    public static string U() => Tag("u");
    public static string U(params string[] contents) => Tag("u", contents);
    public static string U((string key, string? value) attribute) => Tag("u", new List<(string, string?)> { attribute });
    public static string U((string key, string? value) attribute, params string[] contents) => Tag("u", new List<(string, string?)> { attribute }, contents);
    public static string U(List<(string key, string? value)> attributes) => Tag("u", attributes);
    public static string U(List<(string key, string? value)> attributes, params string[] contents) => Tag("u", attributes, contents);
    public static string U((string key, bool? value) attribute) => Tag("u", new List<(string, bool?)> { attribute });
    public static string U((string key, bool? value) attribute, params string[] contents) => Tag("u", new List<(string, bool?)> { attribute }, contents);
    public static string U(List<(string key, bool? value)> attributes) => Tag("u", attributes);
    public static string U(List<(string key, bool? value)> attributes, params string[] contents) => Tag("u", attributes, contents);

    public static string Ul() => Tag("ul");
    public static string Ul(params string[] contents) => Tag("ul", contents);
    public static string Ul((string key, string? value) attribute) => Tag("ul", new List<(string, string?)> { attribute });
    public static string Ul((string key, string? value) attribute, params string[] contents) => Tag("ul", new List<(string, string?)> { attribute }, contents);
    public static string Ul(List<(string key, string? value)> attributes) => Tag("ul", attributes);
    public static string Ul(List<(string key, string? value)> attributes, params string[] contents) => Tag("ul", attributes, contents);
    public static string Ul((string key, bool? value) attribute) => Tag("ul", new List<(string, bool?)> { attribute });
    public static string Ul((string key, bool? value) attribute, params string[] contents) => Tag("ul", new List<(string, bool?)> { attribute }, contents);
    public static string Ul(List<(string key, bool? value)> attributes) => Tag("ul", attributes);
    public static string Ul(List<(string key, bool? value)> attributes, params string[] contents) => Tag("ul", attributes, contents);

    public static string Var() => Tag("var");
    public static string Var(params string[] contents) => Tag("var", contents);
    public static string Var((string key, string? value) attribute) => Tag("var", new List<(string, string?)> { attribute });
    public static string Var((string key, string? value) attribute, params string[] contents) => Tag("var", new List<(string, string?)> { attribute }, contents);
    public static string Var(List<(string key, string? value)> attributes) => Tag("var", attributes);
    public static string Var(List<(string key, string? value)> attributes, params string[] contents) => Tag("var", attributes, contents);
    public static string Var((string key, bool? value) attribute) => Tag("var", new List<(string, bool?)> { attribute });
    public static string Var((string key, bool? value) attribute, params string[] contents) => Tag("var", new List<(string, bool?)> { attribute }, contents);
    public static string Var(List<(string key, bool? value)> attributes) => Tag("var", attributes);
    public static string Var(List<(string key, bool? value)> attributes, params string[] contents) => Tag("var", attributes, contents);

    public static string Video() => Tag("video");
    public static string Video(params string[] contents) => Tag("video", contents);
    public static string Video((string key, string? value) attribute) => Tag("video", new List<(string, string?)> { attribute });
    public static string Video((string key, string? value) attribute, params string[] contents) => Tag("video", new List<(string, string?)> { attribute }, contents);
    public static string Video(List<(string key, string? value)> attributes) => Tag("video", attributes);
    public static string Video(List<(string key, string? value)> attributes, params string[] contents) => Tag("video", attributes, contents);
    public static string Video((string key, bool? value) attribute) => Tag("video", new List<(string, bool?)> { attribute });
    public static string Video((string key, bool? value) attribute, params string[] contents) => Tag("video", new List<(string, bool?)> { attribute }, contents);
    public static string Video(List<(string key, bool? value)> attributes) => Tag("video", attributes);
    public static string Video(List<(string key, bool? value)> attributes, params string[] contents) => Tag("video", attributes, contents);

    public static string Iframe() => Tag("iframe");
    public static string Iframe(params string[] contents) => Tag("iframe", contents);
    public static string Iframe((string key, string? value) attribute) => Tag("iframe", new List<(string, string?)> { attribute });
    public static string Iframe((string key, string? value) attribute, params string[] contents) => Tag("iframe", new List<(string, string?)> { attribute }, contents);
    public static string Iframe(List<(string key, string? value)> attributes) => Tag("iframe", attributes);
    public static string Iframe(List<(string key, string? value)> attributes, params string[] contents) => Tag("iframe", attributes, contents);
    public static string Iframe((string key, bool? value) attribute) => Tag("iframe", new List<(string, bool?)> { attribute });
    public static string Iframe((string key, bool? value) attribute, params string[] contents) => Tag("iframe", new List<(string, bool?)> { attribute }, contents);
    public static string Iframe(List<(string key, bool? value)> attributes) => Tag("iframe", attributes);
    public static string Iframe(List<(string key, bool? value)> attributes, params string[] contents) => Tag("iframe", attributes, contents);

    public static string Template() => Tag("template");
    public static string Template(params string[] contents) => Tag("template", contents);
    public static string Template((string key, string? value) attribute) => Tag("template", new List<(string, string?)> { attribute });
    public static string Template((string key, string? value) attribute, params string[] contents) => Tag("template", new List<(string, string?)> { attribute }, contents);
    public static string Template(List<(string key, string? value)> attributes) => Tag("template", attributes);
    public static string Template(List<(string key, string? value)> attributes, params string[] contents) => Tag("template", attributes, contents);
    public static string Template((string key, bool? value) attribute) => Tag("template", new List<(string, bool?)> { attribute });
    public static string Template((string key, bool? value) attribute, params string[] contents) => Tag("template", new List<(string, bool?)> { attribute }, contents);
    public static string Template(List<(string key, bool? value)> attributes) => Tag("template", attributes);
    public static string Template(List<(string key, bool? value)> attributes, params string[] contents) => Tag("template", attributes, contents);


    // Void elements (TagSingle)
    public static string Area() => TagSingle("area");
    public static string Area((string key, string? value) attribute) => TagSingle("area", new List<(string, string?)> { attribute });
    public static string Area(List<(string key, string? value)> attributes) => TagSingle("area", attributes);
    public static string Area((string key, bool? value) attribute) => TagSingle("area", new List<(string, bool?)> { attribute });
    public static string Area(List<(string key, bool? value)> attributes) => TagSingle("area", attributes);

    public static string Base() => TagSingle("base");
    public static string Base((string key, string? value) attribute) => TagSingle("base", new List<(string, string?)> { attribute });
    public static string Base(List<(string key, string? value)> attributes) => TagSingle("base", attributes);
    public static string Base((string key, bool? value) attribute) => TagSingle("base", new List<(string, bool?)> { attribute });
    public static string Base(List<(string key, bool? value)> attributes) => TagSingle("base", attributes);

    public static string Br() => TagSingle("br");
    public static string Br((string key, string? value) attribute) => TagSingle("br", new List<(string, string?)> { attribute });
    public static string Br(List<(string key, string? value)> attributes) => TagSingle("br", attributes);
    public static string Br((string key, bool? value) attribute) => TagSingle("br", new List<(string, bool?)> { attribute });
    public static string Br(List<(string key, bool? value)> attributes) => TagSingle("br", attributes);

    public static string Col() => TagSingle("col");
    public static string Col((string key, string? value) attribute) => TagSingle("col", new List<(string, string?)> { attribute });
    public static string Col(List<(string key, string? value)> attributes) => TagSingle("col", attributes);
    public static string Col((string key, bool? value) attribute) => TagSingle("col", new List<(string, bool?)> { attribute });
    public static string Col(List<(string key, bool? value)> attributes) => TagSingle("col", attributes);

    public static string Embed() => TagSingle("embed");
    public static string Embed((string key, string? value) attribute) => TagSingle("embed", new List<(string, string?)> { attribute });
    public static string Embed(List<(string key, string? value)> attributes) => TagSingle("embed", attributes);
    public static string Embed((string key, bool? value) attribute) => TagSingle("embed", new List<(string, bool?)> { attribute });
    public static string Embed(List<(string key, bool? value)> attributes) => TagSingle("embed", attributes);

    public static string Hr() => TagSingle("hr");
    public static string Hr((string key, string? value) attribute) => TagSingle("hr", new List<(string, string?)> { attribute });
    public static string Hr(List<(string key, string? value)> attributes) => TagSingle("hr", attributes);
    public static string Hr((string key, bool? value) attribute) => TagSingle("hr", new List<(string, bool?)> { attribute });
    public static string Hr(List<(string key, bool? value)> attributes) => TagSingle("hr", attributes);

    public static string Img() => TagSingle("img");
    public static string Img((string key, string? value) attribute) => TagSingle("img", new List<(string, string?)> { attribute });
    public static string Img(List<(string key, string? value)> attributes) => TagSingle("img", attributes);
    public static string Img((string key, bool? value) attribute) => TagSingle("img", new List<(string, bool?)> { attribute });
    public static string Img(List<(string key, bool? value)> attributes) => TagSingle("img", attributes);

    public static string Input() => TagSingle("input");
    public static string Input((string key, string? value) attribute) => TagSingle("input", new List<(string, string?)> { attribute });
    public static string Input(List<(string key, string? value)> attributes) => TagSingle("input", attributes);
    public static string Input((string key, bool? value) attribute) => TagSingle("input", new List<(string, bool?)> { attribute });
    public static string Input(List<(string key, bool? value)> attributes) => TagSingle("input", attributes);

    public static string Link() => TagSingle("link");
    public static string Link((string key, string? value) attribute) => TagSingle("link", new List<(string, string?)> { attribute });
    public static string Link(List<(string key, string? value)> attributes) => TagSingle("link", attributes);
    public static string Link((string key, bool? value) attribute) => TagSingle("link", new List<(string, bool?)> { attribute });
    public static string Link(List<(string key, bool? value)> attributes) => TagSingle("link", attributes);

    public static string Meta() => TagSingle("meta");
    public static string Meta((string key, string? value) attribute) => TagSingle("meta", new List<(string, string?)> { attribute });
    public static string Meta(List<(string key, string? value)> attributes) => TagSingle("meta", attributes);
    public static string Meta((string key, bool? value) attribute) => TagSingle("meta", new List<(string, bool?)> { attribute });
    public static string Meta(List<(string key, bool? value)> attributes) => TagSingle("meta", attributes);

    public static string Source() => TagSingle("source");
    public static string Source((string key, string? value) attribute) => TagSingle("source", new List<(string, string?)> { attribute });
    public static string Source(List<(string key, string? value)> attributes) => TagSingle("source", attributes);
    public static string Source((string key, bool? value) attribute) => TagSingle("source", new List<(string, bool?)> { attribute });
    public static string Source(List<(string key, bool? value)> attributes) => TagSingle("source", attributes);

    public static string Track() => TagSingle("track");
    public static string Track((string key, string? value) attribute) => TagSingle("track", new List<(string, string?)> { attribute });
    public static string Track(List<(string key, string? value)> attributes) => TagSingle("track", attributes);
    public static string Track((string key, bool? value) attribute) => TagSingle("track", new List<(string, bool?)> { attribute });
    public static string Track(List<(string key, bool? value)> attributes) => TagSingle("track", attributes);

    public static string Wbr() => TagSingle("wbr");
    public static string Wbr((string key, string? value) attribute) => TagSingle("wbr", new List<(string, string?)> { attribute });
    public static string Wbr(List<(string key, string? value)> attributes) => TagSingle("wbr", attributes);
    public static string Wbr((string key, bool? value) attribute) => TagSingle("wbr", new List<(string, bool?)> { attribute });
    public static string Wbr(List<(string key, bool? value)> attributes) => TagSingle("wbr", attributes);

    // Contract
    private static string Tag(string tagName)
    {
        return $"<{tagName}></{tagName}>";
    }
    private static string TagSingle(string tagName)
    {
        return $"<{tagName}>";
    }

    private static string Tag(string tagName, List<(string key, string? value)> attributes)
    {
        return $"<{tagName}{GetAttributes(attributes)}></{tagName}>";
    }

    private static string Tag(string tagName, List<(string key, bool? value)> attributes)
    {
        return $"<{tagName}{GetAttributes(attributes)}></{tagName}>";
    }

    private static string TagSingle(string tagName, List<(string key, string? value)> attributes)
    {
        return $"<{tagName}{GetAttributes(attributes)}>";
    }

    private static string TagSingle(string tagName, List<(string key, bool? value)> attributes)
    {
        return $"<{tagName}{GetAttributes(attributes)}>";
    }

    private static string Tag(string tagName, params string[] content)
    {
        return $"<{tagName}>{GetContent(content)}</{tagName}>";
    }

    private static string Tag(string tagName, List<(string key, string? value)> attributes, params string[] content)
    {
        return $"<{tagName}{GetAttributes(attributes)}>{GetContent(content)}</{tagName}>";
    }

    private static string Tag(string tagName, List<(string key, bool? value)> attributes, params string[] content)
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

            if (value.ToLower() is "true")
            {
                result += $" {key}";
                continue;
            }

            if (value.ToLower() is "false")
            {
                continue;
            }

            result += $" {key}=\"{value}\"";
        }

        return result;
    }

    private static string GetAttributes(List<(string key, bool? value)> attributes)
    {
        string result = "";
        foreach ((string key, bool? value) in attributes)
        {
            if (value is null || value is true)
            {
                result += $" {key}";
            }
        }

        return result;
    }
}