#ifndef CUP_HEAP_H
#define CUP_HEAP_H

struct heap_context {
    int arr_len;
    int heap_size;
    int max_elem_val;
    int min_elem_val;
    int (*comp)(int, int); /* comparator function */
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

/* Sort array using a heap */
void heapsort(int *arr, struct heap_context *hctx);

#endif
