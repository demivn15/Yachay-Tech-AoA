#include <iostream>
#include <vector>
#include <algorithm>

void distributionCountingSort(int A[], int n, int l, int u){
    int size = u - l + 1;
    std::vector<int> D(size, 0);
    std::vector<int> S(n);
    for(int i = 0; i < n; i++) D[A[i] - l]++;
    for(int j = 1; j < size; j++) D[j] += D[j - 1];
    for(int i = n - 1; i >= 0; i--){
        int j = A[i] - l;
        S[D[j] - 1] = A[i];
        D[j]--;
    }
    for(int i = 0; i < n; i++) A[i] = S[i];
}

int main(){
    std::cout << "Initial array: " << std::endl;
    int data[] ={13, 11, 12, 13, 12, 12};
    for(int x : data) std::cout << x << " ";
    std::cout << std::endl;
    distributionCountingSort(data, 6, 11, 13);
    std::cout << "Sorted array: " << std::endl;
    for(int x : data) std::cout << x << " ";
    std::cout << std::endl;
    return 0;
}
