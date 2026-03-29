// Mergesort implementation

#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
using namespace std;

struct Element {
	int value;
	int originalIndex;
};

Element* generateRandomArray(int sizeOfArray){
	Element* array = new Element[sizeOfArray];
	for(int index = 0; index < sizeOfArray; index++){
		int random = rand() % (11);
		array[index].value = random;
		array[index].originalIndex = index;
	}
	return array;
}

Element* merge(Element sortedArray_B[], Element sortedArray_C[], int p, int q){
	Element* sortedArray = new Element[p + q];
	int i = 0, j = 0, k = 0;
	while(i < p && j < q){
		if(sortedArray_B[i].value <= sortedArray_C[j].value){
			sortedArray[k] = sortedArray_B[i];
			i += 1;
		} else{
			sortedArray[k] = sortedArray_C[j];
			j += 1;
		}
		k += 1;
	}
	if(i == p){
		for(int index = k; index < p + q; index++)
			sortedArray[index] = sortedArray_C[index - p];
	} else{
		for(int index = k; index < p + q; index++)
			sortedArray[index] = sortedArray_B[index - q];
	}
	return sortedArray;
}

Element* mergesort(Element array[], int sizeOfArray){
	if(sizeOfArray <= 1){
		Element* sortedArray = new Element[sizeOfArray];
		for(int i = 0; i < sizeOfArray; i++)
			sortedArray[i] = array[i];
		return sortedArray;
	}
	int halfSizeOfArray = floor(sizeOfArray / 2);
	Element* array_B = new Element[halfSizeOfArray];
	Element* array_C = new Element[sizeOfArray - halfSizeOfArray];
	for(int i = 0; i < halfSizeOfArray; i++){
		array_B[i] = array[i];
		array_C[i] = array[i + halfSizeOfArray];
	}
	if(sizeOfArray % 2 != 0)
		array_C[halfSizeOfArray] = array[sizeOfArray - 1];
	Element* sortedArray_B = mergesort(array_B, halfSizeOfArray);
	Element* sortedArray_C = mergesort(array_C, sizeOfArray - halfSizeOfArray);
	Element* sortedArray = merge(sortedArray_B, sortedArray_C, halfSizeOfArray, sizeOfArray - halfSizeOfArray);
	delete[] array_B;
	delete[] array_C;
	delete[] sortedArray_B;
	delete[] sortedArray_C;
	return sortedArray;
}

void printArray(Element array[], int sizeOfArray){
	for(int i = 0; i < sizeOfArray; i++)
		cout << "(" << array[i].value << ", original index " << array[i].originalIndex << ") ";
}

int main(){
	srand(time(0));
	int sizeOfArray = 10;
	Element* array = generateRandomArray(sizeOfArray);
	cout << "Unsorted array:" << endl;
	printArray(array, sizeOfArray);
	cout << endl;
	Element* sortedArray = mergesort(array, sizeOfArray);
	cout << "Sorted array:" << endl;
	printArray(sortedArray, sizeOfArray);
	cout << endl;
	delete[] sortedArray;
	return 0;
}
