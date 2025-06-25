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

  const htmlTags = [
    "html",
    "head",
    "title",
    "base",
    "link",
    "meta",
    "style",

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

    "img",
    "audio",
    "video",
    "source",
    "track",
    "map",
    "area",

    "iframe",
    "embed",
    "object",
    "param",
    "picture",

    "script",
    "noscript",
    "canvas",

    "del",
    "ins",

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

    "details",
    "summary",
    "dialog",

    "slot",
    "template",
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

  const htmb = {};

  htmlTags.forEach((tag) => {
    htmb[tag] = createElementFunction(tag);
  });

  if (isBrowser) {
    global.__htmb = htmb;
  }

  if (typeof module !== "undefined" && module.exports) {
    module.exports = htmb;
  }
})(typeof window !== "undefined" ? window : global);
