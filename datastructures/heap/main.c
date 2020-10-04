#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "heap.h"
#include "util.h"

#define ITERATIONS 200

int real_ge(int a, int b) {
    return a >= b;
}

int real_le(int a, int b) {
    return a <= b;
}

int gt_wrapper(void *a, void *b) {
    return *((int *) a) >= *((int *) b);
}

int le_wrapper(void *a, void *b) {
    return *((int *) a) <= *((int *) b);
}

int main(int argc, char **argv) {
    int iterations = ITERATIONS;
    int *arr, tmp;

    struct heap ctx = {
        NULL,
        ITERATIONS,
        ITERATIONS,
        real_le         /* We sort in decreasing order
                           i.e. arr[i] < arr[i + 1] for 
                           all elements in the array */
    };

    if (argc > 1) {
        ctx.arr_len = ctx.heap_size = atoi(argv[1]);
    }
    if (argc > 2) {
        iterations = atoi(argv[2]);
    }

    srand(time(NULL));
    arr = assurealloc(sizeof(int) * (ctx.arr_len + 1));
    ctx.arr = arr;
    puts("Heapsort check: ");
    for (int i = 1; i <= iterations; i++) {
        printf("Test case %d/%d: ", i, iterations);
        fill_with_random(arr, &ctx);
        heapsort(arr, &ctx);
        if (!sort_check(arr, ctx.arr_len, sizeof(int), le_wrapper)) {
            exit(EXIT_FAILURE);
        } else {
            printf("PASSED!\r");
        }
    }
    puts("\nInsert check: ");

    for (int i = 1; i <= iterations; i++) {
        int most = -1; // greatest or least number

        memset(arr, 0, sizeof(int) * ctx.heap_size);
        ctx.heap_size = 0;

        printf("Test case %d/%d: ", i, iterations);
        for (int j = 0; j < ctx.arr_len; j++) {
            int tmp;

            tmp = rand_in_range(HEAP_MIN_ELEM_VALUE, HEAP_MAX_ELEM_VALUE);
            if (most < 0 || real_le(tmp, most)) {
                most = tmp;
            }
            heap_insert(arr, &ctx, tmp);
            if (arr[ROOT] != most) {
                fprintf(stderr, "FAILED!\n");
                printf("most is: %d and arr[1] is: %d\n", most, arr[1]);
                for (int i = 1; i <= ctx.heap_size; i++) {
                    printf("%d ", arr[i]);
                }
                puts("");
                exit(EXIT_FAILURE);
            }
        }

        if (!is_heap(arr, ctx.heap_size, sizeof(int), le_wrapper)) {
            fprintf(stderr, "FAILED!\nNot a heap!\n");
            for (int i = ROOT; i < ctx.arr_len; i++) {
                printf("%d ", arr[i]);
            }
            puts("");
            exit(EXIT_FAILURE);
        }
        printf("PASSED!\r");
    }

    if (!is_heap(arr, ctx.heap_size, sizeof(int), le_wrapper)) {
        printf("NOT A HEAP BEFORE EXTRACT!\n");
    }
    puts("\nRemove check: ");
    for (int i = 1; i <= iterations; i++) {
        printf("Test case %d/%d: ", i, iterations);
        // printf("Extracted %d from the heap\n", heap_extract(arr, &ctx));
        heap_pop(arr, &ctx);
        if (!is_heap(arr, ctx.arr_len, sizeof(int), le_wrapper)) {
            fprintf(stderr, "FAILED!\npop() violated the heap property\n");
            for (int i = 1; i <= ctx.heap_size; i++) {
                printf("%d ", arr[i]);
            }
            puts("");
            exit(EXIT_FAILURE);
        } else {
            printf("PASSED!\r");
        }
    }
    puts("");
    exit(EXIT_SUCCESS);
}

