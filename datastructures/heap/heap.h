#ifndef CUP_HEAP_H
#define CUP_HEAP_H

#define HEAP_SIZE 100
#define HEAP_MAX_ELEM_VALUE 1000
#define HEAP_MIN_ELEM_VALUE 1
#define ROOT 1

struct heap_context {
    int arr_len;
    int heap_size;
    int (*comp)(int, int); /* comparator function */
};

struct abstract_heap_context {
    void *arr;
    int heap_size;
};

/* Pop max/min element from heap */
int heap_pop(int *arr, size_t len, int (*comp)(int, int));

/* Heapify an array */
void heapify(int *arr, struct heap_context *hctx, int i);
/* Build a heap with comparator func */
void build_heap(int *arr, struct heap_context *hctx);
/* Perculate an item down the heap */
void percolateDown(int *arr, struct heap_context *hctx, int i);
/* Perculate an item up the heap */
void percolateUp(int *arr, struct heap_context *hctx, int i);
/* Insert an element into the heap */
int heap_insert(int *arr, struct heap_context *hctx, int val);
/* Delete an element from the heap */
int heap_extract(int *arr, struct heap_context *hctx);

/* Sort array using a heap */
void heapsort(int *arr, struct heap_context *hctx);

#endif
