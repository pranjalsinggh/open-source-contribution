# Circular Queue in C

`queue.c` demonstrates a fixed-capacity FIFO (first-in, first-out) queue using
a circular array. Enqueuing advances the rear index, and dequeuing advances the
front index; both indices wrap to the beginning when they reach the end. This
lets the queue reuse freed positions without shifting its elements.

The menu supports enqueue, dequeue, and display operations. The program reports
when the queue is full or empty, rejects invalid integer input, and exits
cleanly when input ends.

Compile and run it from the `Data Structure Using C` directory:

```sh
gcc queue/queue.c -o queue
./queue
```
