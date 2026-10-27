# JavaScript async/await

`async` and `await` make asynchronous JavaScript easier to read. They are built on promises: an `async` function always returns a promise, and `await` pauses that function until a promise settles. It does not block the rest of the program.

## Run the example

With Node.js installed, run:

```sh
node async-await-tutorial.js
```

The example uses local arrays and a short timer to imitate two data lookups. It does not make network requests or need extra packages.

## Follow the flow

1. `findUserById` and `findOrdersByUserId` return promises. In a real app, these could represent database calls or `fetch` requests.
2. `showUserOrders` is marked `async`, so it can use `await` inside its body.
3. Each `await` gets the value from a promise before the next line runs. The order lookup uses `user.id`, so it happens after the user lookup succeeds.
4. If the user is missing, the function throws an error. The `catch` block handles it and prints a helpful message.
5. `main` awaits each call in turn, so the example output stays easy to follow.

## Promise equivalent

This:

```js
const user = await findUserById(1);
```

is similar to:

```js
findUserById(1).then((user) => {
  // Use the resolved user here.
});
```

Use `try`/`catch` around awaited operations when you need to handle failures. For independent operations that can run at the same time, `Promise.all` can avoid waiting for them one by one.
