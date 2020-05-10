#include <string.h>
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include "../../include/tree.h"

struct container {
    struct tree rbt;
    int key;
};

void printkey(struct tree *e) {
    printf("%d ", ((struct container *) e)->key);
}

void setkey(struct tree *e) {
    printf(">");
    scanf("%d", &((struct container *) e)->key);
}

void *container_of(struct tree *rbt) {
    return (struct contianer *) rbt;
}

int comp(void *a, void *b) {
    return ((struct container *) a)->key - ((struct container *) b)->key;
}

/*
void ins(struct container *root, struct container *leaf, int (*comp)(void *, void *), void *container_of(void *)) {
    struct tree *i = &root->rbt;
    while (i) {
        if (comp(leaf, container_of(i)) < 0) {
            if (i->left) {
                i = i->left;
            } else {
                break;
            }
        } else {
            if (i->right) {
                i = i->right;
            } else {
                break;
            }
        }
    }
    
    leaf->rbt.parent = i;
    if (i) {
        if (comp(leaf, container_of(i)) < 0) {
            i->left = leaf;
        } else {
            i->right = leaf;
        }
    }
}
*/

void ins(struct container *root, struct container *leaf, int (*comp)(void *, void *)) {
    struct tree *i = &root->rbt;
    while (i) {
        if (comp(leaf, i) < 0) {
            if (i->left) {
                i = i->left;
            } else {
                break;
            }
        } else if (i->right) {
            i = i->right;
        } else {
            break;
        }
    }

    leaf->rbt.parent = i;
    if (i) {
        if (comp(leaf, i) < 0) {
            i->left = (struct tree *) leaf;
        } else {
            i->right = (struct tree *) leaf;
        }
    }
}

int main(void) {
    struct container root;
    struct container *rt = &root;
    root.rbt.parent = root.rbt.left = root.rbt.right = NULL;
    scanf("%d", &root.key);
    char buff[10];
    while (1) {
        scanf("%s", buff);
        if (isdigit(*buff)) {
            struct container *tmp = malloc(sizeof(struct container));
            if (!tmp) {
                fprintf(stderr, "malloc returned null pointer\nExiting...");
                exit(EXIT_FAILURE);
            }
            tmp->rbt.parent = tmp->rbt.left = tmp->rbt.right = NULL;
            tmp->key = atoi(buff);
            ins(rt, tmp, comp);
            printf("Traversal: ");
            do_inorder(&rt->rbt, printkey);
            puts("");
        } else {
            if (strcmp(buff, "left") == 0) {
                printf("left rotating\n");
                int status;
                status = left_rotate(&rt->rbt);
                if (status != 0) {
                    printf("illegal rotation on root\n");
                    printf("exiting\n");
                    return -1;
                } else {
                    rt = (struct container *) rt->rbt.parent;
                    printf("done\n");
                }
            } else if (strcmp(buff, "right") == 0) {
                printf("right rotating\n");
                int status = right_rotate(&rt->rbt);
                if (status != 0) {
                    printf("illegal rotation on root\n");
                    printf("exiting\n");
                    return -1;
                } else {
                    rt = (struct container *) rt->rbt.parent;
                    printf("done\n");
                }
            } else if (strcmp(buff, "exit") == 0) {
                printf("exiting\n");
                exit(EXIT_SUCCESS);
            } else if (strcmp(buff, "root") == 0) {
                printf("value of root: %d\n", rt->key);
            } else if (strcmp(buff, "print") == 0) {
                printf("Traversal: ");
                do_inorder(&rt->rbt, printkey);
                puts("");
            } else if (strcmp(buff, "set") == 0) {
                printf("setting values for all nodes\n");
                do_inorder(&root.rbt, setkey);
                printf("done\n");
            } else {
                printf("input not valid. Ignoring\n");
            }
        }   
    }
    return 0;
}
