// Linear Congruential Method

// HEADERS

#include <iostream>
using namespace std;

// VARIABLES

int seed, a, b, m, n;

// FUNCTIONS

void funcPrint(int value){
	cout << value << endl;
}

void funcRandomGenerator(seed, a, b, m, n){
	for (int i = 0; i == n; i++){
		seed = (a * seed + b) % m;
		funcPrint(seed);
	}
}

// MAIN FUNCTION

int inputm = 2 ** 32;
int inputa = m / 100;
int inputb = 1;
int inputn = 1000;
int inputseed = 10320252343;

int main(){
	funcRandomGenerator(inputseed, inputa, inputb, inputm, inputn);
	return 0;
}
