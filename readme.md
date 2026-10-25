# HTMB - Hypertext Markup Builder

A minimalistic library for building HTML structures using pure functions. HTMB provides a clean, simple API for generating HTML for as many programming languages as possible.


## Implementations

HTMB is available in multiple languages:

- [C](c/)
- [C#](cs/HtmbLibrary/)
- [JavaScript](js/)
- [...?](https://github.com/oklar/htmb/pulls)

All of them share one tag list and one set of test cases, in [documentation](documentation/).

## Core Concept

HTMB uses a functional approach to HTML generation, representing elements as function calls:

```
// Pseudocode example
div(
  h1("Hello World"),
  p("Welcome to HTMB")
)
```

This produces HTML like:

```html
<div>
  <h1>Hello World</h1>
  <p>Welcome to HTMB</p>
</div>
```

## Releasing

Each library is released on its own by pushing a tag. Bump the version in the library's file, merge it to `main`, then tag that commit:

| Library | Version lives in | Tag | Publishes to |
| --- | --- | --- | --- |
| C | `c/library.json` | `c-v2.0.0` | Nothing to upload: PlatformIO users pin the tag in `lib_deps` |
| C# | `cs/HtmbLibrary/HtmbLibrary.csproj` | `cs-v2.1.0` | [NuGet](https://www.nuget.org/packages/htmb) |
| JavaScript | `js/package/package.json` | `js-v1.1.0` | [npm](https://www.npmjs.com/package/htmb) |

```bash
git tag -a js-v1.1.0 -m "htmb 1.1.0 for JavaScript"
```

```bash
git push origin js-v1.1.0
```

For `cs-v*` and `js-v*` tags, the [release workflow](.github/workflows/release.yml) checks that the tag is on `main` and matches the version, runs the tests, then publishes. It uses trusted publishing, so the repo holds no API keys. That needs a one-time setup on each registry:

- **npm:** on npmjs.com, open the `htmb` package's settings, add a trusted publisher for GitHub Actions with user `oklar`, repository `htmb` and workflow file `release.yml`, and tick **npm publish** under allowed actions. (Without it, npm only allows staged publishes, which wait for you to approve them.)
- **NuGet:** on nuget.org, open **Trusted Publishing** from your username menu and add a policy with repository owner `oklar`, repository `htmb` and workflow file `release.yml`.

## License

MIT
