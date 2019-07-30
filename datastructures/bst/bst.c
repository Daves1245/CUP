#include <stdio.h>
#include <stdlib.h>

#include "bst.h"

/************************************************************
*
* author: David Santamaria (davidsantamaria1245@gmail.com)
* purpose: C implementation of a BST (binary search node) 
* operations (where N is the number of nodes in the node:
        * insert O(logN)
        * delete O(logN)
        * find O(logN)
*
* version: 1.0.1
* changes:
        * removed dynamic memory allocation (doesn't hold variable length data, no need for heap usage)
        * added documentation
        * added TODOs 
* status: broken (fix insert and remove functions) 
************************************************************/
node * bst_minimum(node * root)
{
        node * c = root;
        while (c && c->left) {
                c = c->left;
        }
        return c;
}
node * bst_maximum(node * root)
{
        node * c = root;
        while (c && c->right) {
                c = c->right;
        }
        return c;
}
/***************************************************
*
*               Tree modification
*
****************************************************/
// insert a new node into the tree
// XXX fix since bst_new() is deprecated
void bst_insert(node * root, node * elem)
{
        if (root && root->data == 0) {
                root->data = elem->data;
        }

        if (root->data == elem->data) { // XXX allow for redundant elements in 
                return;                 // the future. The way it works now is that
        }                               // the tree discards any node with data already
                                        // present in the tree. This keeps the property that 
        if (elem->data < root->data) {        // all children have strictly less or greater than data than
                if (root->left) {       // the root.
                        bst_insert(root->left, elem->data);
                        return;
                }

                left->data = data;
                root->left = left;
                return;
        }
        if (data > root->data) {
                if (root->right) {
                        bst_insert(root->right, data);
                        return;
                }

                node * right = bst_new();
                right->data = data;
                root->right = right;
                return;
        }
}
// get a reference to the node within node with given data
node * bst_find(node * root, int data)
{
        if (!root) {
                return NULL;
        }

        if (data == root->data) {
                return root;
        }

        // XXX since recursion doesn't necessarily help
        // here, do this iteratively. This may add a lot
        // of unnecessary function calling on the stack.
        if (data < root->data) {
                return bst_find(root->left, data);
        }

        if (data > root->data) {
                return bst_find(root->right, data);
        }
}
// remove a node with given data from a node
static node * bst_rm(node * root, node * parent, int data)
{
        // XXX - do this
}
node * bst_remove(node * root, int data)
{
        if (!root) {
                return NULL;
        }

        if (data == root->data) {
                node * rplcmnt;
                if (root->left) {
                        rplcmnt = bst_maximum(root->left);
                } else if (root->right) {
                        rplcmnt = bst_minimum(root->right);
                }

                if (rplcmnt) {
                       // XXX - finish this 
                }
        }
}

/****************************************************
*
*                    Tree traversal
*
*****************************************************/
/* Perform the function fun on all nodes in a node in specified traversal method */
void bst_preorder(void (* fun)(node *), node * n)
{
        if (n) {
                fun(n);
        }
        if (n->left) {
                bst_preorder(fun, n->left);
        }
        if (n->right) {
                bst_preorder(fun, n->right);
        }
}
void bst_inorder(void (* fun)(node * n), node * n)
{
        if (n->left) {
                bst_inorder(fun, n->left);
        }
        if (n) {
                fun(n);
        }
        if (n->right) {
                bst_inorder(fun, n->right);
        }
}
void bst_postorder(void (* fun)(node * n), node * n) { if (n->left) {
        bst_postorder(fun, n->left);
}
        if (n->right) {
                bst_postorder(fun, n->right);
        }
        if (n) {
                fun(n);
        }
}

