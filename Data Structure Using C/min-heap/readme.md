# Min-Heap in C

A min-heap is a complete binary tree stored in an array. Each parent is no
larger than its children, so the smallest value is always at the root. This
example uses a dynamically growing array and supports duplicate and negative
integers.

## Operations

- **Insert:** append a value, then move it upward until the heap property holds.
- **Peek:** read the minimum without removing it.
- **Remove minimum:** replace the root with the last value, then move it down
  into the correct position.

Insertion and removal take `O(log n)` time, while peeking takes `O(1)`. The
array grows geometrically when it runs out of space.

## Build and run

```sh
gcc -std=c11 -Wall -Wextra -Wpedantic -Werror min_heap.c -o min_heap
./min_heap
```

The program demonstrates the minimum before removal and verifies that all
values are removed in ascending order, including duplicates and negative
values. It also checks that removing from an empty heap fails cleanly.
