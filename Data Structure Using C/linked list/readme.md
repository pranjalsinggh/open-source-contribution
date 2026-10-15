# Singly linked list in C

This example stores integers in dynamically allocated nodes. Each node points
to the next one, so the list can grow as values are added.

The menu supports appending a value, deleting the first matching value,
displaying the list, and exiting. Nodes are released when deleted and when the
program exits.

Compile and run with a C compiler:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic linked_list.c -o linked_list
./linked_list
```
