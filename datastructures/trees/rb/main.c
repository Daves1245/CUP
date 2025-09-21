#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <time.h>

#include "../include/tree.h"
#include "../include/bench_common.h"
#include "rb.h"
#include "rbwrapper.h"

#define MAX_ITERATIONS 50
#define MAX_TREE_SIZE 50
#define MAX_ELEM_SIZE 10000

// XXX IMPORTANT: remove container_of from rb.h - not necessary
// TODO: should user handle insert/delete from API perspective with rb_fix?

struct results {
    int errno;
    int index_failed;
    struct tree *node_failed;
};

struct tree_context {
    char *name;
    struct tree **root;
    int num_elems;
    void (*tree_ins)(struct tree **, void *elem);
    void (*tree_del)(struct tree *);
    void *(*generate_elem)(int val);
    void (*verify)(struct tree_context *, struct results *);
    void (*printerrinfo)(int errno);
    // void *(*find)(void *val);
};

struct benchmark_context {
    int max_iterations;
    int max_tree_size;
    int max_elem_size;
    int max_deletions;
    int max_finds;
};

/* We need to give it a function that returns our container given a struct rbtree field */
void *container_of(struct rbtree *n) {
    return __container_of(n, struct myintrbtree, rbt);
}

/* And a comparator function to compare two of our containers */
int comp(void *a, void *b) {
    return ((struct myintrbtree *) a)->data - ((struct myintrbtree *) b)->data;
}

/* We can use this function on the inorder traversal to print out the tree */
void printdata(struct tree *elem) {
    struct myintrbtree *ep = (struct myintrbtree *) container_of((struct rbtree *) elem);
    printf("%d ", ep->data);
}

int min(int a, int b) {
    return a < b ? a : b;
}

int max(int a, int b) {
    return a > b ? a : b;
}

void getminmaxpath(struct tree *elem, int *shortest, int *longest, int *cur) {
    if (!elem->left && !elem->right) {
        *shortest = min(*shortest, *cur);
        *longest = max(*longest, *cur);
    }

    if (elem->left && elem->left != elem) {
        (*cur)++;
        getminmaxpath(elem->left, shortest, longest, cur);
    }

    if (elem->right && elem->right != elem) {
        (*cur)++;
        getminmaxpath(elem->right, shortest, longest, cur);
    }
    (*cur)--;
}

int consecutivereds = 0;

void checkredcoloring(struct tree *elem) {
    if (parent((struct rbtree *) elem) && parent((struct rbtree *) elem)->color == RED) {
        if (((struct rbtree *) elem)->color == RED) {
            consecutivereds = 1;
        }
    }
}

int checkblackheight(struct tree *elem, int *standard, int *cur) {
    if (parent((struct rbtree *) elem) && ((struct rbtree *) elem)->color == BLACK) {
        (*cur)++;
    }
    if (!standard && !elem->left && !elem->right) {
        *standard = *cur;
    }
    if (!elem->left && !elem->right && *cur != *standard) {
        return 1;
    }
    if (elem->left && elem->left != elem) {
        checkblackheight(elem->left, standard, cur);
    }
    if (elem->right && elem->right != elem) {
        checkblackheight(elem->right, standard, cur);
    }

    return 0;
}

void fill_with_random(struct myintrbtree **root, int tree_size, int max_elem_size) {
    for (int i = 0; i < tree_size; i++) {
        struct myintrbtree *elem = malloc(sizeof(struct myintrbtree));
        struct rbtree *rt = &(*root)->rbt;
        if (!elem) {
            fprintf(stderr, "malloc error\n");
            exit(EXIT_FAILURE);
        }

        elem->rbt.node.left = elem->rbt.node.right = NULL;
        elem->data = rand() % max_elem_size;
        rb_ins(&rt, &elem->rbt, container_of, comp);
    }
}

void rb_verify(struct tree_context *tctx, struct results *res) {
    res->errno = 0;
    res->index_failed = -1;
    res->node_failed = NULL;

    /* Check if tree is empty */
    if (!*tctx->root) {
        return; /* Empty tree is valid */
    }

    /* Check if root is black */
    if (((struct rbtree *) *tctx->root)->color != BLACK) {
        res->errno = ROOT_NOT_BLACK;
        res->node_failed = *tctx->root;
        return;
    }

    struct tree *iterator = *tctx->root;
    int prev = ((struct myintrbtree *) container_of((struct rbtree *) *tctx->root))->data;
    for (int i = 0; (iterator = inorder_successor(iterator)); i++) {
        if (prev > ((struct myintrbtree *) container_of((struct rbtree *) iterator))->data) {
            res->errno = NOT_BST;
            res->index_failed = i;
            res->node_failed = iterator;
            return;
        }
        prev = ((struct myintrbtree *) container_of((struct rbtree *) iterator))->data;
    }

    int shortest = tctx->num_elems, longest = 1, cur = 1;
    getminmaxpath(*tctx->root, &shortest, &longest, &cur);
    if (shortest * 2 < longest) {
        res->errno = NOT_BALANCED;
        res->node_failed = *tctx->root;
        return;
    }


    consecutivereds = 0;
    do_inorder(*tctx->root, checkredcoloring);
    if (consecutivereds) {
        res->errno = TWO_CONSECUTIVE_RED_NODES;
        res->node_failed = *tctx->root;
        return;
    }

    int standard = 1;
    cur = 1;

    // TODO check every path on every node, this just checks every root-nil path
    if (checkblackheight(*tctx->root, &standard, &cur)) {
        res->errno = DIFFERING_BLACKHEIGHTS;
        res->node_failed = *tctx->root;
        return;
    }
}

