#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

enum { HASH_TABLE_BUCKET_COUNT = 10 };

typedef struct Entry {
    char *key;
    int value;
    struct Entry *next;
} Entry;

typedef struct {
    Entry *buckets[HASH_TABLE_BUCKET_COUNT];
} HashTable;

static size_t hash_key(const char *key)
{
    size_t hash = 5381;

    while (*key != '\0') {
        hash = hash * 33 + (unsigned char)*key;
        key++;
    }

    return hash % HASH_TABLE_BUCKET_COUNT;
}

static bool hash_table_set(HashTable *table, const char *key, int value)
{
    size_t bucket;
    Entry *entry;
    size_t key_length;
    char *key_copy;

    if (table == NULL || key == NULL) {
        return false;
    }

    bucket = hash_key(key);
    for (entry = table->buckets[bucket]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            entry->value = value;
            return true;
        }
    }

    key_length = strlen(key);
    if (key_length == SIZE_MAX) {
        return false;
    }

    entry = malloc(sizeof(*entry));
    if (entry == NULL) {
        return false;
    }

    key_copy = malloc(key_length + 1);
    if (key_copy == NULL) {
        free(entry);
        return false;
    }
    memcpy(key_copy, key, key_length + 1);

    entry->key = key_copy;
    entry->value = value;
    entry->next = table->buckets[bucket];
    table->buckets[bucket] = entry;
    return true;
}

static bool hash_table_get(const HashTable *table, const char *key, int *value)
{
    size_t bucket;
    const Entry *entry;

    if (table == NULL || key == NULL || value == NULL) {
        return false;
    }

    bucket = hash_key(key);
    for (entry = table->buckets[bucket]; entry != NULL; entry = entry->next) {
        if (strcmp(entry->key, key) == 0) {
            *value = entry->value;
            return true;
        }
    }

    return false;
}

static bool hash_table_remove(HashTable *table, const char *key)
{
    size_t bucket;
    Entry **link;

    if (table == NULL || key == NULL) {
        return false;
    }

    bucket = hash_key(key);
    link = &table->buckets[bucket];
    while (*link != NULL) {
        Entry *entry = *link;

        if (strcmp(entry->key, key) == 0) {
            *link = entry->next;
            free(entry->key);
            free(entry);
            return true;
        }
        link = &entry->next;
    }

    return false;
}

static void hash_table_destroy(HashTable *table)
{
    size_t bucket;

    if (table == NULL) {
        return;
    }

    for (bucket = 0; bucket < HASH_TABLE_BUCKET_COUNT; bucket++) {
        Entry *entry = table->buckets[bucket];

        while (entry != NULL) {
            Entry *next = entry->next;

            free(entry->key);
            free(entry);
            entry = next;
        }
        table->buckets[bucket] = NULL;
    }
}

int main(void)
{
    HashTable table = {0};
    int first_value;
    int second_value;
    bool success = false;

    if (!hash_table_set(&table, "a", 10) ||
        !hash_table_set(&table, "k", 20)) {
        fprintf(stderr, "Could not insert values into the hash table.\n");
        goto cleanup;
    }

    if (!hash_table_set(&table, "a", 15)) {
        fprintf(stderr, "Could not update an existing key.\n");
        goto cleanup;
    }

    if (!hash_table_get(&table, "a", &first_value) ||
        !hash_table_get(&table, "k", &second_value) ||
        first_value != 15 || second_value != 20) {
        fprintf(stderr, "Lookup or update returned an incorrect value.\n");
        goto cleanup;
    }

    if (hash_table_get(&table, "missing", &first_value)) {
        fprintf(stderr, "Looking up a missing key should fail.\n");
        goto cleanup;
    }

    printf("Retrieved values after handling a collision and updating a key: "
           "a=%d, k=%d\n", first_value, second_value);

    if (!hash_table_remove(&table, "a") ||
        hash_table_get(&table, "a", &first_value) ||
        hash_table_remove(&table, "missing")) {
        fprintf(stderr, "Removing keys did not behave as expected.\n");
        goto cleanup;
    }

    success = true;

cleanup:
    hash_table_destroy(&table);
    return success ? EXIT_SUCCESS : EXIT_FAILURE;
}
