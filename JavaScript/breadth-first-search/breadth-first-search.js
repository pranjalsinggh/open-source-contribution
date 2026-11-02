'use strict';

function shortestPathBfs(graph, start, target) {
  if (!graph.has(start) || !graph.has(target)) {
    return null;
  }

  const queue = [start];
  const parent = new Map([[start, null]]);
  let head = 0;

  while (head < queue.length) {
    const current = queue[head];
    head += 1;

    if (current === target) {
      break;
    }

    for (const neighbor of graph.get(current)) {
      if (!parent.has(neighbor)) {
        parent.set(neighbor, current);
        queue.push(neighbor);
      }
    }
  }

  if (!parent.has(target)) {
    return null;
  }

  const path = [];
  let current = target;

  while (current !== null) {
    path.push(current);
    current = parent.get(current);
  }

  return path.reverse();
}

if (require.main === module) {
  const graph = new Map([
    ['A', ['B', 'C']],
    ['B', ['A', 'D', 'E']],
    ['C', ['A', 'F']],
    ['D', ['B']],
    ['E', ['B', 'F']],
    ['F', ['C', 'E', 'G']],
    ['G', ['F']],
  ]);

  console.log(shortestPathBfs(graph, 'A', 'G'));
}

module.exports = { shortestPathBfs };
