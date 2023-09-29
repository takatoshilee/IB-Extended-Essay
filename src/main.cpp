#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
#include <unordered_set>
#include <chrono>   
#include <sstream>
#include <random>
#include <string>
#include <queue>

#include "../include/graph.h"
#include "../include/mst_algorithms.h"


Graph generateRandomGraph(int numNodes, double density) {
    Graph graph(numNodes);

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> weightDist(1, 100);

    for (int i = 0; i < numNodes; ++i) {
        for (int j = i + 1; j < numNodes; ++j) {
            double random = static_cast<double>(gen()) / static_cast<double>(gen.max());
            if (random < density) {
                int weight = weightDist(gen);
                graph.addEdge(i, j, weight);
                graph.addEdge(j, i, weight); 
            }
        }
    }

    return graph;
}

void runAndPrintMSTAlgorithms(const Graph& graph) {
    // KRUSKAL
    MSTResult kruskalResult = kruskalMST(graph);
    std::cout << "Kruskal's MST:\n";
    for (const Edge& edge : kruskalResult.kruskalMST) {
        std::cout << edge.source << " - " << edge.destination << " (" << edge.weight << ")\n";
    }
    std::cout << "Time taken for Kruskal's algorithm: " << kruskalResult.kruskalTime << " seconds\n";

    // PRIM
    MSTResult primResult = primMST(graph);
    std::cout << "Prim's MST:\n";
    for (const Edge& edge : primResult.primMST) {
        std::cout << edge.source << " - " << edge.destination << " (" << edge.weight << ")\n";
    }
    std::cout << "Time taken for Prim's algorithm: " << primResult.primTime << " seconds\n";
}


MSTResult runMSTAlgorithms(const Graph& graph) {
    // KRUSKAL
    MSTResult kruskalResult = kruskalMST(graph);

    // PRIM
    MSTResult primResult = primMST(graph);

    // Store the individual results
    return {kruskalResult.kruskalMST, kruskalResult.kruskalTime, primResult.primMST, primResult.primTime};
}


int main() {
    int numGraphs = 10;
    int initialSize = 100; 
    double sizeIncrement = 100.0; 
    double initialDensity = 0.1; 
    double densityIncrement = 0.1; 

    std::ofstream combinedOutputFile("combined_timing_results.csv");
    combinedOutputFile << "Nodes,Density,Kruskal,Prim\n";

    for (int i = 0; i < numGraphs; ++i) {
        int numNodes = initialSize + static_cast<int>(i * sizeIncrement);

        for (int j = 0; j < numGraphs; ++j) {
            double density = initialDensity + j * densityIncrement;

            Graph graph = generateRandomGraph(numNodes, density);

            MSTResult results = runMSTAlgorithms(graph);

            combinedOutputFile << numNodes << "," << density << "," << results.kruskalTime << "," << results.primTime << "\n";
        }
    }

    combinedOutputFile.close(); 

    system("python3 src/generate_graphs.py");

    return 0;
}
