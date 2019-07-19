#include <stdlib.h>
#include "stack.h"
#include <stdio.h>
#include <errno.h>
#include <string.h>

void stack_init(stack *s)
{
    s->capacity = STACK_INIT_CAPACITY;
    s->size = 0;
    s->items = malloc(sizeof(void *) * s->capacity);
}

int stack_size(stack *s)
{
    return s->size;
}

static void stack_resize(stack *s, int capacity)
{
    #ifdef DEBUG_ON
    printf("stack resize: %d to %d\n", s->capacity, capacity);
    #endif

    void ** items = realloc(s->items, sizeof(void *) * capacity);
    if (items) {
        s->items = items;
        s->capacity = capacity;
    } else {
        fprintf(stderr, "stack: error while resizing");
    }
}

void stack_put(stack *s, void *item)
{
    if (s->size >= s->capacity) {
        stack_resize(s, s->capacity * 2);
    }
    s->items[s->size++] = item;
}

void * stack_pop(stack *s)
{
    if (s->size <= 0) {
        return NULL;
    }
    if (s->size < s->capacity / 4) {
        stack_resize(s, s->capacity / 2);
    }

    return s->items[--s->size];
}

int stack_empty(stack *s)
{
    return s->size == 0;
}

void stack_free(stack *s)
{
    s->size = s->capacity = 0;
    free(s->items);
}

void stack_debug_print_array(stack *s) {
    for (int i = 0; i < s->size; i++) {
        printf("%s", (const char *) s->items[i]);
    }
}
