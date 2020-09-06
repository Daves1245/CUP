#include <string.h>
#include <stdio.h>
#include <time.h>
#include <stdlib.h>

#include "heap.h"

#define HEAP_SIZE 100
#define HEAP_MAX_ELEM_VALUE 1000
#define ROOT 1

void swap(int *arr, int a, int b) {
    int tmp = arr[a];
    arr[a] = arr[b];
    arr[b] = tmp;
}

int randval(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

void fill_with_random(int *arr, struct heap_context *actx) {
    arr[0] = -1;
    for (int i = ROOT; i <= actx->arr_len; i++) {
        arr[i] = randval(actx->min_elem_val, actx->max_elem_val);
    }
}

int greater(int a, int b) {
    return a > b;
}

int lesser(int a, int b) {
    return a < b;
}

void *assurealloc(size_t len) {
    void *p = malloc(len);
    if (!p) {
        fprintf(stderr, "[assurealloc]: failed to allocate memory.\nAbort.\n");
        exit(EXIT_FAILURE);
    }
}

/* Driver - test heapsort algorithm */
int main(int argc, char **argv) {
    int *arr;
    struct heap_context ctx = {
        HEAP_SIZE,
        HEAP_SIZE,
        HEAP_MAX_ELEM_VALUE,
        0,
        greater
    };
    srand(time(NULL));

    if (argc > 1) {
        ctx.arr_len = atoi(argv[1]);
    }
    if (argc > 2) {
        ctx.max_elem_val = atoi(argv[2]);
    }
    if (argc > 3) {
        ctx.min_elem_val = atoi(argv[3]);
    }

    arr = assurealloc(sizeof(int) * (ctx.heap_size + 1));
    fill_with_random(arr, &ctx);
    heapsort(arr, &ctx);
    for (int i = ROOT; i <= ctx.arr_len; i++) {
        printf("%d ", arr[i]);
    }
    puts("Checking if array is sorted... ");
    for (int i = ROOT; i < ctx.arr_len; i++) {
        if (arr[i] > arr[i] + 1) {
            puts("FAILED!");
            exit(EXIT_FAILURE);
        }
    }
    puts("PASSED!");
    exit(EXIT_SUCCESS);
}

int parent(int i) {
    return i / 2;
}

int left(int i) {
    return 2 * i;
}

int right(int i) {
    return 2 * i + 1;
}

/* Heapify an array */
void heapify(int *arr, struct heap_context *hctx, int i) {
    int swapi = i;

    if (left(i) <= hctx->heap_size && hctx->comp(arr[left(i)], arr[i])) {
        swapi = left(i);
    }

    if (right(i) <= hctx->heap_size && hctx->comp(arr[right(i)], arr[swapi])) {
        swapi = right(i);
    }

    if (i != swapi) {
        swap(arr, i, swapi);
        heapify(arr, hctx, swapi);
    }
}

void percolateDown(int *arr, struct heap_context *hctx, int i) {
    int swapi = i;
    if (left(i) <= hctx->heap_size && hctx->comp(arr[left(i)], arr[i])) {
        swapi = left(i);
    }
    if (right(i) <= hctx->heap_size && hctx->comp(arr[right(i)], arr[swapi])) {
        swapi = right(i);
    }

    if (i != swapi) {
        swap(arr, i, swapi);
        percolateDown(arr, hctx, swapi);
    }
}

int *insert(int *arr, struct heap_context *hctx, int i) {
    if (hctx->heap_size == hctx->arr_len) {
        return NULL;
    }

    
}

void percolateUp(int *arr, struct heap_context *hctx, int i) {
    while (i != ROOT && hctx->comp(arr[parent(i)], arr[i])) {
        swap(arr, i, parent(i));
        i = parent(i);
    }
}

/* Build a heap from an unsorted array */
void build_heap(int *arr, struct heap_context *hctx) {
    hctx->heap_size = hctx->arr_len;
    for (int i = hctx->heap_size; i >= ROOT; i--) {
        percolateDown(arr, hctx, i);
    }
}

/* Sort using heap */
void heapsort(int *arr, struct heap_context *hctx) {
    build_heap(arr, hctx);
    for (int i = hctx->arr_len; i >= ROOT; i--) {
        swap(arr, i, ROOT);
        hctx->heap_size--;
        percolateDown(arr, hctx, ROOT);
    }
}
