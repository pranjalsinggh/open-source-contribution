# AVL Tree in C

This example builds an AVL tree by inserting a fixed set of integer keys. An
AVL tree is a binary search tree that keeps the heights of each node's
subtrees within one of each other using rotations.

```sh
gcc -std=c11 -Wall -Wextra -pedantic avl_tree.c -o avl_tree
./avl_tree
```

The program prints the keys in sorted order, the balanced root, and the result
of searching for both a present and an absent key. Duplicate keys are ignored.
Insertion and search take `O(log n)` time because the tree remains balanced;
the tree uses `O(n)` space.
