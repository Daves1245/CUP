#ifndef CUP_ROTATE_H
#define CUP_ROTATE_H

/*      n                   m
 *     / \                 / \
 *    a   m       =>      n   c
 *       / \             / \
 *      b   c           a   b 
 */
void left_rotate(struct tree *n) {
    struct tree *m = n->right;
    n->right = m->left;
    m->parent = n->parent;
    if (n->parent) {
        m->parent = n->parent;
        if (n == n->parent->left) {
            n->parent->left = m;
        } else if (n == n->parent->right) {
            n->parent->right = m;
        }
    }
    m->left = n;
    n->parent = m;
}

/*      n                   m
 *     / \                 / \
 *    m   c       <=      a   n
 *   / \                     / \
 *  a   b                   b   c
 */
void right_rotate(struct tree *n) {
    struct tree *m = n->left;
    n->left = m->right;
    if (n->parent) {
        m->parent = n->parent;
        if (n == n->parent->left) {
            n->parent->left = m;
        } else if (n == n->parent->right) {
            n->parent->right = m;
        }
    }
    m->right = n;
    n->parent = m;
}

#endif
