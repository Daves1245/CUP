#include <stdio.h>

void swap(int arr[], int a, int b) {
    int tmp = arr[b];
    arr[b] = arr[a];
    arr[a] = tmp;
}

void insertion_sort(int arr[], size_t size)
{
    for (int i = 1; i < size; i++) {
        if (arr[i + 1] < arr[i]) {
            for (int j = 0; j <= i; j++) {
                swap(arr, j, i);
            }
        }
    }
}

