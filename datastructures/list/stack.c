#include <stdlib.h>
#include <stdio.h>
#include "list.h"

static LIST_HEAD(stack);

struct elem {
        int data;
        struct list_head list;
} elem;

void stack_put(struct elem *e) {
       list_add(&e->list, &stack); 
}

struct elem *stack_pop() {
       struct elem *ret = list_entry(&stack, struct elem, list); 
       list_del(&ret->list);
        return ret;
}

int main(void)
{
        struct elem *a, *b, *c;
        a = malloc(sizeof(struct elem));
        b = malloc(sizeof(struct elem));
        c = malloc(sizeof(struct elem));
        a->data = 1;
        b->data = 2;
        c->data = 3;
        stack_put(a);
        stack_put(b);
        stack_put(c);
        free(a);
        free(b);
        free(c);
        return 0;
}
