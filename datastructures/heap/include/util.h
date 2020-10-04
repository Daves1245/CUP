#ifndef UTIL_H
#define UTIL_H

#include "../heap.h"

/* Swap two elements in an array */
void swap(int *arr, int a, int b);

/* get a random number within a range */
int rand_in_range(int min, int max);

/* fill a an array with random values (within the heap's min and max element values) */
void fill_with_random(int *arr, struct heap *ctx);

/* exit if memory is not properly allocated. Avoids SEGFAULTs*/
void *assurealloc(size_t len);

/* Check if an array is sorted */
int sort_check(void *arr, int arrlen, size_t elem_size, int (*comp)(void *, void *));

int is_heap(void *arr, int arrlen, size_t elem_size, int (*comp)(void *, void *));

#endif
