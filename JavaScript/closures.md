# JavaScript Closures

A **closure** is a function together with the variables it can access from the
scope where it was created. The returned methods in `closures.js` can still
read and update `count` after `createCounter` has finished running.

```js
const counter = createCounter(2);
counter.increment(); // 3
counter.getValue(); // 3
```

Each call to `createCounter` creates a separate `count`. The value is not
directly accessible from outside the function, so callers interact with it
through the returned methods.

Run the example with Node.js:

```sh
node JavaScript/closures.js
```

The built-in assertions check that the methods update the enclosed value and
that separate counters do not share state. No packages are required.
