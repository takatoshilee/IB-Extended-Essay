#ifndef MST_ALGORITHMS_H
#define MST_ALGORITHMS_H

#include "graph.h"
#include <vector>

struct MSTResult {
    std::vector<Edge> kruskalMST;  // Minimum spanning tree edges from Kruskal's algorithm
    double kruskalTime;  // Time taken for Kruskal's algorithm

    std::vector<Edge> primMST;  // Minimum spanning tree edges from Prim's algorithm
    double primTime;  // Time taken for Prim's algorithm
};



MSTResult kruskalMST(const Graph& graph);

MSTResult primMST(const Graph& graph);

#endif // MST_ALGORITHMS_H
