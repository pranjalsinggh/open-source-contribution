# Binary Search Tree in C

This example builds a binary search tree (BST), searches for values, and prints
an in-order traversal. For each node, smaller values go to the left and larger
values go to the right. Duplicate values are ignored.

The in-order traversal visits the left subtree, the current node, and then the
right subtree, so the output is sorted. Search and insertion take `O(h)` time,
where `h` is the tree height: typically `O(log n)` for a balanced tree and
`O(n)` in the worst case.

## Build and run

From this directory, compile with a C11 compiler:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic binary_search_tree.c -o binary_search_tree
./binary_search_tree
```

Expected output:

```text
Ignored duplicate value: 6
In-order traversal: 1 3 4 6 7 8 10 13 14
Search for 7: found
Search for 2: not found
```
