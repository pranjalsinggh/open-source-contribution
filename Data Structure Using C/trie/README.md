# Trie in C

This example stores lowercase words in a trie (prefix tree). Shared prefixes
reuse the same nodes, making the structure useful for word lookup and prefix
queries.

```sh
gcc -std=c11 -Wall -Wextra -pedantic trie.c -o trie
./trie
```

The demo inserts several words, checks complete-word membership, and checks
whether prefixes exist. Insert and lookup each take `O(L)` time for a word of
length `L`; storage is at most `O(N * 26)` child pointers for `N` stored
characters. Only non-empty lowercase English words and prefixes are accepted.
