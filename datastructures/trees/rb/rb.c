#include <stdio.h>

#include "tree.h"

#define RB_INIT_ROOT(root) \
    do { \
        (&(root))->node.parent = (&(root))->node.left = (&(root))->node.right = NULL; \
        (&(root))->color = BLACK; \
    } while (0)

#define RB_INIT_NODE(root) \
    struct rbtree (root) = {{ NULL, NULL, NULL }, RED }

enum RB_COLOR {
    RED, BLACK
};

struct rbtree {
    struct tree node;
    enum RB_COLOR color;
};

struct rbtree *rb(struct tree *t) {
    return (struct rbtree *) t;
}

struct rbtree *rb_get_root(struct rbtree *node) {
    struct tree *i = &node->node;
    while (i->parent && i->parent != i) {
        i = i->parent;
    }
    return (struct rbtree *) i;
}

struct rbtree *parent(struct rbtree *e) {
    if (!e) {
        return NULL;
    }
    return (struct rbtree *) e->node.parent;
}

struct rbtree *uncle(struct rbtree *e) {
    if (!e || !parent(e) || !parent(parent(e))) {
        return NULL;
    }
    if (parent(e) == (struct rbtree *) parent(parent(e))->node.left) {
        return (struct rbtree *) e->node.parent->parent->right;
    }
    return (struct rbtree *) e->node.parent->parent->left;
}

/*
 * use some magic C polymorphism-like utility from the fact that
 * the base of rbtree is tree by definition:
 * struct rbtree {
 *      struct tree node;
 *      RB_COLOR color;
 * };
 * to get rid of all the ugly rb(stuff)->color
 * and bring together all the code into one, beautiful, elegant program
 */
// TODO rename leaf-not appropriate after successive iterations of while loop

static int rb_fix(struct rbtree **root, struct rbtree *leaf) {
    while (leaf && leaf != *root && parent(leaf) && parent(leaf)->color == RED) {
        struct rbtree *y;
        if (parent(leaf) == (struct rbtree *) parent(parent(leaf))->node.left) {
            y = (struct rbtree *) parent(parent(leaf))->node.right;
            if (y && y->color == RED) {
                parent(leaf)->color = y->color = BLACK;
                parent(parent(leaf))->color = RED;
                leaf = parent(parent(leaf));
            } else {
                if (leaf == (struct rbtree *) parent(leaf)->node.right) {
                    leaf = parent(leaf);
                    left_rotate((struct tree *) leaf);
                }
                parent(leaf)->color = BLACK;
                parent(parent(leaf))->color = RED;
                right_rotate(leaf->node.parent->parent);
            }
        } else {
            y = (struct rbtree *) parent(parent(leaf))->node.left;
            if (y && y->color == RED) {
                parent(leaf)->color = y->color = BLACK;
                parent(parent(leaf))->color = RED;
                leaf = parent(parent(leaf));
            } else {
                if (leaf == (struct rbtree *) parent(leaf)->node.left) {
                    leaf = parent(leaf);
                    right_rotate((struct tree *) leaf);
                }
                parent(leaf)->color = BLACK;
                parent(parent(leaf))->color = RED;
                left_rotate(leaf->node.parent->parent);
            }
        }
    }

    /* Find and set the actual root */
    if (leaf) {
        while (leaf->node.parent) {
            leaf = parent(leaf);
        }
        *root = leaf;
    }

    if (*root) {
        (*root)->color = BLACK;
    }
    return 0;
}

int rb_ins(struct rbtree **root, struct rbtree *leaf, void *(*container_of)(struct rbtree *), int (*comp)(void *, void *)) {
    /* Initialize the new node */
    leaf->node.left = leaf->node.right = NULL;

    /* Handle empty tree case */
    if (*root == NULL) {
        leaf->color = BLACK;
        leaf->node.parent = NULL;
        *root = leaf;
        return 0;
    }

    (*root)->color = BLACK;
    leaf->color = RED;

    struct tree *i = &(*root)->node;
    while (i) {
        if (comp(container_of(leaf), container_of((struct rbtree *) i)) < 0) {
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

    leaf->node.parent = i;
    /* Only ignored on ins(NULL, n) i.e. n defines new root to tree */
    if (i) { // cast to silent compiler
        if (comp(container_of(leaf), container_of((struct rbtree *) i)) < 0) {
            i->left = &leaf->node;
        } else {
            i->right = &leaf->node;
        }
    }

    return rb_fix(root, leaf);
}

int rb_del(struct rbtree *node) {
    return 0; // XXX
}

void *rb_find(struct rbtree *root, void *val, int (*comp)(void *, void *), void *container_of(struct rbtree *)) {
    return NULL; // XXX
}

