# Network Influence Analysis with Gephi

This project focuses on analyzing the influence spread within a social network using a C++ program and visualizing the results with Gephi.

## Overview

The provided C++ code calculates the influence each node has in a network. Each node starts with an influence score of 1.0, and in each iteration, they distribute half of their influence equally among the nodes they follow. The simulation runs for 50 iterations to allow influence to propagate through the network.

## Getting Started

### Prerequisites

- Gephi 0.9.x
- C++ compiler (C++11 or higher)
- Make sure to have `tweeter.csv` file which includes the network data in the following format:
  ```
  Source,Target
  1,2
  1,3
  ...
  ```

### Running the Code

1. Compile the C++ code using a C++11 compatible compiler.
   ```bash
   g++ -std=c++11 -o network_analysis Headquater_algorithm.cpp
   ```
2. Run the compiled program.
   ```bash
   ./network_analysis
   ```
3. This will generate two CSV files:
   - `influence.csv` - Contains the influence score for each node.
   - `node_influence.csv` - Contains the influence score for each node formatted for Gephi input.

### Visualizing in Gephi

1. Open Gephi and create a new project.
2. Import the `tweeter.csv` as an edge table to construct the network graph.
3. Import the `node_influence.csv` as a node table to overlay the influence scores onto the network.
4. Apply a layout algorithm such as ForceAtlas 2 to position nodes with higher in-degree influence towards the center of the graph.
5. Use the Partition or Ranking feature to adjust the node color or size based on the influence score.
6. Adjust the visualization settings to highlight key nodes and patterns.
7. Export the visualization as an image or PDF for reporting or further analysis.

## Analysis

The influence scores can provide insights into which nodes are central in spreading information or which nodes have the potential to be key influencers within the network.


