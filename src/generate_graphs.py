import pandas as pd
import matplotlib.pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# Correct the indentation of the function definition
def measure_mst_time(graph):
    kruskal_result = kruskalMST(graph)
    prim_result = primMST(graph)
    return kruskal_result.kruskalTime, prim_result.primTime

data = pd.read_csv("combined_timing_results.csv")

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
ax.set_xlabel('Number of Nodes')
ax.set_ylabel('Density')
ax.set_zlabel('Time (seconds)')

x = data['Nodes']
y = data['Density']
z_kruskal = data['Kruskal']
z_prim = data['Prim']

ax.scatter(x, y, z_kruskal, c='r', marker='o', label='Kruskal')
ax.scatter(x, y, z_prim, c='b', marker='^', label='Prim')

ax.legend()
plt.show()
