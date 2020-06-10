CC=gcc
SOURCE=heap.c
FLAGS=-lm
CFG=release

ifneq ($(CFG),debug)
ifneq ($(CFG),release)
	@echo "Invalid CFG. Try 'debug' or 'release'"
endif
endif

ifeq ($(CFG), debug)
	FLAGS+=-g3 -O0
endif

all:
	$(CC) $(SOURCE) -o run $(FLAGS)
clean:
	rm run
