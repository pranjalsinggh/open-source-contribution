# Breadth-First Search in JavaScript

Breadth-first search (BFS) explores a graph one distance level at a time. This example uses BFS to find a shortest path in an unweighted graph.

## Run the example

```powershell
node .\breadth-first-search.js
```

The example prints:

```text
[ 'A', 'C', 'F', 'G' ]
```

The graph is represented by a `Map` from each node to its neighbors; include an entry even for nodes with no neighbors. The example lists each undirected connection in both directions. For a directed graph, list only the outgoing neighbors.

`shortestPathBfs(graph, start, target)` returns the shortest path as an array, or `null` if either endpoint is absent or no path exists. If `start` and `target` are the same existing node, the result is `[start]`.

BFS marks a node as visited when it is added to the queue, so cycles do not cause repeated visits. The `parent` map records how each node was reached and is used to reconstruct the path. A queue index avoids the extra work of removing the first array element on each iteration.

The time and space complexity are both **O(V + E)** in the worst case, where `V` is the number of nodes and `E` is the number of edges. BFS finds a shortest path by edge count when all edges have equal cost; use a weighted-graph algorithm such as Dijkstra's algorithm when edge costs differ.
