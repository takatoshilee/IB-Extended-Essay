import matplotlib.pyplot as plt
import pandas as pd

# Load data from CSV files
size_data = pd.read_csv("size_timing_results.csv")
density_data = pd.read_csv("density_timing_results.csv")

# Plot for size-based graphs
plt.figure(figsize=(10, 5))
plt.subplot(1, 2, 1)
plt.plot(size_data["Nodes"], size_data["Kruskal"], label="Kruskal")
plt.plot(size_data["Nodes"], size_data["Prim"], label="Prim")
plt.xlabel("Number of Nodes")
plt.ylabel("Time (seconds)")
plt.title("MST Algorithm Comparison (Size-Based)")
plt.legend()

# Plot for density-based graphs
plt.subplot(1, 2, 2)
plt.plot(density_data["Density"], density_data["Kruskal"], label="Kruskal")
plt.plot(density_data["Density"], density_data["Prim"], label="Prim")
plt.xlabel("Density")
plt.ylabel("Time (seconds)")
plt.title("MST Algorithm Comparison (Density-Based)")
plt.legend()

plt.tight_layout()

# Save the plots
plt.savefig("mst_comparison_plots.png")

# Show the plots
plt.show()
