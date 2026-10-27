// Checked by `npm run test:types`, not run. It imports htmb by its package
// name, so tsc finds the types through package.json the way a user's would.
import htmb, { a, br, div, escape, input, p, var as variable } from "htmb";
import type { Attributes, Child, TagFunction } from "htmb";

const page: string = div(
  { class: "card", id: "main", tabindex: 0, hidden: false, title: null },
  htmb.h1("Title"),
  p("Count: ", 3),
  input({ type: "checkbox", checked: true }),
  br(),
  variable("x"),
  null,
  undefined
);
const empty: string = htmb.span() + htmb.template();
const escaped: string = escape("<b>") + escape(1) + escape(null) + htmb.escape(undefined);

const attributes: Attributes = { href: "/", "data-id": 7 };
const children: Child[] = ["a", 1, null];
const tag: TagFunction = htmb.li;
a(attributes, ...children);
tag(null, "text");

// @ts-expect-error attributes only go first
div("text", { class: "x" });
// @ts-expect-error a child is a string or a number
div(["a", "b"]);
// @ts-expect-error an attribute value is a string, number or boolean
div({ onclick: () => {} });
// @ts-expect-error htmb only has HTML tags
htmb.notATag();
// @ts-expect-error tag functions return a string
const length: number = div();

export { page, empty, escaped, length };
