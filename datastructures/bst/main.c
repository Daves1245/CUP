#include <stdio.h>

#include "bst.h"

void print_tree(node * n)
{
        printf("%d ", n->data);
}

int main(void)
{
        node root = {1, NULL, NULL};
        return 0;
}
