#include <iostream>
#include <chrono>

#define MAX 100

int fibonacciSequence(int n){
    if (n == 0) return 0;
    else if (n == 1) return 1;
    else return fibonacciSequence(n - 1) + fibonacciSequence(n - 2);
}

int fibonacciSequenceDP(int n, int memo[]){
    int result;
    if (memo[n] != 0) return memo[n];
    if (n == 0) result = 0;
    else if (n == 1) result = 1;
    else result = fibonacciSequenceDP(n - 1, memo) + 
        fibonacciSequenceDP(n - 2, memo);
    memo[n] = result;
    return result;
}

int main(){
    int n;
    int memo[MAX] = {};
    std::cout << "Enter the value of n to calculate the fibonacci sequence: ";
    std::cin >> n;
    auto start = std::chrono::steady_clock::now();
    int result = fibonacciSequence(n);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> execTime = end - start;
    auto startDP = std::chrono::steady_clock::now();
    int resultDP = fibonacciSequenceDP(n, memo);
    auto endDP = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> execTimeDP = endDP - startDP;
    std::cout << "The fibonacci sequence in n = " << n << " is " << result 
        << " - Execution time: " << execTime.count() << "ms" << std::endl;
    std::cout << "The fibonacci sequence in n = " << n << " is " << resultDP 
        << " - Execution time: " << execTimeDP.count() << "ms" 
        << " (Dynamic Programming)" <<  std::endl;
    return 0;
}
