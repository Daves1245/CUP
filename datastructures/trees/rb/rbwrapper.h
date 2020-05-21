#define NOT_BST 1
#define ROOT_NOT_BLACK 2
#define NOT_BALANCED 3
#define TWO_CONSECUTIVE_RED_NODES 4
#define DIFFERING_BLACKHEIGHTS 5

/* We can construct a container for any object to be a part of an RB tree */
struct myintrbtree {
    struct rbtree rbt;
    int data;
};

void *rb_container_of(struct rbtree *node) {
    return __container_of(node, struct myintrbtree, rbt);
}

int rb_comp(void *a, void *b) {
    return ((struct myintrbtree *) a)->data - ((struct myintrbtree *) b)->data;
}

void rb_printdata(struct tree *elem) {
    struct myintrbtree *ep = (struct myintrbtree *) rb_container_of((struct rbtree *) elem);
    printf("%d ", ep->data);
}

void tree_ins(struct tree **root, void *elem) {
    rb_ins(root, elem, rb_comp, rb_container_of);
}

void rb_printerrinfo(int status) {
    switch (status) {
        case NOT_BST:
            printf("Not a BST tree\n");
            break;
        case ROOT_NOT_BLACK:
            printf("The root node is not black\n");
            break;
        case NOT_BALANCED:
            printf("Tree is not balanced (longest root-nil path > 2 * shortest)\n");
            break;
        case TWO_CONSECUTIVE_RED_NODES:
            printf("A red node is the child of another red node\n");
            break;
        case DIFFERING_BLACKHEIGHTS:
            printf("Two paths were found from the same node with differing black heights\n");
            break;
    }
}
