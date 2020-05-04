#include <stdio.h>
#include "heap.h"

/* Driver - test heapsort algorithm */
int main(void) {
    int arr[] = {3, 2, 1};
    heapsort(arr, 3);
    for (int i = 0; i < 3; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
    return 0;
}

static inline int greater(int a, int b) {
    return a > b;
}

static inline int lesser(int a, int b) {
    return a < b;
}

#define HEAP_SWAP(type, arr, i, j) \
    do { \
        type tmp = arr[i]; \
        arr[i] = arr[j]; \
        arr[j] = tmp; \
    } while (0);

struct node {
    struct node *left, *right, *parent;
    int data;
};

static inline int parent(int i) {
    return (i - 1) / 2;
}

static inline int left(int i) {
    return 2 * i + 1;
}

static inline int right(int i) {
    return 2 * i + 2;
}

/* Heapify an array */
void heapify(int *arr, size_t len, unsigned i, int (*comp)(int, int)) {
    unsigned swapi = i;
    if (left(i) < len && comp(arr[left(i)], arr[i])) {
        swapi = left(i); 
    }
    if (right(i) < len && comp(arr[right(i)], arr[swapi])) {
        swapi = right(i);
    }
    if (i != swapi) {
        HEAP_SWAP(int, arr, i, swapi);
        heapify(arr, len, swapi, comp);
    }
}

/* Build a heap with comparator func */
void build_heap(int *arr, size_t len, int (*comp)(int, int)) {
    for (unsigned i = len - 1; i != 0; i = parent(i)) {
        heapify(arr, len, i, comp);
    }
}

/* Sort using heap */
void heapsort(int *arr, size_t len) {
    for (int i = len - 1; i > 0; i--) {
        HEAP_SWAP(int, arr, 0, i);
        heapify(arr, len, 0, lesser);
    }
}

void printarr(int *arr, size_t len) {
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

