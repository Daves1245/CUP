#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "include.c"
#include "bubble.c"
#include "quicksort.c"
#include "selection.c"
#include "insertion.c"
#include "merge.c"

#define LIMIT 50
#define MAX_RAND 100

// trick - use pointers to array elements
// rather than giving a pointer to the array 
// and indexes of the elements

void shuffle(int arr[], int n) {
    for (int i = 0; i < n; i++) {
        swap(&arr[i], &arr[rand() % n]);
    }
}

void fill_with_random(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % MAX_RAND;
    }
}

int main(void)
{
    srand(time(0));

    int arr[] = {5, 4, 3, 2, 1, 0};
    merge_sort(arr, 6);
    for (int i = 0; i < 6; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
    return 0;
}
