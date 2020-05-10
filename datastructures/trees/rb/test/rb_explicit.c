#include <stdio.h>
#include <stdlib.h>

#include "../../include/tree.h"

/* XXX move to .. and generalize */

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

static inline struct rb *getrt(struct rb *node) {
    while (node->parent != &nil) {
        node = node->parent;
    }
    return node;
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
        return 0;
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

int rb_ins(struct rb *root, struct rb *node) {
    node->color = 1; /* Set the inserted node's color to red */
    bt_ins(root, node);
    rb_fix(root, node);
}

void printdata(struct tree *n) {
    //printf("p: %p ", n);
    printf("%d ", ((struct rb *) n)->key);
}

int main(int argc, char **argv) {
    struct rb *root = malloc(sizeof(struct rb));
    root->parent = root->left = root->right = &nil;
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

    return 0;
}

/*
int main(int argc, char **argv) {
    struct rb *root, *r1, *r2;
    root = malloc(sizeof(struct rb));
    r1 = malloc(sizeof(struct rb));
    r2 = malloc(sizeof(struct rb));
    if (!root || !r1 || !r2) {
        fprintf(stderr, "a pointer returned malloc NULL\n");
        exit(EXIT_FAILURE);
    }

    root->key = 1;
    r1->key = 2;
    r2->key = 3;

    root->parent = NULL;
    root->left = NULL;
    root->right = r1;
    r1->parent = root;
    r1->left = NULL;
    r1->right = r2;
    r2->parent = r1;
    r2->left = NULL;
    r2->right = NULL;

    left_rotate((struct tree *) root);
    do_inorder(root->parent, printdata);
    return 0;
}
*/
