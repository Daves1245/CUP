#define STACK_INIT_CAPACITY 4

typedef struct stack {
        void ** items;
        int size;
        int capacity;
} stack;

void stack_init(stack *s);
static void stack_resize(stack *s, int capacity);
void stack_put(stack *s, void * item);
void * stack_pop(stack *s);
int stack_size(stack *s);
int stack_empty(stack *s);
void stack_free(stack *s);

