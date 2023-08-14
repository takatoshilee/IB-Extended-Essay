#include "../include/graph.h"

Graph::Graph(int numNodes) : numNodes(numNodes) {
    adjList.resize(numNodes);
    nodes.resize(numNodes);
}

void Graph::addEdge(int source, int destination, int weight) {
    edges.emplace_back(source, destination, weight);
    adjList[source].push_back(edges.back());
    adjList[destination].push_back(edges.back()); // For undirected graph
}