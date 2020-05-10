#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

#include "../include/tree.h"
#include "rb.h"

struct myintrbtree {
    struct rbtree rbt;
    int data;
};

void *container_of(struct rbtree *n) {
    return __container_of(n, struct myintrbtree, rbt);
}

int comp(void *a, void *b) {
    return ((struct myintrbtree *) a)->data - ((struct myintrbtree *) b)->data;
}

void printdata(struct tree * elem) {
    printf("%d ", ((struct myintrbtree *) container_of((struct rbtree *)elem))->data);
}

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s [number of elements]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
    
    struct myintrbtree *root = malloc(sizeof(struct myintrbtree));
    RB_INIT_ROOT(root->rbt);

    if (!root) {
        fprintf(stderr, "malloc error\n");
        exit(EXIT_FAILURE);
    }

    scanf("%d ", &root->data);
    for (int i = 1; i < atoi(argv[1]); i++) {
        struct myintrbtree *tmp = malloc(sizeof(struct myintrbtree));
        if (!tmp) {
            fprintf(stderr, "malloc error\n");
            exit(EXIT_FAILURE);
        }
        scanf("%d", &tmp->data);
        /*
         * You can either have struct rbtree be the first member of 
         * your desired struct and directly insert it with a cast,
         * or just give it a pointer to the struct rbtree member
         * within your struct of choice */
        rb_ins((struct rbtree *) root, (struct rbtree *) tmp, container_of, comp);
        printf("Inorder Traversal: ");
        do_inorder((struct tree *) rb_get_root(&root->rbt, container_of), printdata);
        puts("");
    }

    /* By the current implementation, the root node may have been
     * moved around the tree and is no longer the root. For now,
     * there is simply a get_root function that returns the root
     * of the tree of a given node. Currently working on updating
     * root as it is moved around. */
    return 0;
}
