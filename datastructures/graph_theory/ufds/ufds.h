#ifndef UFDS_H

/*
 * The Union Find Disjoint Set data structure.
 * Useful applications include Kruskal's algorithm
 * for finding a MST of an undirected graph.
 */

struct ufds {
    /* Rank -
     *  the upper bound of the height of a tree
     *  in the forest of sets.
     * Parent -
     *  The value at i in this array is the index
     *  of the representative item of i. We can
     *  assign each set a unique representative
     *  item, and construct a tree in the parent
     *  array. Since there is one root in a tree,
     *  this makes a good representative item
     *  of all elements in the set.
     * Size -
     *  Convenience array, used to keep track of
     *  the size of a set.
     */
    int *rank, *parent, *size;
    /*
     * Len - 
     *  Doubles as the size of rank/parent/size
     *  arrays, and the number of total items
     *  in the union find.
     */
    size_t len;
    /*
     * num_sets:
     *  The number of disjoint sets in the union
     *  find.
     */
    int num_sets;
};

struct ufds *UnionFind(int size);
int findset(int i, struct ufds *uf);
void unionSet(int a, int b, struct ufds *uf);
int in_same_set(int i, int j, struct ufds *uf);
int num_sets(struct ufds *uf);
int set_size(int i, struct ufds *uf);

#endif
