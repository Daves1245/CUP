#include <stdio.h>

int partition(int arr[], int l, int h)
{
    int p = arr[h];
    int ei = l - 1;

    for (int i = l; i < h; i++) {
        if (arr[i] <= p) {
            ei++;
            swap(&arr[ei], &arr[i]);
        }
    }
    swap(&arr[ei + 1], &arr[h]);
    return ei + 1;
}

void quicksort(int arr[], int l, int h)
{
    if (l < h) {
        int pi = partition(arr, l, h);
        quicksort(arr, l, pi - 1);
        quicksort(arr, pi + 1, h);
    }
}

