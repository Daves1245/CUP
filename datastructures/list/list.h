typedef struct list {
    list * next;
    list * previous;
    int data;
} node;

// creation and deletion
list * list_new();
void list_delete();

// modification
void list_insert(int data);
void list_remove(int data); 

list * list_find(int data);
