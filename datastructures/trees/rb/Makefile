CC=gcc
FLAGS=-Wall -fstack-protector
SOURCES = rb.c

CFG=release
ifneq ($(CFG), release)
ifneq ($(CFG), debug)
	@echo "Invalid CFG specified. Valid options are:"
	@echo "release, debug"
endif
endif
ifeq ($(CFG), debug)
	FLAGS += -g3 -O0 -DDEBUG
else
	FLAGS += -O2
endif

.PHONY: all clean

all:
	$(CC) $(FLAGS) $(SOURCES) -o run

clean:
	rm run
