#include "ufds.h"

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
        } else {
            uf->parent[rj] = ri; 
            if (rank[ri] == rank[rj]) {
                rank[rj]++;
            }
        }
    }
}

// Find the number of items in a set
int num_sets(struct ufds *uf) {
    int count = 0;
    for (int i = 0; i < SIZE OF PARENTS ARR; i++) {
        if (p[i] != i) {
            count++;
        }
    }
    return count;
}

// Find the size of a set
int set_size(int i, struct ufds *uf) {
    int count = 0;
    for (int j = 0; j < SIZE OF PARENTS ARR; j++) {
        if (findSet(j) == i) {
            count++; 
        }
    }
    return count;
}

