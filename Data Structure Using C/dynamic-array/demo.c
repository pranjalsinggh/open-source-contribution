#include "dynamic_array.h"

#include <stdio.h>

int main(void)
{
    DynamicArray numbers;
    if (!dynamic_array_init(&numbers)) {
        fprintf(stderr, "Could not initialize the array.\n");
        return 1;
    }

    for (int value = 10; value <= 50; value += 10) {
        if (!dynamic_array_push(&numbers, value)) {
            fprintf(stderr, "Could not add a value to the array.\n");
            dynamic_array_destroy(&numbers);
            return 1;
        }
    }

    printf("Length: %zu, capacity: %zu\n", numbers.length, numbers.capacity);
    printf("Values:");
    for (size_t index = 0; index < numbers.length; index++) {
        int value;
        if (!dynamic_array_get(&numbers, index, &value)) {
            fprintf(stderr, "\nCould not read the array value.\n");
            dynamic_array_destroy(&numbers);
            return 1;
        }
        printf(" %d", value);
    }
    printf("\n");

    int removed_value;
    if (!dynamic_array_pop(&numbers, &removed_value)) {
        fprintf(stderr, "Could not remove a value from the array.\n");
        dynamic_array_destroy(&numbers);
        return 1;
    }
    printf("Popped: %d\n", removed_value);

    dynamic_array_destroy(&numbers);
    return 0;
}
