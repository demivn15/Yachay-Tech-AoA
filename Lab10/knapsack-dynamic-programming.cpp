#include <iostream>
#include <vector>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <chrono>

int knapsackDP(int i, int w, const std::vector<int>& weights, const std::vector<int>& values, std::vector<std::vector<int>>& memo) {
    if (i < 0 || w == 0) {
        return 0;
    }
    if (memo[i][w] != -1) {
        return memo[i][w];
    }
    if (weights[i] > w) {
        memo[i][w] = knapsackDP(i - 1, w, weights, values, memo);
    } 
    else {
        memo[i][w] = std::max(
            knapsackDP(i - 1, w, weights, values, memo),
            values[i] + knapsackDP(i - 1, w - weights[i], weights, values, memo)
        );
    }
    return memo[i][w];
}

void printVector(std::vector<int> vector, int n) {
    std::cout << "[";
    for (int i = 0; i < n - 1; i++) {
        std::cout << vector[i] << " ";
    }
    std::cout << vector[n - 1];
    std::cout << "]";
    std::cout << std::endl;
}

int main() {
    srand(time(0));
    int n = 10;
    int capacity = 20;
    std::vector<int> values(n);
    std::vector<int> weights(n);
    for (int i = 0; i < n; i++) {
        values[i] = rand() % 20 + 1;
        weights[i] = rand() % 10 + 1;
    }
    std::vector<std::vector<int>> memo(n, std::vector<int>(capacity + 1, -1));
    auto start = std::chrono::steady_clock::now();
    int maxValue = knapsackDP(n - 1, capacity, weights, values, memo);
    auto end = std::chrono::steady_clock::now();
    std::chrono::duration<double, std::milli> execTime = end - start;
    std::cout << "Values: "; 
    printVector(values, n);
    std::cout << "Weights: "; 
    printVector(weights, n);
    std::cout << "Maximum value in Knapsack: " << maxValue << std::endl;
    std::cout << "Execution time: " << execTime.count() << "ms" << std::endl;
    return 0;
}
