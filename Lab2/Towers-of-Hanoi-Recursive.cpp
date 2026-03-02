// Towers-of-Hanoi
// Recursive implementation

// HEADERS

#include <iostream>
using namespace std;

// VARIABLES

int inputNumberOfDisks, inputStartingRod, inputDestinationRod;

// FUNCTIONS

void funcPrintMovements(int currentRod, int objectiveRod){
	cout << currentRod << " -> " << objectiveRod << endl;
}

int funcTowersOfHanoi(int numberOfDisks, int startingRod, int destinationRod){
	if ((numberOfDisks < 1) || (startingRod < 1 || startingRod > 3) || (destinationRod < 1 || destinationRod > 3) || (startingRod == destinationRod)){
		return -1;
	} else {
		if (numberOfDisks == 1){
			funcPrintMovements(startingRod, destinationRod);
		} else {
			int supportingRod = 6 - (startingRod + destinationRod);
			funcTowersOfHanoi(numberOfDisks - 1, startingRod, supportingRod);
			funcPrintMovements(startingRod, destinationRod);
			funcTowersOfHanoi(numberOfDisks - 1, supportingRod, destinationRod);
		}
		}
	return 0;
	}

// MAIN FUNCTION

int main(void){
	cout << "Enter the number of disks: ";
	cin >> inputNumberOfDisks;
	cout << "Enter the starting rod (1, 2 or 3): ";
	cin >> inputStartingRod;
	cout << "Enter the destination rod (1, 2 or 3): ";
	cin >> inputDestinationRod;
	funcTowersOfHanoi(inputNumberOfDisks, inputStartingRod, inputDestinationRod); 
	return 0;
}
