# Data Structures in C

This folder contains small, menu-driven examples of common data structures:

- [Stack](stack/stack.c) — a fixed-size stack with push, pop, and display operations.
- [Circular queue](queue/queue.c) — a fixed-size FIFO queue with enqueue, dequeue, and display operations.

Compile an example with a C compiler, for example:

```sh
gcc queue/queue.c -o queue
./queue
```

The circular queue reuses freed array positions by wrapping its front and rear
indices back to the start of the array.
