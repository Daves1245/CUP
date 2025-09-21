#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "vector.h"
#include "../../trees/include/bench_common.h"

#define MAX_ITERATIONS 50
#define MAX_VECTOR_SIZE 100
#define MAX_ELEMENT_VALUE 1000

void benchmark_vector_operations(struct benchmark_config *config) {
    struct performance_stats add_stats, get_stats, set_stats, rm_stats;
    bench_init_stats(&add_stats, "Add");
    bench_init_stats(&get_stats, "Get");
    bench_init_stats(&set_stats, "Set");
    bench_init_stats(&rm_stats, "Remove");
    
    bench_print_section("Vector Add Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        vector *v = vector_new();
        
        /* Add elements */
        for (int j = 0; j < config->max_size; j++) {
            int *data = malloc(sizeof(int));
            *data = bench_rand_in_range(1, config->max_element_value);
            
            BENCH_START_TIMER(add_timer);
            vector_add(v, data);
            BENCH_END_TIMER(add_timer, &add_stats);
        }
        
        /* Verify size */
        if (vector_size(v) != config->max_size) {
            bench_print_test_case(i, config->max_iterations, "Add", TEST_FAILED);
            if (!config->compact_mode) {
                printf("\nVector size mismatch: expected %d, got %d\n", 
                       config->max_size, vector_size(v));
            }
            /* Clean up before exit */
            for (int k = 0; k < vector_size(v); k++) {
                free(vector_get(v, k));
            }
            vector_delete(v);
            exit(EXIT_FAILURE);
        }
        
        bench_print_test_case(i, config->max_iterations, "Add", TEST_PASSED);
        
        /* Clean up */
        for (int k = 0; k < vector_size(v); k++) {
            free(vector_get(v, k));
        }
        vector_delete(v);
    }
    
    bench_finalize_stats(&add_stats);
    bench_print_stats(&add_stats);
    
    bench_print_section("Vector Get Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        vector *v = vector_new();
        
        /* Build vector */
        for (int j = 0; j < config->max_size; j++) {
            int *data = malloc(sizeof(int));
            *data = j + 1;
            vector_add(v, data);
        }
        
        /* Get elements */
        int get_count = config->max_size < 10 ? config->max_size : config->max_size / 10;
        for (int j = 0; j < get_count; j++) {
            int index = bench_rand_in_range(0, config->max_size - 1);
            
            BENCH_START_TIMER(get_timer);
            void *elem = vector_get(v, index);
            BENCH_END_TIMER(get_timer, &get_stats);
            
            if (!elem) {
                bench_print_test_case(i, config->max_iterations, "Get", TEST_FAILED);
                if (!config->compact_mode) {
                    printf("\nGet operation failed for index %d\n", index);
                }
                /* Clean up before exit */
                for (int k = 0; k < vector_size(v); k++) {
                    free(vector_get(v, k));
                }
                vector_delete(v);
                exit(EXIT_FAILURE);
            }
        }
        
        bench_print_test_case(i, config->max_iterations, "Get", TEST_PASSED);
        
        /* Clean up */
        for (int k = 0; k < vector_size(v); k++) {
            free(vector_get(v, k));
        }
        vector_delete(v);
    }
    
    bench_finalize_stats(&get_stats);
    bench_print_stats(&get_stats);
    
    bench_print_section("Vector Set Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        vector *v = vector_new();
        
        /* Build vector */
        for (int j = 0; j < config->max_size; j++) {
            int *data = malloc(sizeof(int));
            *data = j + 1;
            vector_add(v, data);
        }
        
        /* Set elements */
        int set_count = config->max_size < 10 ? config->max_size : config->max_size / 10;
        for (int j = 0; j < set_count; j++) {
            int index = bench_rand_in_range(0, config->max_size - 1);
            int *new_data = malloc(sizeof(int));
            *new_data = bench_rand_in_range(1, config->max_element_value);
            
            /* Free old data before setting new */
            free(vector_get(v, index));
            
            BENCH_START_TIMER(set_timer);
            vector_set(v, index, new_data);
            BENCH_END_TIMER(set_timer, &set_stats);
        }
        
        bench_print_test_case(i, config->max_iterations, "Set", TEST_PASSED);
        
        /* Clean up */
        for (int k = 0; k < vector_size(v); k++) {
            free(vector_get(v, k));
        }
        vector_delete(v);
    }
    
    bench_finalize_stats(&set_stats);
    bench_print_stats(&set_stats);
    
    bench_print_section("Vector Remove Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        vector *v = vector_new();
        
        /* Build vector */
        for (int j = 0; j < config->max_size; j++) {
            int *data = malloc(sizeof(int));
            *data = j + 1;
            vector_add(v, data);
        }
        
        int original_size = vector_size(v);
        int remove_count = config->max_size < 10 ? config->max_size / 2 : config->max_size / 10;
        
        /* Remove elements */
        for (int j = 0; j < remove_count; j++) {
            if (vector_empty(v)) break;
            
            int index = bench_rand_in_range(0, vector_size(v) - 1);
            
            /* Free the element before removing */
            free(vector_get(v, index));
            
            BENCH_START_TIMER(rm_timer);
            vector_rm(v, index);
            BENCH_END_TIMER(rm_timer, &rm_stats);
        }
        
        /* Verify size reduction */
        if (vector_size(v) != original_size - remove_count) {
            bench_print_test_case(i, config->max_iterations, "Remove", TEST_FAILED);
            if (!config->compact_mode) {
                printf("\nSize mismatch after removals: expected %d, got %d\n", 
                       original_size - remove_count, vector_size(v));
            }
            /* Clean up before exit */
            for (int k = 0; k < vector_size(v); k++) {
                free(vector_get(v, k));
            }
            vector_delete(v);
            exit(EXIT_FAILURE);
        }
        
        bench_print_test_case(i, config->max_iterations, "Remove", TEST_PASSED);
        
        /* Clean up */
        for (int k = 0; k < vector_size(v); k++) {
            free(vector_get(v, k));
        }
        vector_delete(v);
    }
    
    bench_finalize_stats(&rm_stats);
    bench_print_stats(&rm_stats);
    
    bench_print_summary_header();
    bench_print_summary_line(&add_stats);
    bench_print_summary_line(&get_stats);
    bench_print_summary_line(&set_stats);
    bench_print_summary_line(&rm_stats);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    /* Initialize benchmark configuration */
    struct benchmark_config config;
    bench_init_config(&config, MAX_ITERATIONS, MAX_VECTOR_SIZE, MAX_ELEMENT_VALUE);
    bench_parse_args(&config, argc, argv);
    bench_init_terminal(&config);
    
    bench_print_header("VECTOR", &config);
    benchmark_vector_operations(&config);
    
    return 0;
}