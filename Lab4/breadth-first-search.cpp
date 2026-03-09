// Breadth-First search

#include <bits/stdc++.h>
using namespace std;

// VARIABLES

int graphSize;

// FUNCTIONS

vector<vector<int>> buildAdjacencyList(vector<pair<int,int>> edgeList){
    vector<vector<int>> adjacencyList(graphSize);
    for(int i = 0; i < edgeList.size(); i++){
        int sourceNode = edgeList[i].first;
        int destinationNode = edgeList[i].second;
        adjacencyList[sourceNode].push_back(destinationNode);
        adjacencyList[destinationNode].push_back(sourceNode); 
    }
    return adjacencyList;
}

vector<int> breadthFirstSearch(int startNode, vector<vector<int>>& adjacencyList){
    vector<bool> visitedNodes(graphSize, false);
    vector<int> traversalOrder;
    queue<int> nodeQueue;
    visitedNodes[startNode] = true;
    nodeQueue.push(startNode);

    while(!nodeQueue.empty()){
        int currentNode = nodeQueue.front();
        nodeQueue.pop();
        traversalOrder.push_back(currentNode);
        for(int i = 0; i < adjacencyList[currentNode].size(); i++){
            int neighborNode = adjacencyList[currentNode][i];
            if(!visitedNodes[neighborNode]){
                visitedNodes[neighborNode] = true;
                nodeQueue.push(neighborNode);
            }
        }
    }
    return traversalOrder;
}

// MAIN FUNCTION

int main(){
    graphSize = 6;
    vector<pair<int,int>> edgeList = {
        {0, 1}, {0, 2}, {1, 3}, {1, 4}, {2, 5}
    };
    vector<vector<int>> adjacencyList = buildAdjacencyList(edgeList);
    int startNode = 0;
    vector<int> traversalOrder = breadthFirstSearch(startNode, adjacencyList);
    cout << "BFS traversal from node " << startNode << ": ";
    for(int i = 0; i < traversalOrder.size(); i++){
        cout << traversalOrder[i];
        if(i < traversalOrder.size() - 1) cout << " -> ";
    }
    cout << endl;
    return 0;
}
