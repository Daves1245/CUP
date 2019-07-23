#include <stdio.h>
#include <stdlib.h>
#include <string.h>

static inline int parent(int i)
{
    return i / 2;
}

static inline int lchild(int i)
{
    return 2 * i + 1;
}

static inline int rchild(int i)
{
    return 2 * i + 2;
}

// this should be check if i is within [(n + 1) / 2, n) 
// but due to indexing being 0 based, it is [n / 2, n - 1)
static inline int isleaf(int i, int n)
{
    return (i >= n / 2) && (i < n); 
}

static int build(int arr[], int n, int i)
{
    if (!isleaf(i, n)) {
        arr[i] = build(arr, n, lchild(i)) + build(arr, n, rchild(i));
    }
    return arr[i];
}

int *segtree_make(int arr[], int n)
{
    int *ret = malloc(sizeof(*ret) * (2 * n));
    for (int i = 0; i < n; i++) {
        ret[i + n - 1] = arr[i];
    }
    ret[0] = build(ret, 2 * n - 1, 0);
    return ret;
}

void segtree_update(int arr[], int i, int key)
{
    int diff = key - arr[i];
    while (i > 0) {
        arr[i] += diff;
        i = parent(i);
    }
    arr[0] += diff;
}

int segtree_query(int arr[], int i, int l, int r)
{
    if (i < l || i > r) {
        return 0;
    }
    if (i >= l && i < r) {
        return arr[parent(i)];
    }
}

#define LIMIT 5

void print(int arr[], int n)
{
    for (int i = 0; i < n; i++) {
        printf("%d ", arr[i]);
    }
    printf("\n");
}

