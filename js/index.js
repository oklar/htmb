/**
 * HTMB - Hypertext Markdown Builder
 * A lightweight library for building HTML structures using functions
 */
(function (global) {
  const SELF_CLOSING_TAGS = [
    "area",
    "base",
    "br",
    "col",
    "embed",
    "hr",
    "img",
    "input",
    "link",
    "meta",
    "param",
    "source",
    "track",
    "wbr",
  ];

  const isBrowser = typeof window !== "undefined";
  const NodeClass = isBrowser ? Node : function () {};

  function createElementFunction(tag) {
    const fn = function (...args) {
      let attributes = {};
      let children = [];

      for (let i = 0; i < args.length; i++) {
        const arg = args[i];
        if (arg === null || arg === undefined) continue;

        if (
          i === 0 &&
          typeof arg === "object" &&
          !Array.isArray(arg) &&
          !(arg instanceof NodeClass) &&
          !arg.__isTagFunction
        ) {
          attributes = arg;
        } else {
          children.push(arg);
        }
      }

      let html = `<${tag}`;
      for (const [key, value] of Object.entries(attributes)) {
        if (value === true) {
          html += ` ${key}`;
        } else if (value !== false && value !== null && value !== undefined) {
          html += ` ${key}="${String(value).replace(/"/g, "&quot;")}"`;
        }
      }

      if (SELF_CLOSING_TAGS.includes(tag) && children.length === 0) {
        return `${html}/>`;
      }

      html += ">";
      for (const child of children) {
        if (child !== null && child !== undefined) {
          html += String(child);
        }
      }
      return html + `</${tag}>`;
    };

    fn.__isTagFunction = true;
    return fn;
  }

  function head(options = {}) {
    const {
      title = "",
      charset = "UTF-8",
      viewport = "width=device-width, initial-scale=1.0",
      stylesheets = [],
      scripts = [],
      meta = [],
      extraHeadContent = [],
    } = options;

    const headContent = [];

    if (charset) headContent.push(htmb.meta({ charset }));
    if (viewport)
      headContent.push(htmb.meta({ name: "viewport", content: viewport }));
    if (title) headContent.push(htmb.title(title));

    stylesheets.forEach((s) => {
      headContent.push(
        typeof s === "string"
          ? htmb.link({ rel: "stylesheet", href: s })
          : htmb.link({ rel: "stylesheet", ...s })
      );
    });

    meta.forEach((m) => headContent.push(htmb.meta(m)));
    extraHeadContent.forEach((content) => headContent.push(content));

    scripts.forEach((s) => {
      headContent.push(
        typeof s === "string" ? htmb.script({ src: s }) : htmb.script(s)
      );
    });

    return htmb.head(...headContent);
  }

  function list(items, renderer) {
    return items.map(renderer).join("");
  }

  function style(content) {
    return `<style>${content || ""}</style>`;
  }

  // HTML tags
  const htmlTags =
    /*global.window !== undefined
      ? Object.getOwnPropertyNames(global.window)
          .filter((n) => n.startsWith("HTML") && n.endsWith("Element"))
          .map((n) =>
            ((s) => ({ anchor: "a", paragraph: "p" }[s] || s))(
              n
                .replace(/^HTML/, "")
                .replace(/Element$/, "")
                .toLowerCase()
            )
          )
      : 
      */
    [
      // Document metadata
      "html",
      "head",
      "title",
      "base",
      "link",
      "meta",
      "style",

      // Sectioning elements
      "body",
      "article",
      "section",
      "nav",
      "aside",
      "h1",
      "h2",
      "h3",
      "h4",
      "h5",
      "h6",
      "header",
      "footer",
      "address",
      "main",

      // Text content
      "p",
      "hr",
      "pre",
      "blockquote",
      "ol",
      "ul",
      "li",
      "dl",
      "dt",
      "dd",
      "figure",
      "figcaption",
      "div",

      // Inline text semantics
      "a",
      "em",
      "strong",
      "small",
      "s",
      "cite",
      "q",
      "dfn",
      "abbr",
      "data",
      "time",
      "code",
      "var",
      "samp",
      "kbd",
      "sub",
      "sup",
      "i",
      "b",
      "u",
      "mark",
      "ruby",
      "rt",
      "rp",
      "bdi",
      "bdo",
      "span",
      "br",
      "wbr",

      // Image and multimedia
      "img",
      "audio",
      "video",
      "source",
      "track",
      "map",
      "area",

      // Embedded content
      "iframe",
      "embed",
      "object",
      "param",
      "picture",

      // Scripting
      "script",
      "noscript",
      "canvas",

      // Demarcating edits
      "del",
      "ins",

      // Table content
      "table",
      "caption",
      "colgroup",
      "col",
      "tbody",
      "thead",
      "tfoot",
      "tr",
      "td",
      "th",

      // Forms
      "form",
      "label",
      "input",
      "button",
      "select",
      "datalist",
      "optgroup",
      "option",
      "textarea",
      "output",
      "progress",
      "meter",
      "fieldset",
      "legend",

      // Interactive elements
      "details",
      "summary",
      "dialog",

      // Web Components
      "slot",
      "template",
    ];

  const htmb = {};

  htmlTags.forEach((tag) => {
    htmb[tag] = createElementFunction(tag);
  });

  htmb.list = list;
  htmb.head = head;
  htmb.style = style;

  if (isBrowser) {
    global.__htmb = htmb;
  }

  if (typeof module !== "undefined" && module.exports) {
    module.exports = htmb;
  }
})(typeof window !== "undefined" ? window : global);
