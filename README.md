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

### Algorithm Details

The algorithm is implemented in the `Headquater_algorithm.cpp` file. The algorithm is implemented in the following steps:

1. Read the network data from the `tweeter.csv` file.
2. In every node, initialize the influence score to 1.0.
3. In every iteration, propagate the influence score from each node to the nodes it follows. The influence score is divided equally among the nodes it follows but 

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

## Nov 29, 2023 Update
-----------------
- 기존의 전파 알고리즘에 오류가 있어서 수정하였고, 노드가 제대로 연결되었습니다.
- 의도대로 구현 시, 노드의 영향력 간 차이가 매우 크게 나타나 이러한 편차를 줄이기 위해 다음과 같은 시도를 했습니다.
  - 전파는 그대로 진행하되, Logarithm 적용하여 최종 출력하는 영향력을 조정하였습니다.
- 이후 한 가지 고려사항으로, 노드에서 다음 노드에 영향력을 전파할 때 leak을 적용해 influence의 과도한 누적을 방지할까 합니다.

## DEC 2, 2023 Update
-----------------
- DECAY_RATE를 적용해, following이 없어 영향력이 계속해서 누적되는 경우 decay를 적용하였습니다
- Log scale을 10으로 적용했고, 이에 따라 초기 노드의 영향력을 10으로 설정하였습니다.
- 출력하면 0~3까지의 4단계의 노드로 분류하도록 하였습니다.

![Prototype.png](https://github.com/junnystateofmind/Social_Network_Analysis/blob/main/Prototype.png)
<embed src="./Prototype.pdf" type="application/pdf" width="100%" height="600px" />
