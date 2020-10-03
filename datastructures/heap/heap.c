#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"
#include "util.h"

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

/* Percolate an element up the heap */
void percolateUp(int *arr, struct heap_context *hctx, int i) {
    while (i != ROOT && hctx->comp(arr[i], arr[parent(i)])) {
        swap(arr, i, parent(i));
        i = parent(i);
    }
}

/* Percolate an element down the heap */
void percolateDown(int *arr, struct heap_context *hctx, int i) {
    int swapi = i;
    // printf("i = %d, a[i, l(i), r(i)] = %d, %d, %d\n", i, arr[i], arr[left(i)], arr[right(i)]);
    if (left(i) <= hctx->heap_size && hctx->comp(arr[i], arr[left(i)])) {
        swapi = left(i);
    }
    if (right(i) <= hctx->heap_size && hctx->comp(arr[swapi], arr[right(i)])) {
        swapi = right(i);
    }

    if (i != swapi) {
        swap(arr, i, swapi);
        percolateDown(arr, hctx, swapi);
    }
}

/* Insert an element into the heap */
int heap_insert(int *arr, struct heap_context *hctx, int val) {
    if (hctx->heap_size == hctx->arr_len) {
        // TODO set an error state
        printf("HEAP REACHED CAPACITY, CANNOT ADD TO HEAP\n");
        return -1;
    }
    hctx->heap_size++;
    arr[hctx->heap_size] = val;
    percolateUp(arr, hctx, hctx->heap_size);
}

/* Remove an element from the heap */
int heap_extract(int *arr, struct heap_context *hctx) {
    int ret = -1;
    if (hctx->heap_size == 0) {
        printf("heap empty, cannot extract\n");
        // TODO set an error state
        return ret;
    }

    ret = arr[ROOT];
    swap(arr, ROOT, hctx->heap_size);
    // ret = arr[ROOT] = arr[hctx->heap_size];
    hctx->heap_size--;
    percolateDown(arr, hctx, ROOT);
    return ret;
}

/* Build a heap from an array */
void build_heap(int *arr, struct heap_context *hctx) {
    hctx->heap_size = hctx->arr_len;
    for (int i = hctx->heap_size; i >= ROOT; i--) {
        percolateDown(arr, hctx, i);
    }
}

/* Apply heap sort to an array */
void heapsort(int *arr, struct heap_context *hctx) {
    build_heap(arr, hctx);
    for (int i = hctx->arr_len; i >= ROOT; i--) {
        swap(arr, i, ROOT);
        hctx->heap_size--;
        percolateDown(arr, hctx, ROOT);
    }
}

