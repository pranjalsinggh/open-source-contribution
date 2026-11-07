#ifndef DYNAMIC_ARRAY_H
#define DYNAMIC_ARRAY_H

#include <stdbool.h>
#include <stddef.h>

typedef struct {
    int *items;
    size_t length;
    size_t capacity;
} DynamicArray;

bool dynamic_array_init(DynamicArray *array);
void dynamic_array_destroy(DynamicArray *array);
bool dynamic_array_push(DynamicArray *array, int value);
bool dynamic_array_get(const DynamicArray *array, size_t index, int *out_value);
bool dynamic_array_set(DynamicArray *array, size_t index, int value);
bool dynamic_array_pop(DynamicArray *array, int *out_value);

#endif