void rmnode(struct tree *n) {
    struct myintrbtree *i = (struct myintrbtree *) n;
    free(i);
}

// XXX remove all elements from tree and start over fresh
void benchmark(struct benchmark_context *bctx, struct tree_context *tctx) {
    struct performance_stats insert_stats;
    bench_init_stats(&insert_stats, "Insert");

    bench_print_section("Insert check");

    for (int i = 0; i < bctx->max_iterations; i++) {
        for (int j = 0; j < bctx->max_tree_size; j++) {
            BENCH_START_TIMER(insert_timer);
            void *p = tctx->generate_elem(rand() % bctx->max_elem_size);
            tctx->tree_ins(tctx->root, p);
            BENCH_END_TIMER(insert_timer, &insert_stats);
        }

        struct results res;
        tctx->verify(tctx, &res);

        if (res.errno) {
            bench_print_test_case(i + 1, bctx->max_iterations, "Insert", TEST_FAILED);
            if (!bench_compact_mode) {
                printf("\n%s VERIFICATION FAILED: ", tctx->name);
                tctx->printerrinfo(res.errno);
                if (res.node_failed) {
                    printf("near: %d\n", ((struct myintrbtree *) res.node_failed)->data);
                }
                do_inorder(*tctx->root, printdata);
                puts("");
            }
            exit(EXIT_FAILURE);
        } else {
            bench_print_test_case(i + 1, bctx->max_iterations, "Insert", TEST_PASSED);
        }

        if (*tctx->root) {
            do_inorder(*tctx->root, rmnode);
            *tctx->root = NULL;
        }
    }
    
    bench_finalize_stats(&insert_stats);
    bench_print_stats(&insert_stats);
    
    bench_print_summary_header();
    bench_print_summary_line(&insert_stats);
}

void *rb_genelem(int val) {
    struct myintrbtree *ret = malloc(sizeof(struct myintrbtree));
    memset(ret, 0, sizeof(*ret));
    if (!ret) {
        fprintf(stderr, "malloc error!\n");
        return NULL;
    }
    ret->data = val;
    return ret;
}

int getdata(struct tree *t) {
    return ((struct myintrbtree *) t)->data;
}

/*void interactive(void) {
  char buff[100];
  int state = 0, first = 1;
  struct myintrbtree *root = malloc(sizeof(struct myintrbtree));
  struct rbtree *rbroot = &root->rbt;
  do {
  scanf("%s", buff);
  switch (*buff) {
  case 'i':
  state = 1;
  break;
  case 'p':
  state = 0;
  printf("> ");
  do_inorder(rbroot, printdata);
  puts("");
  break;
  default:
  if (!state) {
  printf("assuming insert\n");
  state = 1;
  } 
  if (first) {
  first = 0;
  root->data = atoi(buff);
  break;
  }
  struct myintrbtree *tmp = malloc(sizeof(struct myintrbtree));
  if (!tmp) {
  fprintf(stderr, "malloc returned null. exiting\n");
  exit(EXIT_FAILURE);
  }
  tmp->data = atoi(buff);
  rb_ins_wrapper(rbroot, (struct rbtree *) tmp);
  }
  } while (strcmp(buff, "exit") != 0);

  }*/

int main(int argc, char **argv) {
    srand(time(NULL));

    /* Initialize benchmark configuration */
    struct benchmark_config config;
    bench_init_config(&config, MAX_ITERATIONS, MAX_TREE_SIZE, MAX_ELEM_SIZE);
    bench_parse_args(&config, argc, argv);
    bench_init_terminal(&config);

    struct benchmark_context bctx = { config.max_iterations, config.max_size, config.max_element_value };

    /* Initialize root as NULL for empty tree */
    struct tree *rbroot = NULL;

    struct tree_context trees[1] = {{
        "Red Black Tree",
            &rbroot,
            config.max_size,
            rb_ins_wrapper,
            rb_del_wrapper,
            rb_genelem,
            rb_verify,
            rb_printerrinfo
    }};

    bench_print_header("RED-BLACK TREE", &config);
    benchmark(&bctx, &trees[0]);

    return 0;
}
