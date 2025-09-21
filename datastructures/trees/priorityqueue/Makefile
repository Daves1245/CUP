CC=gcc
FLAGS=-Wall -I../include
SOURCES=bench_main.c priority_queue.c

all:
	$(CC) $(FLAGS) $(SOURCES) -o run

demo:
	$(CC) $(FLAGS) main.c priority_queue.c -o demo_run

clean:
	rm -f run demo_run