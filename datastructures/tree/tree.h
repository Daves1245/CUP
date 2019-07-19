
typedef struct tree {
    struct tree * left;
    struct tree * right;
    int data;
} tree;

tree * tree_new();
void tree_delete(tree * root);

void tree_insert(tree * root, int data);
tree * tree_remove(tree * root, int data);

void tree_preorder(void (* fun)(tree * n), tree * n);
void tree_inorder(void (* fun)(tree * n), tree * n);
void tree_postorder(void (* fun)(tree * n), tree * n);
