#include <stdio.h>

#include "tree.h"

void print_tree(tree * n)
{
    printf("%d ", n->data);
}

int main(void)
{
    tree * root = tree_new(); 
    root->data = 5;
    for (int i = 0; i < 10; i++) {
        if (i == 5) continue;
        tree_insert(root, i);
    }

    tree_remove(root, 3);
    tree_remove(root, 1);
    tree_remove(root, 2);

    tree_preorder(print_tree, root);
    printf("\n");
    tree_inorder(print_tree, root); 
    printf("\n");
    tree_postorder(print_tree, root);
    printf("\n");

    tree_delete(root);
    return 0;
}
