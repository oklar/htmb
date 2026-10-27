# Shared tag list and test cases

The files here are used by every implementation, so they all provide the same tags and return the same HTML.

## html.json

The HTML tags each implementation provides, taken from the [HTML specification](https://html.spec.whatwg.org/multipage/syntax.html):

- `tagsVoid`: [void elements](https://html.spec.whatwg.org/multipage/syntax.html#void-elements), which close themselves, like `<br/>`.
- `tags`: [every other element](https://html.spec.whatwg.org/dev/indices.html#index).

The tag functions in each library are generated from this file. To add or remove a tag, edit `html.json`, then run these from the repo root:

```bash
gcc c/generate_html.c -o generate_html
```

```bash
./generate_html documentation/html.json c/include/htmb.h
```

```bash
dotnet run --project cs/HtmbSolution -- documentation/html.json cs/HtmbLibrary/Htmb.cs
```

```bash
node js/package/generate.js
```

```bash
node c/tests/generate_cases.js
```

Each generator only rewrites the lines between its two marker comments. `generate.js` writes the tags into both `index.js` and the TypeScript types in `index.d.ts`, and also rebuilds `htmb.umd.js` and the ES module `index.mjs` from `index.js`, so run it after any change to `index.js` as well. CI fails if a generated file is out of date.

## test-cases.json

Cases that every implementation must pass with exactly the same HTML. The C, C# and JavaScript tests each run them, and also check every tag in `html.json` on its own. After editing this file, run `node c/tests/generate_cases.js` to rebuild the C version of the cases.
