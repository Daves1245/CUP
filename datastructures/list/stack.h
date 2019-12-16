#include <stdlib.h>
#include <stdio.h>

#include "list.h"

static LIST_HEAD(stack);

struct elem {
	int data;
	struct list_head list;
};

void stack_push(struct elem *e)
{
	list_add(&e->list, &stack);
}

struct elem *stack_pop()
{
	struct elem *ret = list_entry(stack.prev, struct elem, list);
	if (&ret->list == ret->list.prev || ret == NULL) {
		return NULL;
	}
	list_del(&ret->list);
	return ret;
}

