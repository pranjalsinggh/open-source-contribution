#include <stdio.h>

void swap(int *left, int *right)
{
    int temporary = *left;
    *left = *right;
    *right = temporary;
}

int partition(int array[], int low, int high)
{
    int pivot = array[high];
    int i = low - 1;
    int j;

    for (j = low; j < high; j++) {
        if (array[j] <= pivot) {
            i++;
            swap(&array[i], &array[j]);
        }
    }

    swap(&array[i + 1], &array[high]);
    return i + 1;
}

void quick_sort(int array[], int low, int high)
{
    if (low < high) {
        int pivot = partition(array, low, high);
        quick_sort(array, low, pivot - 1);
        quick_sort(array, pivot + 1, high);
    }
}

void print_array(const int array[], int length)
{
    int i;

    for (i = 0; i < length; i++) {
        printf("%d ", array[i]);
    }
    printf("\n");
}

int main(void)
{
    int array[] = {10, 7, 8, 9, 1, 5};
    int length = (int)(sizeof(array) / sizeof(array[0]));

    printf("Before sorting:\n");
    print_array(array, length);

    quick_sort(array, 0, length - 1);

    printf("After sorting:\n");
    print_array(array, length);

    return 0;
}
