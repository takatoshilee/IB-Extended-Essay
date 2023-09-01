import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
import numpy as np
from matplotlib.colors import ListedColormap

# Load data from CSV
data = pd.read_csv("combined_timing_results.csv")

# Create a 2D grid for nodes and density
nodes = data['Nodes'].unique()
density = data['Density'].unique()
X, Y = np.meshgrid(nodes, density)

# Calculate the performance difference (Kruskal - Prim) for each combination
performance_diff = data['Kruskal'] - data['Prim']

# Reshape the performance difference into a 2D array
Z = performance_diff.values.reshape(len(density), len(nodes))

# Create a custom colormap: blue for Prim and red for Kruskal
colors = ['blue' if val < 0 else 'red' for val in performance_diff]
cmap = ListedColormap(colors)

# Create the figure and 3D scatter plot
fig = plt.figure(figsize=(12, 10))
gs = fig.add_gridspec(2, 1, height_ratios=[6, 2], hspace=0.3)

# First subplot: 3D scatter plot
ax1 = fig.add_subplot(gs[0], projection='3d')
ax1.set_xlabel('Number of Nodes')
ax1.set_ylabel('Density')
ax1.set_zlabel('Time Difference (Kruskal - Prim)')

# Scatter plot for Kruskal and Prim
ax1.scatter(data['Nodes'], data['Density'], data['Kruskal'], c='r', marker='o', label='Kruskal')
ax1.scatter(data['Nodes'], data['Density'], data['Prim'], c='b', marker='^', label='Prim')

# Create the heatmap plot beneath the 3D scatter plot
heatmap = ax1.plot_surface(X, Y, Z, cmap='coolwarm', alpha=0.5)

# Add colorbar
cbar = plt.colorbar(heatmap, ax=ax1, label='Time Difference (Kruskal - Prim)')

ax1.legend()

# Second subplot: Heatmap for better performing algorithm
ax2 = fig.add_subplot(gs[1])
heatmap_better = ax2.pcolormesh(X, Y, Z, cmap=cmap, shading='auto')

# Add colorbar for the second heatmap
cbar2 = plt.colorbar(heatmap_better, ax=ax2, label='Better Algorithm (Prim vs Kruskal)')

plt.tight_layout()
plt.show()
