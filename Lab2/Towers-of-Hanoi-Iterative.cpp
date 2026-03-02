// Towers-of-Hanoi
// Iterative implementation

// HEADERS

#include <iostream>
using namespace std;

// FUNCTIONS

void funcPrintMovements(int currentRod, int objectiveRod){
	cout << currentRod << " -> " << objectiveRod << endl;
}

void funcTowersOfHanoi(int numberOfDisks, int startingRod, int destinationRod){
	if ((numberOfDisks < 1) || (startingRod < 1 || startingRod > 3) || (destinationRod < 1 || destinationRod > 3) || (startingRod == destinationRod)){
		return -1;
	} else {
		if (numberOfDisks == 1){
			funcPrintMovements(startingRod, destinationRod);
		} else {

		}
	}
}

// MAIN FUNCTION

int main(void){
	return 0;
}
