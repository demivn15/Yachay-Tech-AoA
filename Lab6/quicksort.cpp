#include <bits/stdc++.h>
#include <iostream>
#include <cmath>
#include <chrono>
using namespace std;

int* generateRandomArray(int sizeOfArray){
	int* array = new int[sizeOfArray];
	for(int index = 0; index < sizeOfArray; index++){
		int random = rand() % (101);
		array[index] = random;
	}
	return array;
}

int partition(int array[], int sizeOfArray){
	int l = 0, r = sizeOfArray - 1;
	int p = array[l];
	int i = l + 1, j = r, aux;
	while(i <= j){
		while(i <= r && array[i] < p)
			i += 1;
		while(j > l && array[j] > p)
			j -= 1;
		if(i < j){
			aux = array[i];
			array[i] = array[j];
			array[j] = aux;
			i += 1;
			j -= 1;
		} else{
			break;
		}
	}
	aux = array[l];
	array[l] = array[j];
	array[j] = aux;
	return j;
}

void quicksort(int array[], int sizeOfArray){
	int l = 0, r = sizeOfArray - 1;
	if(l < r){
		int s = partition(array, sizeOfArray);
		int sizeOf_array_A = s;
		int sizeOf_array_B = sizeOfArray - s - 1;
		int* array_A = new int[sizeOf_array_A];
		int* array_B = new int[sizeOf_array_B];
		for(int index = 0; index < sizeOf_array_A; index++){
			array_A[index] = array[index];
		}
		for(int index = 0; index < sizeOf_array_B; index++){
			array_B[index] = array[index + s + 1];
		}
		quicksort(array_A, sizeOf_array_A);
		quicksort(array_B, sizeOf_array_B);
		for(int index = 0; index < sizeOf_array_A; index++){
			array[index] = array_A[index];
		}
		for(int index = 0; index < sizeOf_array_B; index++){
			array[index + s + 1] = array_B[index];
		}
		delete[] array_A;
		delete[] array_B;
	}
}

void printArray(int array[], int sizeOfArray){
	for(int i = 0; i < sizeOfArray; i++)
		cout << array[i] << " ";
}

int main(){
	srand(time(0));
	int sizeArray[9] = {100000, 200000, 300000, 400000, 500000, 600000, 700000, 800000, 900000};
	std::chrono::duration<double> timeArray[9];
	for(int i = 0; i < 9; i++){ 
		int sizeOfArray = sizeArray[i];
		int* array = generateRandomArray(sizeOfArray);
// 		printArray(array, sizeOfArray);
// 		cout << endl;
		auto start = std::chrono::high_resolution_clock::now();
		quicksort(array, sizeOfArray);
		auto end = std::chrono::high_resolution_clock::now();
		std::chrono::duration<double> duration = end - start;
		timeArray[i] = duration;
// 		printArray(array, sizeOfArray);
// 		cout << endl;
		delete[] array;
	}
	ofstream MyFile("quicksort-empirical.csv");
	for(int i = 0; i < 9; i++){
		cout << "Size of array: " << sizeArray[i] << " | Execution time: " << timeArray[i].count() << "s" << endl;
		MyFile << sizeArray[i] << "," << timeArray[i].count() << endl;
	}
	MyFile.close();
	cout << endl;
	int sizeOfArray = 10;
	int* array = generateRandomArray(sizeOfArray);
	printArray(array, sizeOfArray);
	cout << endl;
	quicksort(array, sizeOfArray);
	printArray(array, sizeOfArray);
	cout << endl;
	delete[] array;
	return 0;
}
