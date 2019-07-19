#include <stdio.h>

void swap(int arr[], int a, int b)
{
    int tmp = arr[b];
    arr[b] = arr[a];
    arr[a] = tmp;
}

void bubblesort(int arr[], size_t size)
{
    for (int i = 0; i < size - 1; i++) {
        for (int j = 0; j < size - (i + 1); j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr, j, j + 1);
            }
        }
    }
}

int main(void)
{
    int n;
    printf("how many numbers? ");
    scanf("%d", &n);
    printf("enter %d numbers: ", n);
    int arr[n];
    for (int i = 0; i < n; i++) {
        scanf("%d", &arr[i]);
    }
    bubblesort(arr, n);
    printf("here are the numbers in sorted order: ");
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
