#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct {
    int *values;
    size_t size;
    size_t capacity;
} MinHeap;

static bool min_heap_init(MinHeap *heap)
{
    if (heap == NULL) {
        return false;
    }

    heap->values = NULL;
    heap->size = 0;
    heap->capacity = 0;
    return true;
}

static bool min_heap_reserve(MinHeap *heap, size_t needed)
{
    size_t new_capacity = heap->capacity;
    int *new_values;

    if (needed <= heap->capacity) {
        return true;
    }

    if (new_capacity == 0) {
        new_capacity = 8;
    }

    while (new_capacity < needed) {
        if (new_capacity > SIZE_MAX / 2) {
            new_capacity = needed;
            break;
        }
        new_capacity *= 2;
    }

    if (new_capacity > SIZE_MAX / sizeof(*heap->values)) {
        return false;
    }

    new_values = realloc(heap->values, new_capacity * sizeof(*heap->values));
    if (new_values == NULL) {
        return false;
    }

    heap->values = new_values;
    heap->capacity = new_capacity;
    return true;
}

static bool min_heap_push(MinHeap *heap, int value)
{
    size_t child;

    if (heap == NULL || heap->size == SIZE_MAX ||
        !min_heap_reserve(heap, heap->size + 1)) {
        return false;
    }

    child = heap->size++;
    while (child > 0) {
        size_t parent = (child - 1) / 2;

        if (heap->values[parent] <= value) {
            break;
        }
        heap->values[child] = heap->values[parent];
        child = parent;
    }
    heap->values[child] = value;
    return true;
}

static bool min_heap_peek(const MinHeap *heap, int *minimum)
{
    if (heap == NULL || minimum == NULL || heap->size == 0) {
        return false;
    }

    *minimum = heap->values[0];
    return true;
}

static bool min_heap_pop(MinHeap *heap, int *minimum)
{
    size_t parent = 0;
    int last;

    if (heap == NULL || minimum == NULL || heap->size == 0) {
        return false;
    }

    *minimum = heap->values[0];
    last = heap->values[heap->size - 1];
    heap->size--;

    while (parent < heap->size / 2) {
        size_t child = parent * 2 + 1;

        if (child + 1 < heap->size &&
            heap->values[child + 1] < heap->values[child]) {
            child++;
        }
        if (last <= heap->values[child]) {
            break;
        }
        heap->values[parent] = heap->values[child];
        parent = child;
    }

    if (heap->size > 0) {
        heap->values[parent] = last;
    }
    return true;
}

static void min_heap_destroy(MinHeap *heap)
{
    if (heap != NULL) {
        free(heap->values);
        heap->values = NULL;
        heap->size = 0;
        heap->capacity = 0;
    }
}

int main(void)
{
    MinHeap heap;
    const int input[] = {7, -2, 4, 4, 0, 12, -9, 3, 1};
    const int expected[] = {-9, -2, 0, 1, 3, 4, 4, 7, 12};
    int value;
    size_t index;

    if (!min_heap_init(&heap)) {
        fprintf(stderr, "Could not initialize the min-heap.\n");
        return EXIT_FAILURE;
    }

    for (index = 0; index < sizeof(input) / sizeof(input[0]); index++) {
        if (!min_heap_push(&heap, input[index])) {
            fprintf(stderr, "Could not add a value to the min-heap.\n");
            min_heap_destroy(&heap);
            return EXIT_FAILURE;
        }
    }

    if (!min_heap_peek(&heap, &value) || value != expected[0]) {
        fprintf(stderr, "The min-heap returned an incorrect minimum.\n");
        min_heap_destroy(&heap);
        return EXIT_FAILURE;
    }
    printf("Minimum before removal: %d\n", value);
    printf("Values removed in priority order:");

    for (index = 0; index < sizeof(expected) / sizeof(expected[0]); index++) {
        if (!min_heap_pop(&heap, &value) || value != expected[index]) {
            fprintf(stderr, "\nThe min-heap returned values in the wrong order.\n");
            min_heap_destroy(&heap);
            return EXIT_FAILURE;
        }
        printf(" %d", value);
    }
    printf("\n");

    if (min_heap_pop(&heap, &value)) {
        fprintf(stderr, "Removing from an empty min-heap should fail.\n");
        min_heap_destroy(&heap);
        return EXIT_FAILURE;
    }

    min_heap_destroy(&heap);
    return EXIT_SUCCESS;
}
