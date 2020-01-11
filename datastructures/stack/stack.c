#include "list.h"
#include "stack.h"

struct stack {
  struct list_head base;
};

void stack_new(stack *s) {
  LIST_INIT_HEAD(s->base); 
}

int stack_push(stack *s, void *data) {
   
}

void *stack_pop(stack *s) {
  if (stack_empty(s)) {
    return NULL;
  }
   
}

int stack_empty(stack *s) {
  return list_empty(s->base);
}

