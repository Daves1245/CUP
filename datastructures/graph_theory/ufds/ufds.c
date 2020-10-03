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
