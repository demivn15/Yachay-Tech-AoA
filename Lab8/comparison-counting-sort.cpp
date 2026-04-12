#include <iostream>
#include <vector>

void comparisonCountingSort(int A[], int n){
    int count[n] ={0};
    int S[n];
    for(int i = 0; i < n - 1; i++){
        for(int j = i + 1; j < n; j++){
            if(A[i] < A[j]) count[j]++;
            else count[i]++;
        }
    }
    for(int i = 0; i < n; i++) S[count[i]] = A[i];
    for(int i = 0; i < n; i++) A[i] = S[i];
}

int main(){
    int data[] = {60, 35, 81, 98, 14, 47};
    std::cout << "Initial array: " << std::endl;
    for(int x : data) 
        std::cout << x << " ";
    std::cout << std::endl;
    int n = sizeof(data)/sizeof(data[0]);
    comparisonCountingSort(data, n);
    std::cout << "Sorted array: " << std::endl;
    for(int x : data) 
        std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
