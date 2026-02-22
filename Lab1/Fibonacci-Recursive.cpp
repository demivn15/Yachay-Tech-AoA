// Lab1-Exercise2
// Write a C++ program that generates the sequence using iteration.

// 0 1 1 2 3 5 8 13 ...

// HEADERS

#include <iostream>
using namespace std;

// VARIABLES

int prevNumber = 0;
int currentNumber = 1;
int sumOfNumbers = 0;
int i, result, input;

// FUNCTIONS

int fibonacciIterative(int n){  // The sequence starts from n = 0.
	if (n < 0){
		result = -1;
	}

	else if (n <= 1){
		result = n;
	}

	else{
		for (i = 2; i <= n; i++){  // From i = 2 since the first two numbers from the sequence have been already considered.
			sumOfNumbers = prevNumber + currentNumber;
			prevNumber = currentNumber;
			currentNumber = sumOfNumbers;
			result = currentNumber;
		}
	}

	return result;
}

// MAIN FUNCTION

int main(){
	cout << "Enter the number of iterations to produce the Fibonacci value: ";
	cin >> input;
	cout << "The " << input << " value of the sequence is " << fibonacciIterative(input) << endl;
	return 0;
}
