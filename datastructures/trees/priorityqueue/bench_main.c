#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "priority_queue.h"
#include "../include/bench_common.h"

#define MAX_ITERATIONS 50
#define MAX_QUEUE_SIZE 100
#define MAX_ELEMENT_VALUE 1000
#define MAX_PRIORITY 10

int verify_priority_order(priority_queue *q) {
    if (pq_empty(q)) return 1;
    
    priority_queue *temp_q = pq_new();
    int last_priority = 0;
    int valid = 1;
    
    /* Extract all elements to check ordering */
    while (!pq_empty(q)) {
        int current_priority = pq_peek(q);
        if (current_priority < last_priority) {
            valid = 0;
            break;
        }
        pq_push(temp_q, pq_pop(q), current_priority);
        last_priority = current_priority;
    }
    
    /* Restore original queue */
    while (!pq_empty(temp_q)) {
        int data = pq_pop(temp_q);
        /* Note: we lose priority info here, but that's okay for this test */
        pq_push(q, data, data % MAX_PRIORITY + 1);
    }
    
    pq_delete(temp_q);
    return valid;
}

void benchmark_pq_operations(struct benchmark_config *config) {
    struct performance_stats push_stats, pop_stats, peek_stats;
    bench_init_stats(&push_stats, "Push");
    bench_init_stats(&pop_stats, "Pop");
    bench_init_stats(&peek_stats, "Peek");
    
    bench_print_section("Priority Queue Push Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        priority_queue *pq = pq_new();
        
        /* Push elements with random priorities */
        for (int j = 0; j < config->max_size; j++) {
            int data = bench_rand_in_range(1, config->max_element_value);
            int priority = bench_rand_in_range(1, MAX_PRIORITY);
            
            BENCH_START_TIMER(push_timer);
            pq_push(pq, data, priority);
            BENCH_END_TIMER(push_timer, &push_stats);
        }
        
        /* Verify queue is not empty */
        if (pq_empty(pq)) {
            bench_print_test_case(i, config->max_iterations, "Push", TEST_FAILED);
            if (!config->compact_mode) {
                printf("\\nQueue is empty after insertions!\\n");
            }
            pq_delete(pq);
            exit(EXIT_FAILURE);
        }
        
        bench_print_test_case(i, config->max_iterations, "Push", TEST_PASSED);
        pq_delete(pq);
    }
    
    bench_finalize_stats(&push_stats);
    bench_print_stats(&push_stats);
    
    bench_print_section("Priority Queue Peek Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        priority_queue *pq = pq_new();
        
        /* Build queue */
        for (int j = 0; j < config->max_size; j++) {
            int data = j + 1;
            int priority = bench_rand_in_range(1, MAX_PRIORITY);
            pq_push(pq, data, priority);
        }
        
        /* Peek at elements */
        int peek_count = config->max_size < 10 ? config->max_size : config->max_size / 10;
        for (int j = 0; j < peek_count; j++) {
            BENCH_START_TIMER(peek_timer);
            int top = pq_peek(pq);
            BENCH_END_TIMER(peek_timer, &peek_stats);
            
            if (top < 0) {  /* Assuming peek returns negative on error */
                bench_print_test_case(i, config->max_iterations, "Peek", TEST_FAILED);
                if (!config->compact_mode) {
                    printf("\\nPeek operation failed!\\n");
                }
                pq_delete(pq);
                exit(EXIT_FAILURE);
            }
        }
        
        bench_print_test_case(i, config->max_iterations, "Peek", TEST_PASSED);
        pq_delete(pq);
    }
    
    bench_finalize_stats(&peek_stats);
    bench_print_stats(&peek_stats);
    
    bench_print_section("Priority Queue Pop Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        priority_queue *pq = pq_new();
        
        /* Build queue */
        for (int j = 0; j < config->max_size; j++) {
            int data = j + 1;
            int priority = bench_rand_in_range(1, MAX_PRIORITY);
            pq_push(pq, data, priority);
        }
        
        /* Pop elements */
        for (int j = 0; j < config->max_size; j++) {
            if (pq_empty(pq)) break;
            
            BENCH_START_TIMER(pop_timer);
            int popped = pq_pop(pq);
            BENCH_END_TIMER(pop_timer, &pop_stats);
            
            if (popped < 0) {  /* Assuming pop returns negative on error */
                bench_print_test_case(i, config->max_iterations, "Pop", TEST_FAILED);
                if (!config->compact_mode) {
                    printf("\\nPop operation failed!\\n");
                }
                pq_delete(pq);
                exit(EXIT_FAILURE);
            }
        }
        
        /* Verify queue is empty */
        if (!pq_empty(pq)) {
            bench_print_test_case(i, config->max_iterations, "Pop", TEST_FAILED);
            if (!config->compact_mode) {
                printf("\\nQueue not empty after popping all elements!\\n");
            }
            pq_delete(pq);
            exit(EXIT_FAILURE);
        }
        
        bench_print_test_case(i, config->max_iterations, "Pop", TEST_PASSED);
        pq_delete(pq);
    }
    
    bench_finalize_stats(&pop_stats);
    bench_print_stats(&pop_stats);
    
    bench_print_summary_header();
    bench_print_summary_line(&push_stats);
    bench_print_summary_line(&peek_stats);
    bench_print_summary_line(&pop_stats);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    /* Initialize benchmark configuration */
    struct benchmark_config config;
    bench_init_config(&config, MAX_ITERATIONS, MAX_QUEUE_SIZE, MAX_ELEMENT_VALUE);
    bench_parse_args(&config, argc, argv);
    bench_init_terminal(&config);
    
    bench_print_header("PRIORITY QUEUE", &config);
    benchmark_pq_operations(&config);
    
    return 0;
}