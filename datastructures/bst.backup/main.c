#include <stdio.h>

#include "bst.h"

void print_tree(node * n)
{
    printf("%d ", n->data);
}

int main(void)
{
    node * root = bst_new(); 
    root->data = 5;
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;
        bst_insert(root, i);
    }

    bst_remove(root, 3);
    bst_remove(root, 1);
    bst_remove(root, 2);

    bst_preorder(print_tree, root);
    printf("\n");
    bst_inorder(print_tree, root); 
    printf("\n");
    bst_postorder(print_tree, root);
    printf("\n");

    bst_delete(root);
    return 0;
}
