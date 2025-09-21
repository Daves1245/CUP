#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <unistd.h>
#include <sys/wait.h>

#include "trees/include/bench_common.h"

struct benchmark_target {
    const char *name;
    const char *path;
    const char *description;
};

static struct benchmark_target benchmarks[] = {
    {"heap", "trees/heap", "Binary Heap (heapsort, insert, extract)"},
    {"rb", "trees/rb", "Red-Black Tree (insert, search, delete)"},
    {"bst", "trees/bst", "Binary Search Tree (insert, search)"},
    {"list", "linear/list", "Linked List (add, delete, search)"},
    {"vector", "linear/vector", "Dynamic Array (add, get, set, remove)"},
    {NULL, NULL, NULL}
};

void print_separator(char c, int width) {
    for (int i = 0; i < width; i++) {
        printf("%c", c);
    }
    printf("\n");
}

void print_usage(const char *program_name) {
    printf("Usage: %s [OPTIONS] [TARGETS]\n", program_name);
    printf("\nOPTIONS:\n");
    printf("  --compact         Enable compact mode for all benchmarks\n");
    printf("  --no-color        Disable colored output\n");
    printf("  --help            Show this help message\n");
    printf("\nTARGETS (if none specified, all will run):\n");

    for (int i = 0; benchmarks[i].name; i++) {
        printf("  %-8s          %s\n", benchmarks[i].name, benchmarks[i].description);
    }

    printf("\nEXAMPLES:\n");
    printf("  %s                    # Run all benchmarks\n", program_name);
    printf("  %s heap list          # Run only heap and list benchmarks\n", program_name);
    printf("  %s --compact heap     # Run heap benchmark in compact mode\n", program_name);
}

int run_benchmark(const char *name, const char *path, char **extra_args) {
    printf("\n");
    print_separator('=', 60);
    printf("%s RUNNING %s BENCHMARK %s\n",
           bench_color(ANSI_COLOR_CYAN), name, bench_color(ANSI_COLOR_RESET));
    print_separator('=', 60);

    char full_path[256];
    snprintf(full_path, sizeof(full_path), "%s/run", path);

    /* Check if benchmark executable exists */
    if (access(full_path, X_OK) != 0) {
        printf("%sError: Benchmark executable not found at %s%s\n",
               bench_color(ANSI_COLOR_RED), full_path, bench_color(ANSI_COLOR_RESET));
        printf("Please ensure the benchmark is built by running 'make' in %s\n", path);
        return 1;
    }

    pid_t pid = fork();
    if (pid == 0) {
        /* Child process - run the benchmark */
        if (chdir(path) != 0) {
            perror("chdir");
            exit(1);
        }

        /* Count extra arguments */
        int argc = 1;  /* ./run */
        if (extra_args) {
            while (extra_args[argc - 1]) argc++;
        }

        /* Build argv array */
        char **argv = malloc((argc + 1) * sizeof(char*));
        argv[0] = "./run";
        for (int i = 1; i < argc; i++) {
            argv[i] = extra_args[i - 1];
        }
        argv[argc] = NULL;

        execv("./run", argv);
        perror("execv");
        exit(1);
    } else if (pid > 0) {
        /* Parent process - wait for completion */
        int status;
        waitpid(pid, &status, 0);

        if (WIFEXITED(status)) {
            int exit_code = WEXITSTATUS(status);
            if (exit_code == 0) {
                printf("\n%s %s benchmark completed successfully%s\n",
                       bench_color(ANSI_COLOR_GREEN), name, bench_color(ANSI_COLOR_RESET));
                return 0;
            } else {
                printf("\n%s✗ %s benchmark failed (exit code: %d)%s\n",
                       bench_color(ANSI_COLOR_RED), name, exit_code, bench_color(ANSI_COLOR_RESET));
                return 1;
            }
        } else {
            printf("\n%s✗ %s benchmark terminated abnormally%s\n",
                   bench_color(ANSI_COLOR_RED), name, bench_color(ANSI_COLOR_RESET));
            return 1;
        }
    } else {
        perror("fork");
        return 1;
    }
}

int is_valid_target(const char *target) {
    for (int i = 0; benchmarks[i].name; i++) {
        if (strcmp(benchmarks[i].name, target) == 0) {
            return 1;
        }
    }
    return 0;
}

const char* get_benchmark_path(const char *name) {
    for (int i = 0; benchmarks[i].name; i++) {
        if (strcmp(benchmarks[i].name, name) == 0) {
            return benchmarks[i].path;
        }
    }
    return NULL;
}

