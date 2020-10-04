#include "ufds.h"

struct ufds *UnionFind(int size) {
    struct ufds *ret = malloc(sizeof(struct ufds));
    if (!ret) {
        fprintf(stderr, "[ufds:UnionFind]: error allocating memory\n");
        return NULL;
    }
    ret->rank = malloc(sizeof(int) * size);
    if (!ret->rank) {
        free(ret);
        fprintf(stderr, "[ufds:UnionFind]: error allocating memory\n");
        return NULL;
    }
    ret->parent = malloc(sizeof(int) * size);
    if (!ret->parent) {
        free(ret->rank);
        free(ret);
        fprintf(stderr, "[ufds:UnionFind]: error allocating memory\n");
        return NULL;
    }
    ret->size = malloc(sizeof(int) * size);
    if (!ret->size) {
        free(ret->parent);
        free(ret->rank);
        free(ret);
        fprintf(stderr, "[ufds:UnionFind]: error allocating memory\n");
        return NULL;
    }

    ret->len = size;
    memset(ret->rank, 0, size);
    memset(ret->size, 0, size);
    for (int i = 0; i < size; i++) {
        ret->parent[i] = i;
    }
}

// Return the representative item of the set
int findSet(int i, struct ufds *uf) {
    if (uf->parent[i] != i) {
        return uf->parent[i] = findSet(uf->parent[i]);
    }
    return i;
}

// Return true if both items are within the same disjoint set
int in_same_set(int i, int j, struct ufds *uf) {
    return findSet(i, uf) == findSet(j, uf);
}

// Join two disjoint sets together
void unionSet(int i, int j, struct ufds *uf) {
    if (!in_same_set(i, j, uf)) {
        int ri = findSet(i), rj = findSet(j);
        if (uf->rank[ri] < uf->rank[rj]) {
            uf->parent[ri] = rj;
            uf->size[rj]++;
        } else {
            uf->parent[rj] = ri; 
            if (uf->rank[ri] == uf->rank[rj]) {
                uf->rank[rj]++;
                uf->size[rj]++;
            }
        }
        uf->num_sets--;
    }
}

