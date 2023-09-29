#ifndef GRAPH_H
#define GRAPH_H

#include <vector>

struct Edge {
    int source;
    int destination;
    int weight;

    Edge(int src, int dest, int w) : source(src), destination(dest), weight(w) {}
};

struct Node {
    int id;
};

class Graph {
public:
    std::vector<Edge> edges;
    std::vector<Node> nodes;
    
    Graph(int numNodes);

    void addEdge(int source, int destination, int weight);

    const std::vector<Edge>& getEdges(int vertex) const {
        return adjList[vertex];
    }

private:
    int numNodes;
    std::vector<std::vector<Edge> > adjList;

};

#endif 