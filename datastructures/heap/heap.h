#ifndef CUP_HEAP_H
#define CUP_HEAP_H

#define HEAP_SWAP(type, arr, i, j) \
    do { \
        type tmp = arr[i]; \
        arr[i] = arr[j]; \
        arr[j] = tmp; \
    } while (0);

// XXX

struct node {
    struct node *left, *right, *parent;
    int data;
};

struct heap_context {
    int arr_len;
    int max_elem_val;
    int min_elem_val;
    int heap_size;
    int (*comp)(int, int); /* comparator function */
};

/* Pop max/min element from heap */
int heap_pop(int *arr, size_t len, int (*comp)(int, int));

/* Heapify an array */
void heapify(int *arr, struct heap_context *hctx, int i);
/* Build a heap with comparator func */
void build_heap(int *arr, struct heap_context *hctx);

/* Sort array using a heap */
void heapsort(int *arr, struct heap_context *hctx);

#endif
