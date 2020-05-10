#include <stdio.h>

#include "tree.h"

struct thing {
    struct tree n;
    int key;
};

void printkey(struct tree *t) {
    printf("%d ", ((struct thing *) t)->key);
}

int main() {
    struct thing root;
    struct thing left;
    struct thing right;

    left.key = 1;
    root.key = 2;
    right.key = 3;

    root.n.parent = &left.n;
    root.n.left = NULL;
    root.n.right = &right.n;

    left.n.parent = NULL;
    right.n.parent = &root.n;

    left.n.left = NULL;
    left.n.right = &root.n;
    right.n.left = right.n.right = NULL;

    do_inorder(&root.n, printkey);
    puts("");
    right_rotate(&root.n);

    do_inorder(&root.n, printkey);
    puts("");
    do_preorder(root.n.parent, printkey);
    puts("");
    do_postorder(root.n.parent, printkey);
    puts("");
    return 0;
}
