#ifndef CUP_TRAVERSALS_H
#define CUP_TRAVERSALS_H

/*
 * Make these macros as well, that expand out
 * like for each declarations (perhaps using
 * some to-be-implemented pre/in/post-order successor
 * functions :)
 */

int do_preorder(struct tree *root, void (*func)(void *)) {
    func(root);
    if (root->left != root) {
        do_preorder(root->left, func);
    }
    if (root->right != root) {
        do_preorder(root->right, fun);
    }
}

int do_inorder(struct tree *root, void (*func)(void *)) {
    if (root->left != root) {
        do_inorder(root->left, func);
    }
    func(root);
    if (root->right != root) {
        do_inorder(root->right, func);
    }
}

int do_postorder(struct tree *root, void (*func)(void *)) {
    if (root->left != root) {
        do_postorder(root->left, func);
    }
    if (root->right != root) {
        do_postorder(root->right, func);
    }
    func(root);
}

#endif
