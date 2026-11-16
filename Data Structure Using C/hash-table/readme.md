# Hash Table with Separate Chaining in C

This example maps string keys to integer values. A hash function selects one
of ten buckets, and each bucket contains a linked list. Separate chaining lets
different keys share a bucket without overwriting one another.

## Operations

- **Set:** insert a key or update its value if it already exists.
- **Get:** look up a key and return whether it was found.
- **Remove:** unlink and free a key-value entry.
- **Destroy:** free every entry and its copied key.

The example's keys `"a"` and `"k"` intentionally collide with the included
hash function, demonstrating lookup and removal in a chained bucket. Lookup
and insertion are `O(1)` on average when keys are distributed across buckets;
in the worst case, a bucket contains all `n` entries and an operation is
`O(n)`. This teaching implementation uses a fixed bucket count rather than
resizing the table.

## Build and run

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror hash_table.c -o hash_table
./hash_table
```

The program checks collision handling, updating an existing key, missing-key
lookups, and removal. It exits with a failure status if any check fails.
