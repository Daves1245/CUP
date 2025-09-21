#include <stdlib.h>
#include <stdio.h>
#include <time.h>
#include <string.h>

#include "heap.h"
//#include "util.h"
#include "benchmarking.h"
#include "../include/bench_common.h"

#define ITERATIONS 200

int real_ge(int a, int b) {
    return a >= b;
}

int real_le(int a, int b) {
    return a <= b;
}

int ge_wrapper(void *a, void *b) {
    return *((int *) a) >= *((int *) b);
}

int le_wrapper(void *a, void *b) {
    return *((int *) a) <= *((int *) b);
}

int main(int argc, char **argv) {
    int *arr, tmp;
    
    /* Initialize benchmark configuration */
    struct benchmark_config config;
    bench_init_config(&config, ITERATIONS, ITERATIONS, HEAP_MAX_ELEM_VALUE);
    bench_parse_args(&config, argc, argv);
    bench_init_terminal(&config);
    
    struct sort_context sctx = {
        .arr = NULL,
        .len = config.max_size,
        .comp = real_le
    };

    struct heap ctx = {
        NULL,
        config.max_size,
        config.max_size,
        real_ge         /* We should be* sort in decreasing order
                           i.e. arr[i] < arr[i + 1] for 
                           all elements in the array */
    };

    srand(time(NULL));
    arr = assurealloc(sizeof(int) * (ctx.arr_len + 1));
    memset(sctx.failed, -1, 3 * sizeof(int));
    ctx.arr = arr;
    
    /* Initialize performance statistics */
    struct performance_stats heapsort_stats, insert_stats, extract_stats;
    bench_init_stats(&heapsort_stats, "Heapsort");
    bench_init_stats(&insert_stats, "Insert");
    bench_init_stats(&extract_stats, "Extract");
    
    bench_print_header("HEAP", &config);
    
    bench_print_section("Heapsort check");
    for (int i = 1; i <= config.max_iterations; i++) {
        fill_randomly(arr, &ctx);
        
        BENCH_START_TIMER(heapsort_timer);
        heapsort(arr, &ctx);
        BENCH_END_TIMER(heapsort_timer, &heapsort_stats);
        
        if (!is_sorted(arr + 1, &sctx)) {
            bench_print_test_case(i, config.max_iterations, "Heapsort", TEST_FAILED);
            if (!config.compact_mode) {
                printf("\nNot sorted! Failed at indices %d and %d\n", sctx.failed[0], sctx.failed[1]);
                for (int j = 0; j < ctx.arr_len; j++) {
                    printf("%d ", arr[j]);
                }
                puts("");
            }
            exit(EXIT_FAILURE);
        } else {
            bench_print_test_case(i, config.max_iterations, "Heapsort", TEST_PASSED);
        }
    }
    bench_finalize_stats(&heapsort_stats);
    bench_print_stats(&heapsort_stats);
    bench_print_section("Insert check");

    for (int i = 1; i <= config.max_iterations; i++) {
        int most = -1; // greatest or least number

        memset(arr, 0, sizeof(int) * ctx.heap_size);
        ctx.heap_size = 0;

        for (int j = 0; j < ctx.arr_len; j++) {
            tmp = bench_rand_in_range(HEAP_MIN_ELEM_VALUE, HEAP_MAX_ELEM_VALUE);
            if (most < 0 || real_le(tmp, most)) {
                most = tmp;
            }
            
            BENCH_START_TIMER(insert_timer);
            heap_insert(arr, &ctx, tmp);
            BENCH_END_TIMER(insert_timer, &insert_stats);
            
            if (arr[ROOT] != most) {
                bench_print_test_case(i, config.max_iterations, "Insert", TEST_FAILED);
                if (!config.compact_mode) {
                    printf("\nRoot value mismatch! Expected: %d, Got: %d\n", most, arr[1]);
                    for (int k = 1; k <= ctx.heap_size; k++) {
                        printf("%d ", arr[k]);
                    }
                    puts("");
                }
                exit(EXIT_FAILURE);
            }
        }

        if (!is_heap(&ctx, &sctx)) {
            bench_print_test_case(i, config.max_iterations, "Insert", TEST_FAILED);
            if (!config.compact_mode) {
                printf("\nHeap property violated!\n");
                print_heap_err_diagnostics(&ctx, &sctx);
                for (int j = ROOT; j < ctx.arr_len; j++) {
                    printf("%d ", arr[j]);
                }
                puts("");
            }
            exit(EXIT_FAILURE);
        }
        bench_print_test_case(i, config.max_iterations, "Insert", TEST_PASSED);
    }
    bench_finalize_stats(&insert_stats);
    bench_print_stats(&insert_stats);

    if (!is_heap(&ctx, &sctx)) {
        printf("%sWARNING:%s Heap property violated before extract phase\n", 
               bench_color(ANSI_COLOR_YELLOW), bench_color(ANSI_COLOR_RESET));
    }
    bench_print_section("Remove check");
    for (int i = 1; i <= config.max_iterations && ctx.heap_size > 0; i++) {
        BENCH_START_TIMER(extract_timer);
        int extracted = heap_pop(arr, &ctx);
        BENCH_END_TIMER(extract_timer, &extract_stats);
        
        if (!is_heap(&ctx, &sctx)) {
            bench_print_test_case(i, config.max_iterations, "Extract", TEST_FAILED);
            if (!config.compact_mode) {
                printf("\nExtract violated heap property\n");
                print_heap_err_diagnostics(&ctx, &sctx);
                for (int j = 1; j <= ctx.heap_size; j++) {
                    printf("%d ", arr[j]);
                }
                puts("");
            }
            exit(EXIT_FAILURE);
        } else {
            bench_print_test_case(i, config.max_iterations, "Extract", TEST_PASSED);
        }
    }
    
    bench_finalize_stats(&extract_stats);
    bench_print_stats(&extract_stats);
    
    bench_print_summary_header();
    bench_print_summary_line(&heapsort_stats);
    bench_print_summary_line(&insert_stats);
    bench_print_summary_line(&extract_stats);
    
    exit(EXIT_SUCCESS);
}

