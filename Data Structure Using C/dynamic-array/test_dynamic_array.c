#include "dynamic_array.h"

#include <stdio.h>

#define CHECK(condition)                                                        \
    do {                                                                        \
        if (!(condition)) {                                                     \
            fprintf(stderr, "Check failed at line %d: %s\n", __LINE__, #condition); \
            return 1;                                                           \
        }                                                                       \
    } while (0)

int main(void)
{
    DynamicArray numbers;
    int value;

    CHECK(dynamic_array_init(&numbers));
    CHECK(!dynamic_array_get(&numbers, 0, &value));
    CHECK(!dynamic_array_pop(&numbers, &value));

    for (int number = 0; number < 128; number++) {
        CHECK(dynamic_array_push(&numbers, number));
    }
    CHECK(numbers.length == 128);
    CHECK(numbers.capacity >= numbers.length);

    for (size_t index = 0; index < numbers.length; index++) {
        CHECK(dynamic_array_get(&numbers, index, &value));
        CHECK(value == (int)index);
    }

    CHECK(dynamic_array_set(&numbers, 50, -50));
    CHECK(dynamic_array_get(&numbers, 50, &value));
    CHECK(value == -50);
    CHECK(!dynamic_array_get(&numbers, numbers.length, &value));
    CHECK(!dynamic_array_set(&numbers, numbers.length, 0));

    for (int number = 127; number >= 0; number--) {
        CHECK(dynamic_array_pop(&numbers, &value));
        CHECK(value == (number == 50 ? -50 : number));
    }
    CHECK(numbers.length == 0);
    CHECK(!dynamic_array_pop(&numbers, &value));

    dynamic_array_destroy(&numbers);
    CHECK(numbers.items == NULL);
    CHECK(numbers.length == 0);
    CHECK(numbers.capacity == 0);
    dynamic_array_destroy(&numbers);

    puts("All dynamic array checks passed.");
    return 0;
}
