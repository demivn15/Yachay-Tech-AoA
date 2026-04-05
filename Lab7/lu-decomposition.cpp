#include <iostream>
#include <string>

using namespace std;

double* matrixInitialization(int n){
    double* matrix = new double[n * n];
    for (int index = 0; index < n * n; index++) matrix[index] = 0.0;
    return matrix;
}

void luDecomposition(double* A, double* L, double* U, int n){
    for (int i = 0; i < n; i++){
        for (int k = i; k < n; k++){
            double sum = 0;
            for (int j = 0; j < i; j++)
                sum += (L[i * n + j] * U[j * n + k]);
            U[i * n + k] = A[i * n + k] - sum;
        }

        for (int k = i; k < n; k++){
            if (i == k)
                L[i * n + i] = 1.0; 
            else{
                double sum = 0;
                for (int j = 0; j < i; j++)
                    sum += (L[k * n + j] * U[j * n + i]);
                if (U[i * n + i] == 0) return; 
                L[k * n + i] = (A[k * n + i] - sum) / U[i * n + i];
            }
        }
    }
}

double* forwardSubstitution(double* L, double* b, int n){
    double* y = new double[n];
    for (int i = 0; i < n; i++){
        double sum = 0;
        for (int j = 0; j < i; j++){
            sum += L[i * n + j] * y[j];
        }
        y[i] = (b[i] - sum) / L[i * n + i];
    }
    return y;
}

double* backwardSubstitution(double* U, double* y, int n){
    double* x = new double[n];
    for (int i = n - 1; i >= 0; i--){
        double sum = 0;
        for (int j = i + 1; j < n; j++){
            sum += U[i * n + j] * x[j];
        }
        if (U[i * n + i] == 0) return nullptr;
        x[i] = (y[i] - sum) / U[i * n + i];
    }
    return x;
}

int main(){
    int n = 3;
    double* A = new double[n * n]{
        2, 1, -1,
        -3, -1, 2,
        -2, 1, 2
    };
    double* b = new double[n]{8, -11, -3};
    double* L = matrixInitialization(n);
    double* U = matrixInitialization(n);
    luDecomposition(A, L, U, n);
    double* y = forwardSubstitution(L, b, n);
    double* x = backwardSubstitution(U, y, n);
    if (x != nullptr){
        cout << "Solution Vector x: ";
        for (int index = 0; index < n; index++) cout << x[index] << " ";
        cout << endl;
    }
    delete[] A; 
    delete[] b; 
    delete[] L; 
    delete[] U; 
    delete[] y; 
    delete[] x;
    return 0;
}
