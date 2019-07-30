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
        *
************************************************************/
// allocate for a new node
node * bst_new()
{
        node *ret = (node *) malloc(sizeof(node));
        if (!ret) {
                return NULL;
        }
        ret->left = ret->right = NULL;
        ret->data = 0;
        return ret;
}
// delete a node and all of its subtrees 
void bst_delete(node * root)
{
        if (root->left) {
                bst_delete(root->left);
        }
        if (root->right) {
                bst_delete(root->right);
        }
        free(root);
}
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
// insert a new node with given data into node
void bst_insert(node * root, int data)
{
        if (root && root->data == 0) {
                root->data = data;
        }

        if (root->data == data) {
                return;
        } 

        if (data < root->data) {
                if (root->left) {
                        bst_insert(root->left, data);
                        return;
                }

                node * left = bst_new();
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
        node * larger = bst_minimum(root->right); 
        node * smaller = bst_maximum(root->left);
        if (root->data - larger->data < root->data - smaller->data) {
                
        }
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

