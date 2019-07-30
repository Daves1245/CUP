
typedef struct node {
        int data;
        struct node *left;
        struct node *right;
} node;

/* Tree manipulations */
void bst_insert(node * root, node * elem);
node * bst_remove(node * root, int data);

/* Tree traversal */
void bst_preorder(void (* fun)(node * n), node * n);  // These functions perform
void bst_inorder(void (* fun)(node * n), node * n);   // the function given to them
void bst_postorder(void (* fun)(node * n), node * n); // on each node in the tree in the
                                                      // appropriate order
