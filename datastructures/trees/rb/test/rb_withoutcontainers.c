#include <stdio.h>
#include <stdlib.h>

#include "../../include/tree.h"

/*
 * Let:
 *  1 = RED,
 *  0 = BLACK
 */
struct rb {
    struct rb *parent, *left, *right; 
    int key;
    int color;
};

struct rb nil = {&nil, &nil, &nil, -1, 0};

/* Insert a node into root as a binary tree */
int bt_ins(struct rb *root, struct rb *node) {
    node->parent = node->left = node->right = &nil;
    struct rb *cur = &nil, *child = root;
    while (child && child != &nil) {
        cur = child;
#ifdef DEBUG
        printf("1\n");
#endif
        if (node->key <= child->key) {
#ifdef DEBUG
            printf("2\n");
#endif
            child = child->left;
#ifdef DEBUG
            printf("-2\n");
#endif
        } else {
#ifdef DEBUG
            printf("3\n");
#endif
            child = child->right;
#ifdef DEBUG
            printf("-3\n");
#endif
        }
    }
#ifdef DEBUG
    printf("4\n");
#endif
    node->parent = cur;
#ifdef DEBUG
    printf("-4\n");
#endif
    if (node->key < cur->key) {
#ifdef DEBUG
        printf("5\n");
#endif
        cur->left = node;
    } else {
#ifdef DEBUG
        printf("6\n");
#endif
        cur->right = node;
    }
}

/* Case 1 - the inserted node is the root */
/* Fix - recolor to black */
static inline int rb_fix_case1(struct rb *root, struct rb *node) {
    node->color = 0; /* Set color to black */
    return 0;
}

/* inserted node's parent is black */
static inline int rb_fix_case2(struct rb *root, struct rb *node) {
    /* Do nothing, this doesn't invalidate the tree */
    return 0;
}

/* Get a node's uncle */
static inline struct rb *uncle(struct rb *n) {
    if (n->parent->parent->left == n->parent) {
        return n->parent->parent->right;
    } else {
        return n->parent->parent->left;
    }
} 

static inline struct rb *grandparent(struct rb *n) {
    return n->parent->parent;
}

/* Inserted node's parent is red and uncle is red */
static inline int rb_fix_case3(struct rb *root, struct rb *node) {
    /* Here, in order to fix property 4, we just have to recolor n's
     * parent, grandfather, and uncle. Notice how this recoloring does not
     * break property 5
     */
    /* Figure out if uncle is grandparent's right or left child */
    node->parent->color = 0; /* Set to black */
    if (node->parent->parent->left == node->parent) {
        node->parent->parent->right->color = 0;
    } else {
        node->parent->parent->left->color = 0;
    }
    node->parent->parent->color = 1; /* Set to red */
}

/* Inserted node's parent is red and uncle is black */
static inline int rb_fix_case4(struct rb *root, struct rb *node) {
    if (uncle(node) == node->parent->parent->right) {
        right_rotate((struct tree *) node->parent->parent);
        node->color = node->parent->color = 0; /* Set to black */
        node->parent->right->color = 1; /* Set to red */
    } else if (uncle(node) == node->parent->parent->left) {
        left_rotate((struct tree *) node->parent->parent);
        node->color = node->parent->color = 0; /* Set to black */
        node->parent->left->color = 1; /* Set to red */
    }
}

static int rb_fix(struct rb *root, struct rb *node) {
    /* There are four cases */
    if (node->parent == &nil) {
        rb_fix_case1(root, node);
    } else if (node->parent->color == 0) {
        rb_fix_case2(root, node);
    } else {
        /* Uncle is grandparent's right child */
        if (uncle(node) == grandparent(node)->right) {
            /* Uncle is same as parent: red */
            if (node->parent->color == 1 && uncle(node)->color == 1) {
                rb_fix_case3(root, node);
            }
            /* Uncle is black */
            if (node->parent->color == 1 && uncle(node)->color == 0) {
                rb_fix_case4(root, node);
            }
        /* Uncle is grandparent's left child */
        } else if (uncle(node) == grandparent(node)->left) {
            /* The same as above, just with uncle on the left */
            if (node->parent->color == 1 && uncle(node)->color == 1) {
                rb_fix_case3(root, node);
            }
            if (node->parent->color == 1 && uncle(node)->color == 0) {
                rb_fix_case4(root, node);
            }
        }
    }
    rb_fix(root, node->parent);
}

int do_inorder(struct rb *root, void (*func)(struct rb *)) {
#ifdef DEBUG
    printf("a\n");
#endif
    if (root->left != &nil) {
#ifdef DEBUG
        printf("b\n");
#endif
        do_inorder(root->left, func);
    }
#ifdef DEBUG
    printf("-b\n");
#endif
    func(root);
#ifdef DEBUG
    printf("c\n");
#endif
    if (root->right != &nil) {
#ifdef DEBUG
        printf("d\n");
#endif
        do_inorder(root->right, func);
    }
#ifdef DEBUG
    printf("e\n");
#endif
}

int rb_ins(struct rb *root, struct rb *node) {
    bt_ins(root, node);
    rb_fix(root, node);
}

void printdata(struct rb *n) {
    printf("p: %p ", n);
    printf("%d ", n->key);
}

int main(int argc, char **argv) {
    struct rb *root = malloc(sizeof(struct rb));
    if (!root) {
        fprintf(stderr, "malloc error!\n");
        exit(EXIT_FAILURE);
    }

    if (argc != 2) {
        fprintf(stderr, "usage: %s [num elements]\n", argv[0]);
        exit(EXIT_FAILURE);
    }

    scanf("%d", &root->key);
    for (int i = 1; i < atoi(argv[1]); i++) {
        struct rb *tmp = malloc(sizeof(struct rb));
        if (!tmp) {
            fprintf(stderr, "malloc error!\n");
            exit(EXIT_FAILURE);
        }
        scanf("%d", &tmp->key);
        rb_ins(root, tmp);
    }

    do_inorder(root, printdata);
    puts("");
    /*printf("%d ", root->left->left->key);
    printf("%d ", root->left->key);
    printf("%d ", root->key);
    printf("%d ", root->right->left->key);
    printf("%d ", root->right->key); */
    puts("");

    return 0;
}
