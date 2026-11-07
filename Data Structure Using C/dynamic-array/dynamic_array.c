#include "dynamic_array.h"

#include <stdint.h>
#include <stdlib.h>

bool dynamic_array_init(DynamicArray *array)
{
    if (array == NULL) {
        return false;
    }

    array->items = NULL;
    array->length = 0;
    array->capacity = 0;
    return true;
}

void dynamic_array_destroy(DynamicArray *array)
{
    if (array == NULL) {
        return;
    }

    free(array->items);
    array->items = NULL;
    array->length = 0;
    array->capacity = 0;
}

bool dynamic_array_push(DynamicArray *array, int value)
{
    if (array == NULL) {
        return false;
    }

    if (array->length == array->capacity) {
        size_t new_capacity = array->capacity == 0 ? 4 : array->capacity * 2;
        if (array->capacity > SIZE_MAX / 2 ||
            new_capacity > SIZE_MAX / sizeof *array->items) {
            return false;
        }

        int *new_items = realloc(array->items, new_capacity * sizeof *array->items);
        if (new_items == NULL) {
            return false;
        }

        array->items = new_items;
        array->capacity = new_capacity;
    }

    array->items[array->length] = value;
    array->length++;
    return true;
}

bool dynamic_array_get(const DynamicArray *array, size_t index, int *out_value)
{
    if (array == NULL || out_value == NULL || index >= array->length) {
        return false;
    }

    *out_value = array->items[index];
    return true;
}

bool dynamic_array_set(DynamicArray *array, size_t index, int value)
{
    if (array == NULL || index >= array->length) {
        return false;
    }

    array->items[index] = value;
    return true;
}

bool dynamic_array_pop(DynamicArray *array, int *out_value)
{
    if (array == NULL || out_value == NULL || array->length == 0) {
        return false;
    }

    array->length--;
    *out_value = array->items[array->length];
    return true;
}
