#include <iostream>
#include <vector>
#include <fstream>
#include <climits>
#include <algorithm>
#include <unordered_set>
#include <chrono>   // Add this include for timing measurements
#include <sstream>
#include <random>
#include <string>
#include <queue>

#include "../include/graph.h"
#include "../include/mst_algorithms.h"


// Function to generate a random graph with given number of nodes and density
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
                graph.addEdge(j, i, weight); // Graph is undirected
            }
        }
    }

    return graph;
}

void runAndPrintMSTAlgorithms(const Graph& graph) {
    // Kruskal's algorithm
    MSTResult kruskalResult = kruskalMST(graph);
    std::cout << "Kruskal's MST:\n";
    for (const Edge& edge : kruskalResult.kruskalMST) {
        std::cout << edge.source << " - " << edge.destination << " (" << edge.weight << ")\n";
    }
    std::cout << "Time taken for Kruskal's algorithm: " << kruskalResult.kruskalTime << " seconds\n";

    // Prim's algorithm
    MSTResult primResult = primMST(graph);
    std::cout << "Prim's MST:\n";
    for (const Edge& edge : primResult.primMST) {
        std::cout << edge.source << " - " << edge.destination << " (" << edge.weight << ")\n";
    }
    std::cout << "Time taken for Prim's algorithm: " << primResult.primTime << " seconds\n";
}


MSTResult runMSTAlgorithms(const Graph& graph) {
    // Kruskal's algorithm
    MSTResult kruskalResult = kruskalMST(graph);

    // Prim's algorithm
    MSTResult primResult = primMST(graph);

    // Store the individual results
    return {kruskalResult.kruskalMST, kruskalResult.kruskalTime, primResult.primMST, primResult.primTime};
}




int main() {
    int numGraphs = 10; // Number of graphs for each factor
    int initialSize = 100; // Initial graph size
    double sizeIncrement = 100.0; // Size increment between graphs
    double initialDensity = 0.2; // Initial graph density
    double densityIncrement = 10; // Density increment between graphs

    // Create a CSV file for graph size timing results
    std::ofstream sizeOutputFile("size_timing_results.csv");
    sizeOutputFile << "Nodes,Kruskal,Prim\n"; // Write header

    // Generate graphs based on size
    for (int i = 0; i < numGraphs; ++i) {
        int numNodes = initialSize + static_cast<int>(i * sizeIncrement);

        Graph graph = generateRandomGraph(numNodes, initialDensity);

        MSTResult results = runMSTAlgorithms(graph);

        // Write the timing results to the CSV file
        sizeOutputFile << numNodes << "," << results.kruskalTime << "," << results.primTime << "\n";
    }

    sizeOutputFile.close(); // Close the CSV file

    // Create a CSV file for density timing results
    std::ofstream densityOutputFile("density_timing_results.csv");
    densityOutputFile << "Density,Kruskal,Prim\n"; // Write header

    // Generate graphs based on density
    for (int i = 0; i < numGraphs; ++i) {
        int numNodes = initialSize + static_cast<int>(i * sizeIncrement);
        double density = initialDensity + i * densityIncrement;

        Graph graph = generateRandomGraph(numNodes, density);

        MSTResult results = runMSTAlgorithms(graph);

        // Write the timing results to the CSV file
        densityOutputFile << density << "," << results.kruskalTime << "," << results.primTime << "\n";
    }

    densityOutputFile.close(); // Close the CSV file

    // Run the Python script to generate plots
    system("python3 src/generate_graphs.py");

    return 0;
}
