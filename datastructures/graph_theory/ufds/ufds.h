#ifndef UFDS_H

/*
 * The Union Find Disjoint Set data structure.
 * Useful applications include Kruskal's algorithm
 * for finding a MST of an undirected graph.
 */

struct ufds {
    int *rank, *parent;
};

int findset(int i, struct ufds *uf);
void unionSet(int a, int b, struct ufds *uf);
int in_same_set(int i, int j, struct ufds *uf);
int num_sets(struct ufds *uf);
int set_size(int i, struct ufds *uf);

#endif
