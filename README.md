# MST Comparison Project

This project compares the Minimum Spanning Tree (MST) algorithms, Kruskal's and Prim's, for increasing density and sizes of randomized integer datasets. The comparison is based on the time complexities of the algorithms.

## Project Structure

- `src`: Contains the source code for the project.
  - `main.cpp`: The main C++ file responsible for executing the comparison.
  - `graph.cpp`: Defines the Graph class for creating and managing graphs.
  - `mst_algorithms.cpp`: Implements the Kruskal's and Prim's MST algorithms.
- `data`: Holds the CSV file (`combined_timing_results.csv`) with algorithmic timing results.
- `venv`: Python virtual environment for managing Python dependencies.

## Virtual Environment Setup (Python)

To set up the Python environment, follow these steps:

1. Create a virtual environment:

```bash
python3 -m venv venv
```
2. Install the required Python packages:
```bash
pip install matplotlib
```
## Running the C++ Code
1. Compile the C++ code:
```bash
g++ -std=c++11 -o mst_comparison src/main.cpp src/graph.cpp src/mst_algorithms.cpp
```
2. Run the compiled executable:
```bash
./mst_comparison
```

This will execute the MST algorithms on the provided datasets and generate a CSV file (combined_timing_results.csv) with the timing results.

## Results
The project generates 3D scatter plots and heatmaps comparing the time complexities of Kruskal's and Prim's algorithms for different graph sizes and densities. The results are visualized using the matplotlib library in Python.

## Dependencies
C++ Code: None (standard libraries only)
Python Script: Matplotlib