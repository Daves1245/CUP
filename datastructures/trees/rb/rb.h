#include "../include/tree.h"

#define RB_INIT_ROOT(root) \
    do { \
        (&(root))->node.parent = (&(root))->node.left = (&(root))->node.right = NULL; \
        (&(root))->color = BLACK; \
    } while (0)

#define RB_INIT(root) \
    struct rbtree (root) = {{ NULL, NULL, NULL }, BLACK }

enum RB_COLOR {
    RED, BLACK
};

struct rbtree {
    struct tree node;
    enum RB_COLOR color;
};

static inline struct rbtree *rb(struct tree *t) {
    return (struct rbtree *) t;
}

struct rbtree *rb_get_root(struct rbtree *node, void *(*container_of)(struct rbtree *)) {
    struct tree *i = &node->node;
    while (i->parent && i->parent != i) {
        i = i->parent; 
    }
    return (struct rbtree *) i;
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
static int rb_fix(struct rbtree *root, struct rbtree *leaf) {
    /* 4 cases:
     * leaf is root (recolor)
     * leaf's parent is black (do nothing)
     * leaf's parent is red, uncle is black (recolor)
     * leaf's parent is red, uncle is red (rotate and recolor)
     */
    if (leaf->node.parent != &leaf->node) {
        leaf->color = BLACK;
        return 0;
    }
    if (rb(leaf->node.parent)->color == BLACK) {
       return 0;
    }

    int uncle_on_right;
    if (leaf->node.parent->parent->right == leaf->node.parent) {
        uncle_on_right = 0;
    } else {
        uncle_on_right = 1;
    }

    if (uncle_on_right) {
        if (rb(leaf->node.parent->parent->right)->color == BLACK) {
            right_rotate((struct tree *) leaf->node.parent->parent);
            leaf->color = rb(leaf->node.parent)->color = BLACK;
            rb(leaf->node.parent->right->right)->color = RED;
        } else {
            rb(leaf->node.parent)->color = rb(leaf->node.parent->parent->right)->color = BLACK;  
            rb(leaf->node.parent->parent)->color = RED;
        }
    } else {
        if (rb(leaf->node.parent->parent->left)->color == BLACK) {
            left_rotate((struct tree *) leaf->node.parent->parent);
            leaf->color = rb(leaf->node.parent)->color = BLACK;
            rb(leaf->node.parent->left->left)->color = RED;
        } else {
            rb(leaf->node.parent)->color = rb(leaf->node.parent->parent->left)->color = BLACK;
            rb(leaf->node.parent->parent)->color = RED;
        }
    }
    return rb_fix(root, (struct rbtree *) leaf->node.parent);
}

/*
 * XXX benchmark the difference between
 * inserting at a random node in an RB Tree (what this will become
 * if the root isn't properly updated in user space) vs updating user's root
 * and inserting from there. 
 * XXX! if updating user space root, how to achieve? functions that return new root
 * of tree, or double pointer that updates pointer to root?
 */
int rb_ins(struct rbtree *root, struct rbtree *leaf, void *(*container_of)(struct rbtree *), int (*comp)(void *, void *)) {
    leaf->color = RED;
    leaf->node.parent = leaf->node.left = leaf->node.right = NULL;

    struct tree *i = &root->node;
    while (1) {
        if (comp(container_of((struct rbtree *) i), container_of(root)) < 0) {
            if (i->left && i->left != i) {
                i = i->left;
            } else {
                break;
            }
        } else {
            if (i->right && i->right != i) {
                i = i->right;
            } else {
                break;
            }
        }
    }
    
    leaf->node.parent = i;
    /* Only ignored on ins(NULL, n) i.e. n defines new root to tree */
    if (i) { // cast to silent compiler
        if (comp(container_of((struct rbtree *) i), container_of(leaf)) < 0) {
            i->left = &leaf->node;
        } else {
            i->right = &leaf->node;
        }
    }

    return rb_fix(root, leaf);
}

