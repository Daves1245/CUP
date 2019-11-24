#include <stdlib.h>
#include <stdio.h>
#include "list.h"

/*
 * @author David Santamaria
 * An implementation of the stack data structure using the linux kernel's linked list
 *  
 * This implementation 
 *
 */

static LIST_HEAD(stack);

struct elem {
	void *data;
	struct list_head stack;
};

void stack_push(struct elem *e)
{
	list_add(&e->stack, &stack);
}

struct elem *stack_pop()
{
	struct elem *ret = list_entry(stack.prev, struct elem, stack);
	/* Check if the stack is empty. This prevents us from accidentally deleting the stack */
	if (&ret->stack == ret->stack.prev || ret == NULL) { 
		return NULL;
	}
	list_del(&ret->stack);
	return ret;
}

