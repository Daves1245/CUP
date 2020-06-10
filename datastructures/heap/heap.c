#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include "heap.h"

#define HEAP_SIZE 100
#define HEAP_MAX_ELEM_VALUE 1000

#define HEAP_SWAP(type, arr, i, j) \
    do { \
        type tmp = arr[i]; \
        arr[i] = arr[j]; \
        arr[j] = tmp; \
    } while (0);

// TODO check discord

static inline int randval(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void fill_with_random(int *arr, struct heap_context *actx) {
    for (int i = 0; i < actx->arr_len; i++) {
        arr[i] = randval(actx->min_elem_val, actx->max_elem_val);
    }
}

static inline int greater(int a, int b) {
    return a > b;
}

static inline int lesser(int a, int b) {
    return a < b;
}


/* Driver - test heapsort algorithm */
int main(int argc, char **argv) {
    int *arr;
    struct heap_context actx = {
        HEAP_SIZE,
        HEAP_MAX_ELEM_VALUE,
        0,
        HEAP_SIZE,
        greater
    };

    if (argc > 1) {
        actx.arr_len = atoi(argv[1]);
    }
    if (argc > 2) {
        actx.max_elem_val = atoi(argv[2]);
    }
    if (argc > 3) {
        actx.min_elem_val = atoi(argv[3]);
    }

    arr = malloc(sizeof(int) * actx.heap_size);
    memset(arr, 0, sizeof(int) * actx.heap_size);
    fill_with_random(arr, &actx);
    heapsort(arr, &actx);

    for (int i = 0; i < actx.arr_len; i++) {
        printf("%d ", arr[i]);
    }
    puts("");
    return 0;
}

static inline int parent(int i) {
    return (i - 2) / 2;
}

int left(int i) {
    return 2 * i + 1;
}

int right(int i) {
    return 2 * i + 2;
}

/* Heapify an array */
void heapify(int *arr, struct heap_context *hctx, int i) {
    int swapi = i;

    if (left(i) < hctx->heap_size && hctx->comp(arr[left(i)], arr[i])) {
        swapi = left(i);
    }

    if (right(i) < hctx->heap_size && hctx->comp(arr[right(i)], arr[swapi])) {
        swapi = right(i);
    }

    if (i != swapi) {
        HEAP_SWAP(int, arr, i, swapi);
        heapify(arr, hctx, swapi);
    }
}

/* Build a heap from an unsorted array */
void build_heap(int *arr, struct heap_context *hctx) {
    hctx->heap_size = hctx->arr_len;
    for (int i = hctx->heap_size; i > 0; i = parent(i)) {
        heapify(arr, hctx, i);
    }
}

/* Sort using heap */
void heapsort(int *arr, struct heap_context *hctx) {
    build_heap(arr, hctx);
    for (int i = hctx->arr_len - 1; i > 0; i--) {
        HEAP_SWAP(int, arr, 0, i);
        hctx->heap_size--;
        heapify(arr, hctx, 0);
    }
}

void printarr(int *arr, size_t len) {
    for(int i = 0; i < len; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

