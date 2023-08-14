#include <iostream>
#include <algorithm>
#include <vector>
#include <stdexcept> // Add this include for exception handling
#include <climits>
#include <chrono>
#include <queue>

#include "../include/mst_algorithms.h"
#include "../include/graph.h" // Correct the path to the header file


int findParent(std::vector<int>& parent, int node) {
    if (node < 0 || node >= parent.size()) {
        std::cout << "Invalid node index: " << node << std::endl;
        return -1; // Return some sentinel value to indicate an error
    }

    // std::cout << "Accessing parent[" << node << "]" << std::endl;

    if (parent[node] != node) {
        // std::cout << "Recursing for parent[" << node << "]: " << parent[node] << std::endl;
        parent[node] = findParent(parent, parent[node]);
    }
    return parent[node];
}


void unionSets(int node1, int node2, std::vector<int>& parent, std::vector<int>& rank) {
    int root1 = findParent(parent, node1);
    int root2 = findParent(parent, node2);

    if (root1 != root2) {
        if (rank[root1] < rank[root2]) {
            std::swap(root1, root2);
        }
        parent[root2] = root1;
        if (rank[root1] == rank[root2]) {
            rank[root1]++;
        }
    }
}

MSTResult kruskalMST(const Graph& graph) {
    MSTResult result;
    std::vector<Edge> minimumSpanningTree;
    std::vector<int> parent(graph.nodes.size());
    std::vector<int> rank(graph.nodes.size(), 0);

    for (size_t i = 0; i < parent.size(); i++)
        parent[i] = i;

    std::vector<Edge> sortedEdges = graph.edges;
    std::sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& e1, const Edge& e2) {
        return e1.weight < e2.weight;
    });

    auto start = std::chrono::high_resolution_clock::now();

    // Kruskal's algorithm implementation
    for (const Edge& edge : sortedEdges) {
        int sourceParent = findParent(parent, edge.source);
        int destinationParent = findParent(parent, edge.destination);

        if (sourceParent != destinationParent) {
            minimumSpanningTree.push_back(edge);
            unionSets(edge.source, edge.destination, parent, rank);
        }
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    result.kruskalMST = minimumSpanningTree;
    result.kruskalTime = duration.count();


    return result;
}

MSTResult primMST(const Graph& graph) {
    MSTResult result;
    std::vector<Edge> minimumSpanningTree;
    int numVertices = graph.nodes.size();

    std::vector<int> key(numVertices, INT_MAX);
    std::vector<int> parent(numVertices, -1);

    std::vector<char> mstSet(numVertices, false);

    int rootNode = 0;
    key[rootNode] = 0;
    parent[rootNode] = -1;

    auto start = std::chrono::high_resolution_clock::now();

    // Priority queue to store vertices with their keys
    std::priority_queue<std::pair<int, int>, std::vector<std::pair<int, int>>, std::greater<std::pair<int, int> > > pq;
    pq.push(std::make_pair(0, rootNode));

    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        if (mstSet[u])
            continue;

        mstSet[u] = true;

        for (const Edge& edge : graph.getEdges(u)) { // Use getEdges function here
            int v = edge.destination;
            int weight = edge.weight;

            if (!mstSet[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push(std::make_pair(key[v], v));
            }
        }
    }

    for (int i = 1; i < numVertices; i++) {
        minimumSpanningTree.push_back(Edge(parent[i], i, key[i]));
    }

    auto end = std::chrono::high_resolution_clock::now();
    std::chrono::duration<double> duration = end - start;

    result.primMST = minimumSpanningTree;
    result.primTime = duration.count();

    return result;
}
