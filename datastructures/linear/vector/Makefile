CC=gcc
FLAGS=-Wall -I../../trees/include
SOURCES=bench_main.c vector.c

run:
	$(CC) $(FLAGS) $(SOURCES) -o run

demo:
	$(CC) $(FLAGS) main.c vector.c -o demo_run

clean:
	rm -f run demo_run