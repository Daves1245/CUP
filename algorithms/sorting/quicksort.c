#include <stdio.h>

void swap(int arr[], int a, int b)
{
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

int partition(int arr[], int l, int h)
{
    int p = arr[h];
    int ei = l - 1;

    for (int i = l; i < h; i++) {
        if (arr[i] <= p) {
            ei++;
            swap(arr, ei, i);
        }
    }
    swap(arr, ei + 1, h);
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

int main(void)
{
    int n;
    printf("How many numbers? ");
    scanf("%d", &n);
    int arr[n];
    printf("Input %d numbers: ", n);
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    quicksort(arr, 0, n - 1);
    printf("\nNumbers in sorted order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
