import numpy as np
import matplotlib.pyplot as plt
import time

def radialKernel(r, epsilon = 1, c = 1, option = 0):
    if option == 0:
        # Gaussian Kernel
        return np.exp(-(epsilon * r) ** 2)
    elif option == 1:
        # Multiquadric kernel
        return (r ** 2 + c ** 2) ** 0.5
    elif option == 2:
        # Cubic kernel
        return r ** 3

def euclideanDistanceComputation(point_i, point_j):
    euclideanSum = 0
    dimension = len(point_i)
    for component in range(dimension):
        euclideanSum += (point_i[component] - point_j[component]) ** 2
    euclideanDistance = euclideanSum ** 0.5
    return euclideanDistance

def euclideanDistanceMatrixGenerator(setOfPoints):
    matrixSize = len(setOfPoints)
    euclideanDistanceMatrix = [[0.0 for _ in range(matrixSize)] for _ in range(matrixSize)]
    for i in range(matrixSize):
        for j in range(matrixSize):
            euclideanDistanceMatrix[i][j] = euclideanDistanceComputation(setOfPoints[i], setOfPoints[j])
    return euclideanDistanceMatrix

def radialKernelMatrixGenerator(euclideanDistanceMatrix, regularization = 1e-9):
    radialKernelMatrix = euclideanDistanceMatrix
    matrixSize = len(radialKernelMatrix)
    for i in range(matrixSize):
        for j in range(matrixSize):
            radialKernelMatrix[i][j] = radialKernel(euclideanDistanceMatrix[i][j])
            if i == j:
                radialKernelMatrix[i][j] += regularization
    return radialKernelMatrix

def RBFInterpolant(node, inputNodes, lambdaVector, epsilon = 1):
    estimation = 0
    for j in range(len(inputNodes)):
        euclideanDistance = euclideanDistanceComputation(node, inputNodes[j])
        estimation += lambdaVector[j] * radialKernel(euclideanDistance, epsilon = epsilon)
    return estimation

def gaussianEliminationPivot(A_matrix, f_vector):
    n = len(f_vector)
    M = [row[:] + [f_vector[i]] for i, row in enumerate(A_matrix)]
    for i in range(n):
        max_row = i
        for k in range(i + 1, n):
            if abs(M[k][i]) > abs(M[max_row][i]):
                max_row = k
        M[i], M[max_row] = M[max_row], M[i]
        pivot = M[i][i]
        if abs(pivot) < 1e-12:
            print("Matrix is near-singular. Ill-conditioning detected.")
        for k in range(i + 1, n):
            factor = M[k][i] / pivot
            for j in range(i, n + 1):
                M[k][j] -= factor * M[i][j]
    lambdas = [0 for _ in range(n)]
    for i in range(n - 1, -1, -1):
        sum_val = sum(M[i][j] * lambdas[j] for j in range(i + 1, n))
        lambdas[i] = (M[i][n] - sum_val) / M[i][i]
    return lambdas

def performanceAnalysis():
    problemSizes = [50, 100, 200, 400, 800]
    dimensions = [1, 2, 3]
    print("N | Dim | Gen Time (s) | Solve Time (s) | Total Time")
    print("-" * 50)
    for d in dimensions:
        for n in problemSizes:
            points = np.random.rand(n, d)
            values = np.random.rand(n)
            startGen = time.perf_counter()
            dist_m = euclideanDistanceMatrixGenerator(points)
            k_m = radialKernelMatrixGenerator(dist_m)
            endGen = time.perf_counter()
            startSolve = time.perf_counter()
            _ = gaussianEliminationPivot(k_m, values)
            endSolve = time.perf_counter()
            genT = endGen - startGen
            solveT = endSolve - startSolve
            print(f"{n} | {d} | {genT:.4f} | {solveT:.4f} | {genT + solveT:.4f}")
