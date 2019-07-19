#include <stdio.h>

void swap(int *arr, int a, int b) {
        int tmp = arr[b];
        arr[b] = arr[a];
        arr[a] = tmp;
}

int main(void) {
        int n;
        scanf("%d", &n);
        
        int arr[n];

        for (int i = 0; i < n; i++) {
                scanf("%d", &arr[i]);
        }

        for (int i = 0; i < n; i++) {
                for (int j = i; j < n; j++) {
                        if (arr[i] > arr[j]) {
                                swap(arr, i, j);
                        }
                }
        }

        for (int i = 0; i < n; i++) {
                printf("%d ", arr[i]);
        }

        return 0;
}
