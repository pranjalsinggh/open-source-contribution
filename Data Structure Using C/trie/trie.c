#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define ALPHABET_SIZE 26

typedef struct TrieNode {
    struct TrieNode *children[ALPHABET_SIZE];
    bool is_end_of_word;
} TrieNode;

static TrieNode *create_node(void)
{
    TrieNode *node = calloc(1, sizeof(*node));

    if (node == NULL) {
        fputs("Unable to allocate memory for a trie node.\n", stderr);
        exit(EXIT_FAILURE);
    }

    return node;
}

static bool is_lowercase_word(const char *word)
{
    if (word == NULL || word[0] == '\0') {
        return false;
    }

    for (size_t i = 0; word[i] != '\0'; i++) {
        if (word[i] < 'a' || word[i] > 'z') {
            return false;
        }
    }
    return true;
}

static void insert(TrieNode *root, const char *word)
{
    if (!is_lowercase_word(word)) {
        printf("Rejected invalid word: %s\n", word == NULL ? "(null)" : word);
        return;
    }

    TrieNode *current = root;
    for (size_t i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            current->children[index] = create_node();
        }
        current = current->children[index];
    }
    current->is_end_of_word = true;
}

static bool contains_word(const TrieNode *root, const char *word)
{
    if (!is_lowercase_word(word)) {
        return false;
    }

    const TrieNode *current = root;
    for (size_t i = 0; word[i] != '\0'; i++) {
        int index = word[i] - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
    }
    return current->is_end_of_word;
}

static bool contains_prefix(const TrieNode *root, const char *prefix)
{
    if (!is_lowercase_word(prefix)) {
        return false;
    }

    const TrieNode *current = root;
    for (size_t i = 0; prefix[i] != '\0'; i++) {
        int index = prefix[i] - 'a';
        if (current->children[index] == NULL) {
            return false;
        }
        current = current->children[index];
    }
    return true;
}

static void free_trie(TrieNode *root)
{
    if (root == NULL) {
        return;
    }

    for (int i = 0; i < ALPHABET_SIZE; i++) {
        free_trie(root->children[i]);
    }
    free(root);
}

int main(void)
{
    const char *words[] = {"cat", "car", "care", "dog", "dove"};
    const size_t word_count = sizeof(words) / sizeof(words[0]);
    TrieNode *root = create_node();

    for (size_t i = 0; i < word_count; i++) {
        insert(root, words[i]);
    }

    printf("Search for 'car': %s\n", contains_word(root, "car") ? "found" : "not found");
    printf("Search for 'cap': %s\n", contains_word(root, "cap") ? "found" : "not found");
    printf("Prefix 'ca': %s\n", contains_prefix(root, "ca") ? "found" : "not found");
    printf("Prefix 'de': %s\n", contains_prefix(root, "de") ? "found" : "not found");

    free_trie(root);
    return 0;
}
