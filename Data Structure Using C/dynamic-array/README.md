# Dynamic Array in C

A dynamic array stores items next to each other in memory and grows its
allocated storage when it runs out of capacity. Unlike a fixed-size array, it
can accept more items at runtime while still providing constant-time indexed
access.

## Files

- `dynamic_array.h` declares the array type and operations.
- `dynamic_array.c` implements the operations.
- `demo.c` shows how to create, use, and free an array.
- `test_dynamic_array.c` checks growth, indexing, updates, removal, and empty
  array behavior.

## Build and run the demo

From this directory, compile the two source files together:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic dynamic_array.c demo.c -o demo
./demo
```

The demo adds five integers, prints the length and capacity, lists the values,
and removes the last item.

## Run the checks

```sh
cc -std=c11 -Wall -Wextra -Wpedantic dynamic_array.c test_dynamic_array.c -o test_dynamic_array
./test_dynamic_array
```

The test inserts enough items to trigger several growth operations, verifies
indexed reads and writes, removes every item, and checks invalid and empty
operations.

## How it works

The array tracks its current `length` separately from its allocated
`capacity`. When a push reaches capacity, it doubles the capacity (starting at
four items) and uses `realloc` to request more contiguous storage. The new
pointer is saved only after `realloc` succeeds, so a failed allocation leaves
the existing array intact.

| Operation | Time |
| --- | --- |
| Get or set by index | O(1) |
| Push | Amortized O(1); O(n) when storage grows |
| Pop from the end | O(1) |

`dynamic_array_get`, `dynamic_array_set`, and `dynamic_array_pop` return `false`
for invalid arguments, out-of-range indices, or an empty array. Always call
`dynamic_array_destroy` when finished; it frees the allocated storage and
resets the array fields.
