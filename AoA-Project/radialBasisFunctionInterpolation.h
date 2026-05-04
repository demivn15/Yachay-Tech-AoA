#ifndef RADIAL_BASIS_FUNCTION_INTERPOLATION_H
#define RADIAL_BASIS_FUNCTION_INTERPOLATION_H

#include <vector>
#include <cmath>
#include <iostream>
#include <iomanip>
#include <stdexcept>
#include <chrono>
#include <random>

// ─────────────────────────────────────────────────────────────
//  Type aliases for readability
// ─────────────────────────────────────────────────────────────
using Point  = std::vector<double>;
using Matrix = std::vector<std::vector<double>>;
using Vector = std::vector<double>;


// ─────────────────────────────────────────────────────────────
//  radialKernel
//  option 0 → Gaussian:     phi(r) = exp(-(epsilon * r)^2)
//  option 1 → Multiquadric: phi(r) = sqrt(r^2 + c^2)
//  option 2 → Cubic:        phi(r) = r^3
// ─────────────────────────────────────────────────────────────
inline double radialKernel(double r, double epsilon = 1.0, double c = 1.0, int option = 0)
{
    switch (option) {
        case 0:  return std::exp(-std::pow(epsilon * r, 2.0));   // Gaussian
        case 1:  return std::sqrt(r * r + c * c);                // Multiquadric
        case 2:  return r * r * r;                               // Cubic
        default: throw std::invalid_argument("Unknown kernel option. Use 0 (Gaussian), 1 (Multiquadric), or 2 (Cubic).");
    }
}


// ─────────────────────────────────────────────────────────────
//  euclideanDistanceComputation
//  Returns the Euclidean distance between two D-dimensional points.
// ─────────────────────────────────────────────────────────────
inline double euclideanDistanceComputation(const Point& point_i, const Point& point_j)
{
    if (point_i.size() != point_j.size())
        throw std::invalid_argument("Points must have the same dimensionality.");

    double euclideanSum = 0.0;
    for (size_t component = 0; component < point_i.size(); ++component) {
        double diff = point_i[component] - point_j[component];
        euclideanSum += diff * diff;
    }
    return std::sqrt(euclideanSum);
}


// ─────────────────────────────────────────────────────────────
//  euclideanDistanceMatrixGenerator
//  Builds the N x N pairwise distance matrix for a set of nodes.
// ─────────────────────────────────────────────────────────────
inline Matrix euclideanDistanceMatrixGenerator(const std::vector<Point>& setOfPoints)
{
    size_t matrixSize = setOfPoints.size();
    Matrix euclideanDistanceMatrix(matrixSize, Vector(matrixSize, 0.0));

    for (size_t i = 0; i < matrixSize; ++i)
        for (size_t j = 0; j < matrixSize; ++j)
            euclideanDistanceMatrix[i][j] = euclideanDistanceComputation(setOfPoints[i], setOfPoints[j]);

    return euclideanDistanceMatrix;
}


// ─────────────────────────────────────────────────────────────
//  radialKernelMatrixGenerator
//  Applies the radial kernel to every element of the distance
//  matrix and adds a small regularization term on the diagonal
//  to guard against near-singularity.
// ─────────────────────────────────────────────────────────────
inline Matrix radialKernelMatrixGenerator(const Matrix& euclideanDistanceMatrix,
                                          double regularization = 1e-9)
{
    size_t matrixSize = euclideanDistanceMatrix.size();
    Matrix radialKernelMatrix(matrixSize, Vector(matrixSize, 0.0));

    for (size_t i = 0; i < matrixSize; ++i) {
        for (size_t j = 0; j < matrixSize; ++j) {
            radialKernelMatrix[i][j] = radialKernel(euclideanDistanceMatrix[i][j]);
            if (i == j)
                radialKernelMatrix[i][j] += regularization;
        }
    }
    return radialKernelMatrix;
}


