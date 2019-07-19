#include <stdio.h>
#include "stack.h"
#include <errno.h>

int main(void)
{
    stack s;
    stack_init(&s);

    for (int i = 0; i < 100; i++) {
        int x = i * i;
        stack_put(&s, &x);
    }

    while (!stack_empty(&s)) {
        printf("%d ", * (int *) stack_pop(&s));
    }

    stack_free(&s);
    return 0;
}

