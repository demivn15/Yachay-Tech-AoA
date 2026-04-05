#include <iostream>
#include <iomanip>
#include <chrono>
#include <fstream>
#include <vector>
using namespace std;

void gaussianElimination(double* systemMatrix, double* rightVector, int matrixSize){
    for(int k = 0; k < matrixSize; k++){
        if(systemMatrix[k * matrixSize + k] == 0){
            cout << "Warning: Zero pivot at row " << k << ". System may be singular." << endl;
            continue; 
        }
        for(int i = k + 1; i < matrixSize; i++){
            double factor = systemMatrix[i * matrixSize + k] / systemMatrix[k * matrixSize + k];
            rightVector[i] -= factor * rightVector[k];
            for(int j = k; j < matrixSize; j++){
                systemMatrix[i * matrixSize + j] -= factor * systemMatrix[k * matrixSize + j];
            }
        }
    }
}

double* backSubstitution(double* systemMatrix, double* rightVector, int matrixSize) {
    double* solutionVector = new double[matrixSize];
    for (int i = matrixSize - 1; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < matrixSize; j++) {
            sum += systemMatrix[i * matrixSize + j] * solutionVector[j];
        }
        if (systemMatrix[i * matrixSize + i] == 0) return nullptr;
        solutionVector[i] = (rightVector[i] - sum) / systemMatrix[i * matrixSize + i];
    }
    return solutionVector;
}

void printMatrix(string label, double* matrix, int n) {
    cout << "--- " << label << " ---" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(8) << fixed << setprecision(2) << matrix[i * n + j] << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void printVector(string label, double* vector, int n) {
    cout << label << ": [ ";
    for (int i = 0; i < n; i++) {
        cout << vector[i] << (i == n - 1 ? "" : ", ");
    }
    cout << " ]" << endl << endl;
}

int main() {
    vector<int> sizes = {100, 300, 500, 800, 1000, 1200, 1500, 1800, 2000};
    ofstream csvFile("backwards-subtitution-running-time.csv");
    for (int n : sizes) {
        double* A = new double[n * n];
        double* b = new double[n];
        for (int i = 0; i < n; i++) {
            b[i] = (double)(i + 1);
            for (int j = 0; j < n; j++) {
                if (i == j) A[i * n + j] = (double)n * 2; 
                else A[i * n + j] = 1.0;
            }
        }
        gaussianElimination(A, b, n);
        auto start = chrono::high_resolution_clock::now();
        double* x = backSubstitution(A, b, n);
        auto end = chrono::high_resolution_clock::now();
        chrono::duration<double> elapsed = end - start;
        csvFile << n << "," << elapsed.count() << endl;
        cout << "Size " << n << " | Back-Sub took: " << elapsed.count() << "s" << endl;
        delete[] A;
        delete[] b;
        delete[] x;
    }
    csvFile.close();
    return 0;
}
