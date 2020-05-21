#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "../include/tree.h"
#include "rb.h"
#include "rbwrapper.h"

#define MAX_ITERATIONS 100
#define MAX_TREE_SIZE 1000
#define MAX_ELEM_SIZE 10000

/* We need to give it a function that returns our container given a struct rbtree field */
void *container_of(struct rbtree *n) {
    return __container_of(n, struct myintrbtree, rbt);
}

/* And a comparator function to compare two of our containers */
int comp(void *a, void *b) {
    return ((struct myintrbtree *) a)->data - ((struct myintrbtree *) b)->data;
}

/* We can use this function on the inorder traversal to print out the tree */
void printdata(struct tree *elem) {
    struct myintrbtree *ep = (struct myintrbtree *) container_of((struct rbtree *) elem);
    printf("%d ", ep->data);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a < b ? a : b;
}

void getminmaxpath(struct tree *elem, int *shortest, int *longest, int *cur) {
    if (!elem->left && !elem->right) {
        *shortest = min(*shortest, *cur);
        *longest = max(*longest, *cur);
    }

    if (elem->left && elem->left != elem) {
        (*cur)++;
        getminmaxpath(elem->left, shortest, longest, cur);
    }

    if (elem->right && elem->right != elem) {
        (*cur)++;
        getminmaxpath(elem->right, shortest, longest, cur);
    }
    (*cur)--;
}

int consecutivereds = 0;

void checkredcoloring(struct tree *elem) {
    if (parent((struct rbtree *) elem) && parent((struct rbtree *) elem)->color == RED) {
        if (((struct rbtree *) elem)->color == RED) {
            consecutivereds = 1;
        }
    }
}

int checkblackheight(struct tree *elem, int *standard, int *cur) {
    if (parent((struct rbtree *) elem) && ((struct rbtree *) elem)->color == BLACK) {
        (*cur)++;
    }

    if (!standard && !elem->left && !elem->right) {
        *standard = *cur;
    }

    if (!elem->left && !elem->right && *cur != *standard) {
        return 1;
    }

    if (elem->left && elem->left != elem) {
        checkblackheight(elem->left, standard, cur);
    }
    if (elem->right && elem->right != elem) {
        checkblackheight(elem->right, standard, cur);
    }

    return 0;
}

void fill_with_random(struct myintrbtree **root, int tree_size, int max_elem_size) {
    for (int i = 0; i < tree_size; i++) {
        struct myintrbtree *elem = malloc(sizeof(struct myintrbtree));
        struct rbtree *rt = &(*root)->rbt;
        if (!elem) {
            fprintf(stderr, "malloc error\n");
            exit(EXIT_FAILURE);
        }

        elem->rbt.node.left = elem->rbt.node.right = NULL;
        elem->data = rand() % max_elem_size;
        rb_ins(&rt, &elem->rbt, container_of, comp);
    }
}

int rb_verify(struct tree **root, int num_elems) {
    struct tree *iterator = *root;
    int prev = ((struct myintrbtree *) root)->data;
    while ((iterator = inorder_successor(iterator))) {
        if (prev > ((struct myintrbtree *) container_of((struct rbtree *) iterator))->data) {
            return NOT_BST;
        }
        prev = ((struct myintrbtree *) container_of((struct rbtree *) iterator))->data;
    }

    int shortest = num_elems, longest = 0, cur = 0;
    getminmaxpath(*root, &shortest, &longest, &cur);
    if (shortest * 2 > longest) {
        return NOT_BALANCED;
    }

    if (do_inorder(*root, checkredcoloring)) {
        return TWO_CONSECUTIVE_RED_NODES;
    }

    int standard = 0;
    cur = 0;

    // TODO check every path on every node, this just checks every root-nil path
    if (checkblackheight(*root, &standard, &cur)) {
        return DIFFERING_BLACKHEIGHTS;
    }

    return 1; // passed all checks
}

struct tree_context {
    char *name;
    struct tree **root;
    void (*tree_ins)(struct tree **, void *elem);
    void (*tree_del)(struct tree *);
    void *(*generate_elem)(int val);
    int (*verify)(struct tree *, int);
    void (*printerrinfo)(int errno);
    // void *(*find)(void *val);
};

struct benchmark_context {
    int max_iterations;
    int max_tree_size;
    int max_elem_size;
    int max_deletions;
    int max_finds;
};

void benchmark(struct benchmark_context *bctx, struct tree_context *tctx) {
    clock_t start, end;
    double avgt = 0, totalt = 0;
    for (int i = 0; i < bctx->max_iterations; i++) {
        for (int j = 0; j < bctx->max_tree_size; j++) {
            start = clock();
            tctx->tree_ins(tctx->root, tctx->generate_elem(rand() % bctx->max_elem_size));
            end = clock();
            double t = (1000 * (double)(end - start) / CLOCKS_PER_SEC);
            avgt += t / bctx->max_iterations;
            totalt += t;
        }

        int status; 
        if ((status = tctx->verify(*tctx->root, bctx->max_tree_size)) != 0) {
            fprintf(stderr, "%s FAILED VERIFICATION: ", tctx->name);
            tctx->printerrinfo(status);
            puts("");
        }
    }

    printf("%s ins\nTotal time = %.2fms, Avg time = %.2fms\n", tctx->name, totalt, avgt);
}

void *rb_genelem(int val) {
    struct myintrbtree *ret = malloc(sizeof(struct myintrbtree));
    if (!ret) {
        return NULL;
    }
    ret->data = val;
    return ret;
}

int main(int argc, char **argv) {

    struct benchmark_context bctx = { MAX_ITERATIONS, MAX_TREE_SIZE, MAX_ELEM_SIZE };

    struct myintrbtree *rb = malloc(sizeof(struct myintrbtree));
    struct tree *rbroot;

    if (!rb) {
        fprintf(stderr, "malloc returned null\n");
        exit(EXIT_FAILURE);
    }

    rbroot = &rb->rbt.node;

    struct tree_context trees[1] = {
        "Red Black Tree",
        &rbroot,
        rb_ins,
        rb_del,
        rb_find,
        rb_genelem,
        rb_verify,
        rb_printerrinfo
    };

    if (argc > 1) {
        bctx.max_iterations = atoi(argv[1]);
    }

    if (argc > 2) {
        bctx.max_tree_size = atoi(argv[2]);
    }

    if (argc > 3) {
        bctx.max_elem_size = atoi(argv[3]);
    }

    benchmark(&bctx, &trees[0]);

    return 0;
}
