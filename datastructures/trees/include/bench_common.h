#ifndef BENCH_COMMON_H
#define BENCH_COMMON_H

#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

/* ANSI Color codes */
#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"
#define ANSI_BOLD          "\x1b[1m"
#define ANSI_CLEAR_LINE    "\x1b[2K\r"

/* Global benchmark configuration */
static int bench_use_colors = 0;
static int bench_compact_mode = 0;

/* Color wrapper functions */
static inline const char* bench_color(const char* color) {
    return bench_use_colors ? color : "";
}

/* Common performance statistics structure */
struct performance_stats {
    double total_time;      /* Total time in milliseconds */
    double avg_time;        /* Average time per operation */
    int operations_count;   /* Number of operations performed */
    const char *operation_name; /* Name of the operation being measured */
};

/* Test result status */
enum test_status {
    TEST_PASSED,
    TEST_FAILED
};

/* Timing macros for consistent measurement */
#define BENCH_START_TIMER(timer) \
    clock_t timer = clock()

#define BENCH_END_TIMER(timer, stats) \
    do { \
        clock_t end_##timer = clock(); \
        double time_ms = (1000.0 * (double)(end_##timer - timer) / CLOCKS_PER_SEC); \
        (stats)->total_time += time_ms; \
        (stats)->operations_count++; \
    } while(0)

/* Initialize performance stats */
static inline void bench_init_stats(struct performance_stats *stats, const char *operation_name) {
    stats->total_time = 0.0;
    stats->avg_time = 0.0;
    stats->operations_count = 0;
    stats->operation_name = operation_name;
}

/* Finalize stats by calculating average */
static inline void bench_finalize_stats(struct performance_stats *stats) {
    if (stats->operations_count > 0) {
        stats->avg_time = stats->total_time / stats->operations_count;
    } else {
        stats->avg_time = 0.0;
    }
}

/* Print performance statistics */
static inline void bench_print_stats(const struct performance_stats *stats) {
    if (bench_compact_mode) {
        printf("\n");
    }
    if (stats->operations_count > 0) {
        printf("%s%s%s Performance:%s Total=%s%.2fms%s, Avg=%s%.6fms%s, Operations=%s%d%s\n", 
               bench_color(ANSI_BOLD), bench_color(ANSI_COLOR_CYAN),
               stats->operation_name, bench_color(ANSI_COLOR_RESET),
               bench_color(ANSI_COLOR_GREEN), stats->total_time, bench_color(ANSI_COLOR_RESET),
               bench_color(ANSI_COLOR_GREEN), stats->avg_time, bench_color(ANSI_COLOR_RESET),
               bench_color(ANSI_COLOR_YELLOW), stats->operations_count, bench_color(ANSI_COLOR_RESET));
    } else {
        printf("%s%s%s Performance:%s No operations performed\n", 
               bench_color(ANSI_BOLD), bench_color(ANSI_COLOR_CYAN),
               stats->operation_name, bench_color(ANSI_COLOR_RESET));
    }
}

/* Print a summary line for final reporting */
static inline void bench_print_summary_line(const struct performance_stats *stats) {
    if (stats->operations_count > 0) {
        printf("%s%-12s%s %s%.6fms%s avg (over %s%d%s operations)\n", 
               bench_color(ANSI_COLOR_CYAN), stats->operation_name, bench_color(ANSI_COLOR_RESET),
               bench_color(ANSI_COLOR_GREEN), stats->avg_time, bench_color(ANSI_COLOR_RESET),
               bench_color(ANSI_COLOR_YELLOW), stats->operations_count, bench_color(ANSI_COLOR_RESET));
    }
}

/* Print section header */
static inline void bench_print_section(const char* section_name) {
    if (bench_compact_mode) {
        printf("\n");
    }
    printf("%s%s%s:\n", bench_color(ANSI_COLOR_CYAN), section_name, bench_color(ANSI_COLOR_RESET));
}

/* Print final summary header */
static inline void bench_print_summary_header(void) {
    printf("\n%s%s=== PERFORMANCE SUMMARY ===%s\n", 
           bench_color(ANSI_BOLD), bench_color(ANSI_COLOR_BLUE), bench_color(ANSI_COLOR_RESET));
}

/* Generate random number in range (common utility) */
static inline int bench_rand_in_range(int min, int max) {
    return min + rand() / (RAND_MAX / (max - min + 1) + 1);
}

/* Common benchmark configuration structure */
struct benchmark_config {
    int max_iterations;     /* Number of test iterations */
    int max_size;          /* Maximum size of data structure */
    int max_element_value; /* Maximum value for elements */
    int verbose;           /* Verbosity level */
    int compact_mode;      /* Compact display mode */
    int use_colors;        /* Enable color output */
};

/* Initialize color and terminal support */
static inline void bench_init_terminal(struct benchmark_config *config) {
    /* Check if stdout is a terminal and colors are requested */
    config->use_colors = isatty(STDOUT_FILENO);
    bench_use_colors = config->use_colors;
    bench_compact_mode = config->compact_mode;
}

static inline void bench_print_status(enum test_status status, const char* message) {
    if (status == TEST_PASSED) {
        printf("%s%s[PASSED]%s %s", 
               bench_color(ANSI_BOLD), 
               bench_color(ANSI_COLOR_GREEN), 
               bench_color(ANSI_COLOR_RESET), 
               message ? message : "");
    } else {
        printf("%s%s[FAILED]%s %s", 
               bench_color(ANSI_BOLD), 
               bench_color(ANSI_COLOR_RED), 
               bench_color(ANSI_COLOR_RESET), 
               message ? message : "");
    }
}

/* Print test case progress */
static inline void bench_print_test_case(int current, int total, const char* test_name, enum test_status status) {
    if (bench_compact_mode) {
        printf("%s", bench_color(ANSI_CLEAR_LINE));
    }
    
    printf("%s%s%s check - Test case %s%d/%d%s: ", 
           bench_color(ANSI_COLOR_CYAN), 
           test_name, 
           bench_color(ANSI_COLOR_RESET),
           bench_color(ANSI_COLOR_YELLOW),
           current, total,
           bench_color(ANSI_COLOR_RESET));
    
    bench_print_status(status, NULL);
    
    if (bench_compact_mode) {
        fflush(stdout);
    } else {
        printf("\n");
    }
}

/* Initialize benchmark config with defaults */
static inline void bench_init_config(struct benchmark_config *config, 
                                    int iterations, int size, int max_val) {
    config->max_iterations = iterations;
    config->max_size = size;
    config->max_element_value = max_val;
    config->verbose = 1;
    config->compact_mode = 0;
    config->use_colors = 0;
}

/* Parse command line arguments for common benchmark parameters */
static inline void bench_parse_args(struct benchmark_config *config, int argc, char **argv) {
    int arg_index = 1;
    
    /* Parse flags first */
    while (arg_index < argc && argv[arg_index][0] == '-') {
        if (strcmp(argv[arg_index], "--compact") == 0) {
            config->compact_mode = 1;
        } else if (strcmp(argv[arg_index], "--no-color") == 0) {
            config->use_colors = 0;
        }
        arg_index++;
    }
    
    /* Parse positional arguments */
    if (arg_index < argc) {
        config->max_size = atoi(argv[arg_index++]);
    }
    if (arg_index < argc) {
        config->max_iterations = atoi(argv[arg_index++]);
    }
    if (arg_index < argc) {
        config->max_element_value = atoi(argv[arg_index++]);
    }
}

/* Print benchmark header */
static inline void bench_print_header(const char *benchmark_name, 
                                     const struct benchmark_config *config) {
    printf("%s%s=== %s BENCHMARK ===%s\n", 
           bench_color(ANSI_BOLD), bench_color(ANSI_COLOR_BLUE),
           benchmark_name, bench_color(ANSI_COLOR_RESET));
    printf("Iterations: %s%d%s, Size: %s%d%s, Max Value: %s%d%s\n", 
           bench_color(ANSI_COLOR_YELLOW), config->max_iterations, bench_color(ANSI_COLOR_RESET),
           bench_color(ANSI_COLOR_YELLOW), config->max_size, bench_color(ANSI_COLOR_RESET),
           bench_color(ANSI_COLOR_YELLOW), config->max_element_value, bench_color(ANSI_COLOR_RESET));
    if (config->compact_mode) {
        printf("Mode: %sCompact%s\n", bench_color(ANSI_COLOR_MAGENTA), bench_color(ANSI_COLOR_RESET));
    }
    printf("%s=====================================%s\n", 
           bench_color(ANSI_COLOR_BLUE), bench_color(ANSI_COLOR_RESET));
}

#endif /* BENCH_COMMON_H */