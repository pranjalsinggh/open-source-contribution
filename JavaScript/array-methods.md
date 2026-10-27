# JavaScript array methods: map, filter, and reduce

This example uses a small product inventory to show three common ways to
transform arrays. It uses only built-in JavaScript features and does not change
the original array.

## Run the example

From the repository root, run:

```sh
node JavaScript/array-methods.js
```

The script prints each product name, the products that are in stock, and the
total value of the inventory.

## The three methods

- `map` calls a function for every item and returns a new array. The example
  uses it to get the product names.
- `filter` keeps only the items for which a condition is true. The example
  keeps products with a quantity greater than zero.
- `reduce` combines all items into one value. The example adds each product's
  price multiplied by its quantity. The initial value of `0` also makes an
  empty inventory total zero.

Try changing a product's quantity or adding a product, then run the script
again to see how each result changes.
