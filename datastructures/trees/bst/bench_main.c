#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "bst.h"
#include "../include/bench_common.h"

#define MAX_ITERATIONS 50
#define MAX_TREE_SIZE 100
#define MAX_ELEMENT_VALUE 10000

void free_tree(node *root) {
    if (!root) return;
    free_tree(root->left);
    free_tree(root->right);
    
    /* Free linked list of duplicates */
    node *current = root->next;
    while (current) {
        node *temp = current;
        current = current->next;
        free(temp);
    }
    free(root);
}

int count_nodes(node *root) {
    if (!root) return 0;
    int count = 1;
    
    /* Count duplicates */
    node *current = root->next;
    while (current) {
        count++;
        current = current->next;
    }
    
    return count + count_nodes(root->left) + count_nodes(root->right);
}

int verify_bst_property(node *root, int min_val, int max_val) {
    if (!root) return 1;
    
    if (root->data < min_val || root->data > max_val) return 0;
    
    return verify_bst_property(root->left, min_val, root->data - 1) &&
           verify_bst_property(root->right, root->data + 1, max_val);
}

void benchmark_bst_operations(struct benchmark_config *config) {
    struct performance_stats insert_stats, search_stats;
    bench_init_stats(&insert_stats, "Insert");
    bench_init_stats(&search_stats, "Search");
    
    bench_print_section("BST Insert Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        node *root = bst_new(config->max_element_value / 2);
        
        /* Insert elements */
        for (int j = 0; j < config->max_size; j++) {
            int value = bench_rand_in_range(1, config->max_element_value);
            
            BENCH_START_TIMER(insert_timer);
            bst_insert(root, value);
            BENCH_END_TIMER(insert_timer, &insert_stats);
        }
        
        /* Verify BST property */
        if (!verify_bst_property(root, 1, config->max_element_value)) {
            bench_print_test_case(i, config->max_iterations, "Insert", TEST_FAILED);
            if (!config->compact_mode) {
                printf("\nBST property violated!\n");
            }
            free_tree(root);
            exit(EXIT_FAILURE);
        }
        
        bench_print_test_case(i, config->max_iterations, "Insert", TEST_PASSED);
        free_tree(root);
    }
    
    bench_finalize_stats(&insert_stats);
    bench_print_stats(&insert_stats);
    
    bench_print_section("BST Search Operations");
    
    for (int i = 1; i <= config->max_iterations; i++) {
        node *root = bst_new(config->max_element_value / 2);
        int *inserted_values = malloc(config->max_size * sizeof(int));
        
        /* Build tree with known values */
        for (int j = 0; j < config->max_size; j++) {
            inserted_values[j] = j + 1;
            bst_insert(root, inserted_values[j]);
        }
        
        /* Search for elements */
        int search_count = config->max_size < 10 ? config->max_size : config->max_size / 10;
        for (int j = 0; j < search_count; j++) {
            int target = inserted_values[bench_rand_in_range(0, config->max_size - 1)];
            
            BENCH_START_TIMER(search_timer);
            node *found = bst_find(root, target);
            BENCH_END_TIMER(search_timer, &search_stats);
            
            if (!found) {
                bench_print_test_case(i, config->max_iterations, "Search", TEST_FAILED);
                if (!config->compact_mode) {
                    printf("\nSearch failed for value %d\n", target);
                }
                free(inserted_values);
                free_tree(root);
                exit(EXIT_FAILURE);
            }
        }
        
        bench_print_test_case(i, config->max_iterations, "Search", TEST_PASSED);
        free(inserted_values);
        free_tree(root);
    }
    
    bench_finalize_stats(&search_stats);
    bench_print_stats(&search_stats);
    
    
    bench_print_summary_header();
    bench_print_summary_line(&insert_stats);
    bench_print_summary_line(&search_stats);
}

int main(int argc, char **argv) {
    srand(time(NULL));
    
    /* Initialize benchmark configuration */
    struct benchmark_config config;
    bench_init_config(&config, MAX_ITERATIONS, MAX_TREE_SIZE, MAX_ELEMENT_VALUE);
    bench_parse_args(&config, argc, argv);
    bench_init_terminal(&config);
    
    bench_print_header("BINARY SEARCH TREE", &config);
    benchmark_bst_operations(&config);
    
    return 0;
}