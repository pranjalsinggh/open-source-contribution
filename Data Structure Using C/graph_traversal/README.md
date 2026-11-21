# Graph Traversal in C

This example runs breadth-first search (BFS) and depth-first search (DFS) on
the same undirected graph represented by an adjacency matrix.

```sh
gcc -std=c11 -Wall -Wextra -pedantic graph_traversal.c -o graph_traversal
./graph_traversal
```

BFS uses a queue and visits vertices in increasing distance from the start
vertex. DFS uses recursion to explore one path before backtracking. Both
traversals start at vertex `0`; vertex labels range from `0` to `5`.

Because this example uses an adjacency matrix, each traversal takes
`O(V^2)` time and the graph representation takes `O(V^2)` space. An adjacency
list is generally preferable for sparse graphs.
