#include <stdlib.h>
#include <stdio.h>

#include "rb.h"

int main(int argc, char **argv) {
    if (argc != 2) {
        fprintf(stderr, "usage: %s [number of elements]\n");
        exit(EXIT_FAILURE);
    }
    
    struct rbtree root = RB_INIT(root);

    return 0;
}
