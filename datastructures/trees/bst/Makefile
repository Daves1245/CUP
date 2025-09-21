CC=gcc
FLAGS=-Wall -I../include
SOURCES=bench_main.c bst.c

all:
	$(CC) $(FLAGS) $(SOURCES) -o run

demo:
	$(CC) $(FLAGS) main.c bst.c -o demo_run

clean:
	rm -f run demo_run