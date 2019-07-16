#include <stdio.h>
#include <stdlib.h>

#include "tree.h"

/*********************************************
*
*               Memory Allocation
*
**********************************************/
// allocate for a new tree
tree * tree_new()
{
        tree *ret = (tree *) malloc(sizeof(tree));
        if (!ret) {
                return NULL;
        }
        ret->left = ret->right = NULL;
        ret->data = 0;
        return ret;
}
// delete a tree and all subtrees
void tree_delete(tree * root)
{
        if (root->left) {
                tree_delete(root->left);
        }
        if (root->right) {
                tree_delete(root->right);
        }
        free(root);
}
tree * tree_minimum(tree * root)
{
        tree * c = root;
        while (c && c->left) {
                c = c->left;
        }
        return c;
}
tree * tree_maximum(tree * root)
{
        tree * c = root;
        while (c && c->right) {
                c = c->right;
        }
        return c;
}
/***************************************************
*
*               Tree modification
*
***************************************************/
// insert a new tree with given data into tree
void tree_insert(tree * root, int data)
{
        if (root && root->data == 0) {
                root->data = data;
        }

        if (root->data == data) {
                return;
        } 

        if (data < root->data) {
                if (root->left) {
                        tree_insert(root->left, data);
                        return;
                }

                tree * left = tree_new();
                left->data = data;
                root->left = left;
                return;
        }
        if (data > root->data) {
                if (root->right) {
                        tree_insert(root->right, data);
                        return;
                }

                tree * right = tree_new();
                right->data = data;
                root->right = right;
                return;
        }
}
// get a reference to the tree within tree with given data
tree * tree_find(tree * root, int data)
{
        if (!root) {
                return NULL;
        }

        if (data == root->data) {
                return root;
        }

        if (data < root->data) {
                return tree_find(root->left, data);
        }

        if (data > root->data) {
                return tree_find(root->right, data);
        }
}
// remove a tree with given data from a tree
static tree * tree_rm(tree * root, tree * parent, int data)
{
        
}
tree * tree_remove(tree * root, int data)
{
        if (!root) {
                return NULL;
        }

        if (data == root->data) {
                tree * rplcmnt;
                if (root->left) {
                        rplcmnt = tree_maximum(root->left);
                } else if (root->right) {
                        rplcmnt = tree_minimum(root->right);
                }

                if (rplcmnt) {
                        
                }
        }
}

/****************************************************
*
*                    Tree traversal
*
*****************************************************/
/* Perform the function fun on all nodes in a tree in specified traversal method */
void tree_preorder(void (* fun)(tree *), tree * n)
{
        if (n) {
                fun(n);
        }
        if (n->left) {
                tree_preorder(fun, n->left);
        }
        if (n->right) {
                tree_preorder(fun, n->right);
        }
}
void tree_inorder(void (* fun)(tree * n), tree * n)
{
        if (n->left) {
                tree_inorder(fun, n->left);
        }
        if (n) {
                fun(n);
        }
        if (n->right) {
                tree_inorder(fun, n->right);
        }
}
void tree_postorder(void (* fun)(tree * n), tree * n) { if (n->left) {
                tree_postorder(fun, n->left);
        }
        if (n->right) {
                tree_postorder(fun, n->right);
        }
        if (n) {
                fun(n);
        }
}