// ─────────────────────────────────────────────────────────────
//  gaussianEliminationPivot
//  Solves A * lambda = f via Gaussian Elimination with Partial
//  Pivoting. Returns the coefficient vector lambda.
// ─────────────────────────────────────────────────────────────
inline Vector gaussianEliminationPivot(const Matrix& A_matrix, const Vector& f_vector)
{
    size_t n = f_vector.size();

    // Build augmented matrix [A | f]
    Matrix M(n, Vector(n + 1));
    for (size_t i = 0; i < n; ++i) {
        for (size_t j = 0; j < n; ++j)
            M[i][j] = A_matrix[i][j];
        M[i][n] = f_vector[i];
    }

    // Forward elimination with partial pivoting
    for (size_t i = 0; i < n; ++i) {
        // Find pivot row
        size_t max_row = i;
        for (size_t k = i + 1; k < n; ++k)
            if (std::abs(M[k][i]) > std::abs(M[max_row][i]))
                max_row = k;

        std::swap(M[i], M[max_row]);

        double pivot = M[i][i];
        if (std::abs(pivot) < 1e-12)
            std::cerr << "Warning: Matrix is near-singular. Ill-conditioning detected.\n";

        // Eliminate below
        for (size_t k = i + 1; k < n; ++k) {
            double factor = M[k][i] / pivot;
            for (size_t j = i; j <= n; ++j)
                M[k][j] -= factor * M[i][j];
        }
    }

    // Back substitution
    Vector lambdas(n, 0.0);
    for (int i = static_cast<int>(n) - 1; i >= 0; --i) {
        double sum_val = 0.0;
        for (size_t j = static_cast<size_t>(i) + 1; j < n; ++j)
            sum_val += M[i][j] * lambdas[j];
        lambdas[i] = (M[i][n] - sum_val) / M[i][i];
    }

    return lambdas;
}


// ─────────────────────────────────────────────────────────────
//  RBFInterpolant
//  Evaluates the RBF interpolant s(x) at a new point `node`:
//      s(x) = sum_j  lambda_j * phi( ||x - x_j|| )
// ─────────────────────────────────────────────────────────────
inline double RBFInterpolant(const Point& node,
                              const std::vector<Point>& inputNodes,
                              const Vector& lambdaVector,
                              double epsilon = 1.0)
{
    double estimation = 0.0;
    for (size_t j = 0; j < inputNodes.size(); ++j) {
        double dist = euclideanDistanceComputation(node, inputNodes[j]);
        estimation += lambdaVector[j] * radialKernel(dist, epsilon);
    }
    return estimation;
}


// ─────────────────────────────────────────────────────────────
//  performanceAnalysis
//  Benchmarks matrix generation and solver times across
//  problem sizes N and spatial dimensions D, matching the
//  output format of the original Python version.
// ─────────────────────────────────────────────────────────────
inline void performanceAnalysis()
{
    std::vector<int> problemSizes = {50, 100, 200, 400, 800};
    std::vector<int> dimensions   = {1, 2, 3};

    // Random number generation
    std::mt19937 rng(42);
    std::uniform_real_distribution<double> dist(0.0, 1.0);

    std::cout << std::left
              << std::setw(6)  << "N"
              << std::setw(6)  << "Dim"
              << std::setw(16) << "Gen Time (s)"
              << std::setw(18) << "Solve Time (s)"
              << "Total Time (s)\n";
    std::cout << std::string(58, '-') << "\n";

    for (int d : dimensions) {
        for (int n : problemSizes) {
            // Generate random nodes and values
            std::vector<Point> points(n, Point(d));
            Vector values(n);
            for (int i = 0; i < n; ++i) {
                for (int k = 0; k < d; ++k)
                    points[i][k] = dist(rng);
                values[i] = dist(rng);
            }

            // Time matrix generation
            auto startGen = std::chrono::high_resolution_clock::now();
            Matrix distMatrix = euclideanDistanceMatrixGenerator(points);
            Matrix kernelMatrix = radialKernelMatrixGenerator(distMatrix);
            auto endGen = std::chrono::high_resolution_clock::now();

            // Time solver
            auto startSolve = std::chrono::high_resolution_clock::now();
            Vector lambdas = gaussianEliminationPivot(kernelMatrix, values);
            auto endSolve = std::chrono::high_resolution_clock::now();

            double genT   = std::chrono::duration<double>(endGen   - startGen).count();
            double solveT = std::chrono::duration<double>(endSolve - startSolve).count();

            std::cout << std::fixed << std::setprecision(4)
                      << std::left
                      << std::setw(6)  << n
                      << std::setw(6)  << d
                      << std::setw(16) << genT
                      << std::setw(18) << solveT
                      << (genT + solveT) << "\n";
        }
    }
}

#endif // RADIAL_BASIS_FUNCTION_INTERPOLATION_H
