#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>

#include "list.h"
#include "../../trees/include/bench_common.h"

#define MAX_ITERATIONS 100
#define MAX_LIST_SIZE 1000
#define MAX_ELEMENT_VALUE 10000

struct element {
    int data;
    struct list_head list;
};

struct element *create_element(int value) {
    struct element *elem = malloc(sizeof(struct element));
    if (!elem) {
        fprintf(stderr, "Failed to allocate memory for element\n");
        exit(EXIT_FAILURE);
    }
    elem->data = value;
    INIT_LIST_HEAD(&elem->list);
    return elem;
}

void free_list(struct list_head *head) {
    struct list_head *pos, *n;
    list_for_each_safe(pos, n, head) {
        struct element *elem = list_entry(pos, struct element, list);
        list_del(pos);
        free(elem);
    }
}

int count_elements(struct list_head *head) {
    int count = 0;
    struct list_head *pos;
    list_for_each(pos, head) {
        count++;
    }
    return count;
}

void benchmark_list_operations(struct benchmark_config *config) {
    LIST_HEAD(test_list);
    
    struct performance_stats add_stats, del_stats, search_stats;
    bench_init_stats(&add_stats, "Add");
    bench_init_stats(&del_stats, "Delete");
    bench_init_stats(&search_stats, "Search");
    
    bench_print_section("List Add Operations");
    
    // Test list additions
    for (int i = 1; i <= config->max_iterations; i++) {
        for (int j = 0; j < config->max_size; j++) {
            int value = bench_rand_in_range(1, config->max_element_value);
            struct element *elem = create_element(value);
            
            BENCH_START_TIMER(add_timer);
            list_add(&elem->list, &test_list);
            BENCH_END_TIMER(add_timer, &add_stats);
        }
        
        bench_print_test_case(i, config->max_iterations, "Add", TEST_PASSED);
        
        // Clean up for next iteration
        free_list(&test_list);
    }
    
    bench_finalize_stats(&add_stats);
    bench_print_stats(&add_stats);
    
    bench_print_section("List Delete Operations");
    
    // Test list deletions
    for (int i = 1; i <= config->max_iterations; i++) {
        // First populate the list
        for (int j = 0; j < config->max_size; j++) {
            struct element *elem = create_element(j);
            list_add(&elem->list, &test_list);
        }
        
        // Now delete elements
        for (int j = 0; j < config->max_size && !list_empty(&test_list); j++) {
            struct element *elem = list_first_entry(&test_list, struct element, list);
            
            BENCH_START_TIMER(del_timer);
            list_del(&elem->list);
            free(elem);
            BENCH_END_TIMER(del_timer, &del_stats);
        }
        
        bench_print_test_case(i, config->max_iterations, "Delete", TEST_PASSED);
    }
    
    bench_finalize_stats(&del_stats);
    bench_print_stats(&del_stats);
    
    bench_print_section("List Search Operations");
    
    // Test list search
    for (int i = 1; i <= config->max_iterations; i++) {
        // Populate list with known values
        for (int j = 0; j < config->max_size; j++) {
            struct element *elem = create_element(j);
            list_add(&elem->list, &test_list);
        }
        
        // Search for elements
        for (int j = 0; j < config->max_size / 10; j++) { // Search fewer times
            int target = bench_rand_in_range(0, config->max_size - 1);
            struct element *found = NULL;
            
            BENCH_START_TIMER(search_timer);
            struct list_head *pos;
            list_for_each(pos, &test_list) {
                struct element *elem = list_entry(pos, struct element, list);
                if (elem->data == target) {
                    found = elem;
                    break;
                }
            }
            BENCH_END_TIMER(search_timer, &search_stats);
        }
        
        bench_print_test_case(i, config->max_iterations, "Search", TEST_PASSED);
        
        // Clean up
        free_list(&test_list);
    }
    
    bench_finalize_stats(&search_stats);
    bench_print_stats(&search_stats);
    
    bench_print_summary_header();
    bench_print_summary_line(&add_stats);
    bench_print_summary_line(&del_stats);
    bench_print_summary_line(&search_stats);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    /* Initialize benchmark configuration */
    struct benchmark_config config;
    bench_init_config(&config, MAX_ITERATIONS, MAX_LIST_SIZE, MAX_ELEMENT_VALUE);
    bench_parse_args(&config, argc, argv);
    bench_init_terminal(&config);
    
    bench_print_header("LINKED LIST", &config);
    benchmark_list_operations(&config);
    
    return 0;
}