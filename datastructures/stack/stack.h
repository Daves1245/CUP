#ifndef STACK_H
#define STACK_H
#define STACK_INIT_CAPACITY 4
#define STACK_TYPE void*

/* The stack structure */
typedef struct stack {
        void ** items;
        int size;
        int capacity;
} stack;

/* Stack creation/deletion - Memory management */
// Return a pointer to a newly created stack
stack * stack_new();
// Free memory pointed to by a stack pointer
void stack_delete(stack *s);

/* Non-modifiers of stack */
// Resize the stack
int stack_resize(stack *s, int capacity);
// Grab the stack size
int stack_size(stack *s);
// Check if stack is empty
// (equivalent to stack_size(s) == 0)
int stack_empty(stack *s);

/* Stack modifiers - change the state of the stack */
// Put an element on the top of the stack
int stack_put(stack *s, void * item);
// Pop the top most element of the stack
void * stack_pop(stack *s);

#endif
