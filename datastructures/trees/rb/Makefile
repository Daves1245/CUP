CC=gcc
FLAGS=-Wall
SOURCES = rb.c

CFG=release
ifneq ($(CFG), release)
ifneq ($(CFG), debug)
	@echo "Invalid CFG specified. Valid options are:"
	@echo "release, debug"
endif
endif
ifeq ($(CFG), debug)
	FLAGS += -DDEBUG
endif

.PHONY: all clean

all:
	$(CC) $(FLAGS) $(SOURCES) -o run

clean:
	rm run
