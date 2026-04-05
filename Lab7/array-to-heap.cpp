#include <iostream>
#include <ctime>
#include <cstdlib>
#include <vector>
#include <algorithm>

using namespace std;

class Node{
public:
    int value;
    Node* left;
    Node* right;
    Node() : value(0), left(nullptr), right(nullptr){}
    Node(int val) : value(val), left(nullptr), right(nullptr){}
};

int* arrayGenerator(int sizeOfArray){
    int* array = new int[sizeOfArray];
    for(int index = 0; index < sizeOfArray; index++)
        array[index] = rand() % 21;
    return array;
}

Node* saveNodeToArray(int* array, int sizeOfArray){
    Node* nodeArray = new Node[sizeOfArray];
    for(int index = 0; index < sizeOfArray; index++){
        nodeArray[index] = Node(array[index]);
    }
    return nodeArray;
}

void connectNodes(Node* nodeArray, int size){
    for(int index = 0; index < size; index++){
        int leftIndex = 2 * index + 1;
        int rightIndex = 2 * index + 2;
        if(leftIndex < size)
            nodeArray[index].left = &nodeArray[leftIndex];
        if(rightIndex < size)
            nodeArray[index].right = &nodeArray[rightIndex];
    }
}

void printArray(int* array, int sizeOfArray){
	cout << "Initial array:" << endl;
	for(int index = 0; index < sizeOfArray; index++)
		cout << array[index] << " ";
	cout << endl;
}

void treeToHeap(Node* nodeArray, int size, int index){
    int largest = index;
    int left = 2 * index + 1;
    int right = 2 * index + 2;
    if(left < size && nodeArray[left].value > nodeArray[largest].value)
        largest = left;
    if(right < size && nodeArray[right].value > nodeArray[largest].value)
        largest = right;
    if(largest != index){
        swap(nodeArray[index].value, nodeArray[largest].value);
        treeToHeap(nodeArray, size, largest);
    }
}

void buildMaxHeap(Node* nodeArray, int size){
    for(int index = size / 2 - 1; index >= 0; index--){
        treeToHeap(nodeArray, size, index);
    }
}

void printTree(Node* root, int depth = 0){
    if(!root) return;
    for(int index = 0; index < depth; index++) cout << "  ";
    cout << "|--" << root->value << endl;
    printTree(root->left, depth + 1);
    printTree(root->right, depth + 1);
}

int main(){
    srand(time(0));
    int size = 7;
    int* data = arrayGenerator(size);
    printArray(data, size);
    Node* nodes = saveNodeToArray(data, size);
    connectNodes(nodes, size);
    buildMaxHeap(nodes, size);
    cout << "Heap from array:" << endl;
    printTree(&nodes[0]);
    delete[] data;
    delete[] nodes;
    return 0;
}
