#include "list.h"

list * list_new()
{
    list * ret = malloc(sizeof(list));  
    ret->next = ret->previous = NULL;
    return ret;
}
void list_delete(list * node)
{
    if (node->next) {
        list_delete(node->next);
    }
    free(node);
}

