// Depth-First search

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

void depthFirstSearch(int currentNode, vector<vector<int>>& adjacencyList, vector<bool>& visitedNodes, vector<int>& traversalOrder){
    visitedNodes[currentNode] = true;
    traversalOrder.push_back(currentNode);
    for(int i = 0; i < adjacencyList[currentNode].size(); i++){
        int neighborNode = adjacencyList[currentNode][i];
        if(!visitedNodes[neighborNode]){
            depthFirstSearch(neighborNode, adjacencyList, visitedNodes, traversalOrder);
        }
    }
}

vector<int> runDepthFirstSearch(int startNode, vector<vector<int>>& adjacencyList){
    vector<bool> visitedNodes(graphSize, false);
    vector<int>  traversalOrder;
    depthFirstSearch(startNode, adjacencyList, visitedNodes, traversalOrder);
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
    vector<int> traversalOrder = runDepthFirstSearch(startNode, adjacencyList);
    cout << "DFS traversal from node " << startNode << ": ";
    for(int i = 0; i < traversalOrder.size(); i++){
        cout << traversalOrder[i];
        if(i < traversalOrder.size() - 1) cout << " -> ";
    }
    cout << endl;
    return 0;
}
