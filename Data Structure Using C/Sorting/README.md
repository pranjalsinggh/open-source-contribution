# Merge Sort in C

Merge sort sorts an array by repeatedly splitting it into smaller halves,
sorting each half, and merging the sorted halves back together. It is a stable
sorting algorithm: equal values keep their original order.

## Example

The function below uses half-open ranges: `left` is included and `right` is
excluded. A temporary array stores values while each pair of sorted halves is
merged.

```c
#include <stddef.h>
#include <stdio.h>

static void merge(int values[], int temporary[], size_t left, size_t middle,
                  size_t right)
{
    size_t first = left;
    size_t second = middle;
    size_t output = left;

    while (first < middle && second < right) {
        if (values[first] <= values[second]) {
            temporary[output++] = values[first++];
        } else {
            temporary[output++] = values[second++];
        }
    }

    while (first < middle) {
        temporary[output++] = values[first++];
    }
    while (second < right) {
        temporary[output++] = values[second++];
    }

    for (size_t index = left; index < right; index++) {
        values[index] = temporary[index];
    }
}

static void merge_sort(int values[], int temporary[], size_t left, size_t right)
{
    if (right - left < 2) {
        return;
    }

    size_t middle = left + (right - left) / 2;
    merge_sort(values, temporary, left, middle);
    merge_sort(values, temporary, middle, right);
    merge(values, temporary, left, middle, right);
}

int main(void)
{
    int values[] = {38, 27, 43, 3, 9, 82, 10};
    int temporary[sizeof values / sizeof values[0]];
    size_t length = sizeof values / sizeof values[0];

    merge_sort(values, temporary, 0, length);

    for (size_t index = 0; index < length; index++) {
        printf("%d ", values[index]);
    }
    putchar('\n');
    return 0;
}
```

Compile and run with a C compiler:

```sh
cc -std=c11 -Wall -Wextra -Wpedantic merge_sort.c -o merge_sort
./merge_sort
```

Expected output:

```text
3 9 10 27 38 43 82
```

## Complexity

- **Time:** `O(n log n)` in the best, average, and worst cases.
- **Extra space:** `O(n)` for the temporary array.
- **Stable:** Yes; choosing the left value when values are equal preserves
  their order.
