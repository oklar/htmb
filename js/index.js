/**
 * HTMB - Hypertext Markdown Builder
 * A lightweight library for building HTML structures using functions
 */
(function (global) {
  const tagsVoid = [
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
    "source",
    "track",
    "wbr",
  ];

  const tags = [
    "a",
    "abbr",
    "address",
    "article",
    "aside",
    "audio",
    "b",
    "bdi",
    "bdo",
    "blockquote",
    "body",
    "button",
    "canvas",
    "caption",
    "cite",
    "code",
    "colgroup",
    "data",
    "datalist",
    "dd",
    "del",
    "details",
    "dfn",
    "dialog",
    "div",
    "dl",
    "dt",
    "em",
    "fieldset",
    "figcaption",
    "figure",
    "footer",
    "form",
    "h1",
    "head",
    "header",
    "hgroup",
    "html",
    "i",
    "ins",
    "kbd",
    "label",
    "legend",
    "li",
    "main",
    "map",
    "mark",
    "menu",
    "meter",
    "nav",
    "noscript",
    "object",
    "ol",
    "optgroup",
    "option",
    "output",
    "p",
    "picture",
    "pre",
    "progress",
    "q",
    "rp",
    "rt",
    "ruby",
    "s",
    "samp",
    "script",
    "search",
    "section",
    "select",
    "slot",
    "small",
    "span",
    "strong",
    "style",
    "sub",
    "summary",
    "sup",
    "table",
    "tbody",
    "td",
    "textarea",
    "tfoot",
    "th",
    "thead",
    "time",
    "title",
    "tr",
    "u",
    "ul",
    "var",
    "video",
    "h2",
    "h3",
    "h4",
    "h5",
    "h6",
    "iframe",
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

      if (tagsVoid.includes(tag) && children.length === 0) {
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

  tags.forEach((tag) => {
    htmb[tag] = createElementFunction(tag);
  });

  if (isBrowser) {
    global.__htmb = htmb;
  }

  if (typeof module !== "undefined" && module.exports) {
    module.exports = htmb;
  }
})(typeof window !== "undefined" ? window : global);
