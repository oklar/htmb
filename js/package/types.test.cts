// Checked by `npm run test:types`, not run: the same types through require
import htmb = require("htmb");

const { div, escape } = htmb;

export const page: string = div({ class: "x" }, escape("<b>"), htmb.br());
