CC=gcc
FLAGS=-Wall -Itrees/include

# Main unified benchmark
all: bench_all

bench_all: bench_all.c trees/include/bench_common.h
	$(CC) $(FLAGS) bench_all.c -o bench_all

# Build individual benchmarks
build-all:
	@echo "Building all individual benchmarks..."
	@cd trees/heap && make clean && make
	@cd trees/rb && make clean && make  
	@cd trees/bst && make clean && make
	@cd linear/list && make clean && make
	@cd linear/vector && make clean && make
	@echo "All benchmarks built successfully!"

# Run all benchmarks
run: bench_all build-all
	./bench_all

# Run with compact mode
run-compact: bench_all build-all
	./bench_all --compact

# Clean everything
clean:
	rm -f bench_all
	@cd trees/heap && make clean 2>/dev/null || true
	@cd trees/rb && make clean 2>/dev/null || true
	@cd trees/bst && make clean 2>/dev/null || true
	@cd linear/list && make clean 2>/dev/null || true
	@cd linear/vector && make clean 2>/dev/null || true

# Help target
help:
	@echo "Available targets:"
	@echo "  all          Build the unified benchmark runner"
	@echo "  build-all    Build all individual benchmarks"
	@echo "  run          Build and run all benchmarks"
	@echo "  run-compact  Build and run all benchmarks in compact mode"
	@echo "  clean        Clean all build artifacts"
	@echo "  help         Show this help message"
	@echo ""
	@echo "Usage examples:"
	@echo "  make run                    # Run all benchmarks"
	@echo "  make run-compact            # Run all in compact mode"
	@echo "  ./bench_all heap list       # Run only heap and list"
	@echo "  ./bench_all --compact bst   # Run BST in compact mode"

.PHONY: all build-all run run-compact clean help