#ifndef KRUSKALS_H
#define KRUSKALS_H

#include "vector.h"

/* DUMMY HEADER */

/*
 * These aren't actually
 * essential to kruskal's - 
 * I will remove these later (TODO edgeList for convenience?)
 * For now there's just for convenience
 */
struct vertexPair {
    int u, v;
};

struct elem {
    int w; /* Weight of this edge */
    struct vertexPair pair; /* The vertices it connects */
};

/* Returns the cost of a MST of the graph depicted by edgeList */
int kruskals(int num_edges, vector *edgeList);

#endif
