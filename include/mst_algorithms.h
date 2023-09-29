#ifndef MST_ALGORITHMS_H
#define MST_ALGORITHMS_H

#include "graph.h"
#include <vector>

struct MSTResult {
    std::vector<Edge> kruskalMST; 
    double kruskalTime;

    std::vector<Edge> primMST;  
    double primTime;
};



MSTResult kruskalMST(const Graph& graph);

MSTResult primMST(const Graph& graph);

#endif 
