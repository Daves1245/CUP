#include "../include/tree.h"

#define RB_INIT(root) { {&(root), &(root), &(root)}, BLACK }

static inline struct rbtree *rb(struct tree *t) {
    return (struct rbtree *) t;
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
    struct rbtree *pivot;
    while (rb(leaf->node.parent)->color == RED) {
        if (leaf->node.parent == leaf->node.parent->parent->left) {
           pivot = rb(leaf->node.parent->parent->right); 
           if (pivot->color == RED) {
               rb(leaf->node.parent)->color = BLACK; 
               leaf->color = BLACK;
               rb(leaf->node.parent->parent)->color = RED;
           } else if (leaf == rb(leaf->node.parent->right)) {
               leaf = rb(leaf->node.parent);
               left_rotate((struct tree *) root, (struct tree *) leaf);
               rb(leaf->node.parent)->color = BLACK;
               rb(leaf->node.parent->parent)->color = RED;
               right_rotate((struct tree *) root, (struct tree *) leaf);
           }
        } else {
            leaf = rb(leaf->node.parent);
            /* XXX */
        }
    }
    root->color = BLACK;
}

int rb_ins(struct rbtree *root, struct rbtree *leaf, void *(*container_of)(struct rbtree *), int (*comp)(void *, void *)) {
    struct rbtree *cur, *child;
    while (1) {
        if (comp(container_of(leaf), container_of(child)) <= 0) {
            if (child->.node->left) {
                cur = child;
                child = child->left;
            } else {
                break;
            }
        } else {
            if (child->right) {
                cur = child;
                child = child->right;
            } else {
                break;
            }
        }
    }

    leaf->parent = cur;
    /* We don't accept subtrees atm XXX */
    leaf->node.right = leaf->node.left = leaf;
    if (comp(container_of(leaf), container_of(cur)) <= 0) {
        cur->left = child;
    } else {
        cur->right = child;
    }
    leaf->color = RB_RED;
    rb_fix(root, leaf);
}

