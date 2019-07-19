#include <stdio.h>

void swap(int arr[], int a, int b)
{
    int tmp = arr[b];
    arr[b] = arr[a];
    arr[a] = tmp;
}

int min_index(int arr[], int low, int high)
{
    int ret = low, val = arr[ret], i;
    for (i = low; i < high; i++) {
        if (arr[i] < val) {
            ret = i;
            val = arr[ret];
        }
    }

    return ret;
}

void selection_sort(int arr[], size_t size) {
    for (int i = 0; i < size; i++) {
        swap(arr, i, min_index(arr, i, size));
    } 
}

