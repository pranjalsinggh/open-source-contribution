# JavaScript `Map` and `Set`

Use a **`Set`** when you need unique values. In `map-and-set.js`, spreading a
`Set` back into an array removes duplicate attendee IDs while preserving their
first-seen order.

Use a **`Map`** to associate keys with values. The example counts votes by
candidate name: `get` reads the current count and `set` stores the incremented
count. `has` checks whether a key exists.

Run the example with Node.js:

```sh
node JavaScript/map-and-set.js
```

The built-in assertions verify the unique IDs, vote totals, and key checks. No
packages are required.
