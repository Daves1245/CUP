#include "kruskals.h"
#include "ufds.h"
#include "vector.h"

/* Return the cost of a MST of the given graph */
int kruskals(int E, vector *edgeList) {
    struct ufds *unionfind = UnionFind(E);
    int cost = 0;
    /* sort(edgeList); */
    for (int i = 0; i < E; i++) {
        struct elem *e = vector_get(edgeList, i);
        if (!in_same_set(e->pair.u,e->pair.v, unionfind)) {
            cost += e->w;
            /*
             * Because this operation is amortized constant time,
             * kruskals runs at O(ElgV) and the main runtime cost
             * is in sorting the edgeList, above.
             */
            unionSet(e->pair.u, e->pair.v, unionfind);
        }
        if (unionfind->num_sets == 1) {
            /* Stop if we've collected every vertex - this forms an MST */
            return cost;
        }
    }
    return cost;
}
