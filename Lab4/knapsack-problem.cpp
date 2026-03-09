// 0/1 knapsack problem.

// HEADERS

#include <vector>
#include <bits/stdc++.h>

using namespace std;

int problemSize;
vector<vector<int>> powerSet;

// FUNCTIONS

int randomNumberGenerator(int maxValue){
	int randomNumber = rand() % (maxValue + 1);
	return randomNumber;
}

vector<int> funcItemValueVectorCreator(int maxItemValue){
	vector<int> itemValueVector;
	for(int i = 0; i < problemSize; i++){
		itemValueVector.push_back(randomNumberGenerator(maxItemValue));
	}
	return itemValueVector;
}

vector<int> funcItemWeightVectorCreator(int maxItemWeight){
	vector<int> itemWeightVector;
	for(int i = 0; i < problemSize; i++){
		itemWeightVector.push_back(randomNumberGenerator(maxItemWeight));
	}
	return itemWeightVector;
}

vector<vector<int>> funcBacktracking(vector<int> currentSet, int currentSetIndex){
	if(currentSetIndex == problemSize){
		powerSet.push_back(currentSet);
		return powerSet;
	}
	currentSet.push_back(currentSetIndex);
	funcBacktracking(currentSet, currentSetIndex + 1);
	currentSet.pop_back();
	funcBacktracking(currentSet, currentSetIndex + 1);
	return powerSet;
}

vector<vector<int>> feasibleSubsets(vector<int> itemWeightVector, vector<vector<int>> backtrackedSubsets, int knapsackSize){
	vector<vector<int>> feasiblePowerSubsets;
	for(int i = 0; i < backtrackedSubsets.size(); i++){
		int sumOfWeights = 0;
		for(int j = 0; j < backtrackedSubsets[i].size(); j++){
			sumOfWeights += itemWeightVector[backtrackedSubsets[i][j]];
		}	
		if(sumOfWeights > knapsackSize){
			continue;
		}
		feasiblePowerSubsets.push_back(backtrackedSubsets[i]);
	}
	return feasiblePowerSubsets;
}

vector<int> valueOfSubsets(vector<int> itemValueVector, vector<vector<int>> feasiblePowerSubsets){
	int bestValue = -1;
	vector<int> bestSubset;
	for(int i = 0; i < feasiblePowerSubsets.size(); i++){
		int sumOfValues = 0;
		for(int j = 0; j < feasiblePowerSubsets[i].size(); j++){
			sumOfValues += itemValueVector[feasiblePowerSubsets[i][j]];
		}	
		if(sumOfValues > bestValue){
			bestValue = sumOfValues;
			bestSubset = feasiblePowerSubsets[i];
		}
	}
	return bestSubset;
}

vector<int> problemGenerator(int problemSizeInput, int knapsackSize, int maxItemValue, int maxItemWeight, vector<int>& itemValueVector, vector<int>& itemWeightVector){
	problemSize = problemSizeInput;
	itemValueVector = funcItemValueVectorCreator(maxItemValue);
	itemWeightVector = funcItemWeightVectorCreator(maxItemWeight);
	vector<vector<int>> backtrackedSubsets = funcBacktracking({}, 0);
	vector<vector<int>> feasiblePowerSubsets = feasibleSubsets(itemWeightVector, backtrackedSubsets, knapsackSize);
	vector<int> bestSubset = valueOfSubsets(itemValueVector, feasiblePowerSubsets);
	return bestSubset;
}

// MAIN FUNCTION

int main(){
	cout << "Enter the max problem size for the iterations: ";
	int maxProblemSizeInput;
	cin >> maxProblemSizeInput;
	cout << endl;
	if(maxProblemSizeInput < 4){
		cout << "Problem Size invalid." << endl;
		return -1;
	}
	srand(time(0));
	vector<double> executionTimeVector;
	int maxProblemSize = maxProblemSizeInput;
	for(int i = 4; i <= maxProblemSize + 1; i++){
		powerSet.clear();
		vector<int> itemValueVector;
		vector<int> itemWeightVector;
		vector<int> bestSubset;
		auto start = chrono::high_resolution_clock::now();
		bestSubset = problemGenerator(i, 10, 20, 15, itemValueVector, itemWeightVector);
		auto end = chrono::high_resolution_clock::now();
		double elapsed = chrono::duration<double, milli>(end - start).count();
		executionTimeVector.push_back(elapsed);
	}
    cout << "-------------------------" << endl;
    cout << "| problemSize | time(ms) |" << endl;
    cout << "-------------------------" << endl;
    for(int i = 4; i < maxProblemSize + 1; i++){
        cout << "| " << setw(11) << i << " | " << setw(8) << fixed << setprecision(3) << executionTimeVector[i - 4] << " |" << endl;
    }
    cout << "-------------------------" << endl;
	return 0;
}
