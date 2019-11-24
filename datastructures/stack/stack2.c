/*
 * @author David Santamaria
 * An implementation of the stack data structure using the linux kernel's linked list
 *
 */

static LIST_HEAD(stack);

struct elem {
	void *data;
	struct list_head stack;
};

void stack_push_generic(void *data, list_head *stack)
{
	struct elem *e = malloc(sizeof(*e));
	e->data = data;
	e->stack = LIST_HEAD_INIT(&e->stack);
	list_add(&e->stack, stack);
}

inline void stack_push(struct elem *e)
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

void print_options()
{
	printf("1: Print stack\n"
			"2: Push to the stack\n"
			"3: Pop from the stack\n\n");
}

void print_stack()
{
	struct list_head *iterator;
	list_for_each(iterator, stack) {

	}
}

int main(void)
{
	int n;
	while (1) {
		print_options();
		scanf("%d", &n);
		if (n < 1 || n > 3) {
			printf("not a valid option\n");
			continue;
		}
		switch (n) {
			case 1:
				print_stack();
				break;
			case 2:
				stack_push(

		}
	}
	return 0;
}
