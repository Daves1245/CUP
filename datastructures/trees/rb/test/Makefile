CC=gcc
FLAGS=-g -g3 -O0
SOURCES=rb_explicit.c

CFG=release
ifneq ($(CFG), release)
ifneq ($(CFG), debug)
	@echo "Invalid configuration"
	@echo "Valid options are CFG=release,debug"
endif
endif

ifeq ($(CFG), debug)
	FLAGS += -DDEBUG
endif

.PHONY: all clean

all:
	$(CC) $(FLAGS) $(SOURCES) -o run

clean:
	rm a

