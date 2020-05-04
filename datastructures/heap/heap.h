#ifndef CUP_HEAP_H
#define CUP_HEAP_H

#define HEAP_SWAP(type, arr, i, j) \
    do { \
        type tmp = arr[i]; \
        arr[i] = arr[j]; \
        arr[j] = tmp; \
    } while (0);

// XXX
struct heap_context {
    void *heap;
    size_t size;
    int (*comp)(const void *, const void *);
};

/* Pop max/min element from heap */
int heap_pop(int *arr, size_t len, int (*comp)(int, int));

/* Heapify an array */
void heapify(int *arr, size_t len, unsigned i, int (*comp)(int, int));
/* Build a heap with comparator func */
void build_heap(int *arr, size_t len, int (*comp)(int, int));

/* Sort array using a heap */
void heapsort(int *arr, size_t len);

#endif