int main(int argc, char **argv) {
    char **targets = NULL;
    int target_count = 0;
    char **extra_args = NULL;
    int extra_arg_count = 0;
    int show_help = 0;

    /* Parse command line arguments */
    for (int i = 1; i < argc; i++) {
        if (strcmp(argv[i], "--help") == 0 || strcmp(argv[i], "-h") == 0) {
            show_help = 1;
            break;
        } else if (strcmp(argv[i], "--compact") == 0 || strcmp(argv[i], "--no-color") == 0) {
            /* Add to extra args to pass to benchmarks */
            extra_args = realloc(extra_args, (extra_arg_count + 2) * sizeof(char*));
            extra_args[extra_arg_count] = argv[i];
            extra_arg_count++;
            extra_args[extra_arg_count] = NULL;
        } else {
            /* Check if it's a valid benchmark target */
            if (is_valid_target(argv[i])) {
                targets = realloc(targets, (target_count + 1) * sizeof(char*));
                targets[target_count] = argv[i];
                target_count++;
            } else {
                printf("Error: Unknown target '%s'\n", argv[i]);
                show_help = 1;
                break;
            }
        }
    }

    if (show_help) {
        print_usage(argv[0]);
        free(targets);
        free(extra_args);
        return 0;
    }

    /* Initialize terminal settings */
    struct benchmark_config config;
    bench_init_config(&config, 50, 100, 1000);  /* Default values */
    if (extra_args) {
        bench_parse_args(&config, extra_arg_count + 1, extra_args - 1);  /* Adjust for program name */
    }
    bench_init_terminal(&config);

    printf("%s", bench_color(ANSI_BOLD));
    printf("DATA STRUCTURES UNIFIED BENCHMARK SUITE\n");
    printf("%s", bench_color(ANSI_COLOR_RESET));
    print_separator('=', 60);

    if (target_count == 0) {
        printf("Running all available benchmarks...\n");
    } else {
        printf("Running selected benchmarks: ");
        for (int i = 0; i < target_count; i++) {
            printf("%s%s%s", targets[i], (i < target_count - 1) ? ", " : "",
                   i == target_count - 1 ? "\n" : "");
        }
    }

    if (extra_args && extra_arg_count > 0) {
        printf("Options: ");
        for (int i = 0; i < extra_arg_count; i++) {
            if (extra_args[i]) {
                printf("%s ", extra_args[i]);
            }
        }
        printf("\n");
    }

    clock_t start_time = clock();
    int failed_count = 0;
    int total_count = 0;

    if (target_count == 0) {
        /* Run all benchmarks */
        for (int i = 0; benchmarks[i].name; i++) {
            total_count++;
            if (run_benchmark(benchmarks[i].name, benchmarks[i].path, extra_args) != 0) {
                failed_count++;
            }
        }
    } else {
        /* Run selected benchmarks */
        for (int i = 0; i < target_count; i++) {
            const char *path = get_benchmark_path(targets[i]);
            if (path) {
                total_count++;
                if (run_benchmark(targets[i], path, extra_args) != 0) {
                    failed_count++;
                }
            }
        }
    }

    clock_t end_time = clock();
    double elapsed_time = (double)(end_time - start_time) / CLOCKS_PER_SEC;

    /* Print summary */
    printf("\n");
    print_separator('=', 60);
    printf("%s BENCHMARK SUITE SUMMARY %s\n",
           bench_color(ANSI_BOLD), bench_color(ANSI_COLOR_RESET));
    print_separator('=', 60);

    printf("Total benchmarks run: %d\n", total_count);
    printf("Successful: %s%d%s\n",
           bench_color(ANSI_COLOR_GREEN), total_count - failed_count, bench_color(ANSI_COLOR_RESET));

    if (failed_count > 0) {
        printf("Failed: %s%d%s\n",
               bench_color(ANSI_COLOR_RED), failed_count, bench_color(ANSI_COLOR_RESET));
    }

    printf("Total time: %.2f seconds\n", elapsed_time);

    if (failed_count == 0) {
        printf("\n%sAll benchmarks completed successfully!%s\n",
               bench_color(ANSI_COLOR_GREEN), bench_color(ANSI_COLOR_RESET));
    } else {
        printf("\n%sSome benchmarks failed. Check the output above for details.%s\n",
               bench_color(ANSI_COLOR_YELLOW), bench_color(ANSI_COLOR_RESET));
    }

    print_separator('=', 60);

    free(targets);
    free(extra_args);
    return failed_count > 0 ? 1 : 0;
}
