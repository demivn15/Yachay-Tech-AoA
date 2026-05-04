import numpy as np
import matplotlib.pyplot as plt
import time
import radialBasisFunctionInterpolation as rbfi

def main():
    inputNodes = [[0.0], [1.5], [3.0], [4.5], [6.0]]
    functionDataValues = [0.0, 0.99, 0.14, -0.97, -0.28]
    testPoints = np.linspace(0.0, 6.0, 20)
    testPointsVector = [[point] for point in testPoints]
    euclideanDistanceMatrix = rbfi.euclideanDistanceMatrixGenerator(inputNodes)
    print(euclideanDistanceMatrix, "\n")
    radialKernelMatrix = rbfi.radialKernelMatrixGenerator(euclideanDistanceMatrix)
    print(radialKernelMatrix, "\n")
    lambdaVector = rbfi.gaussianEliminationPivot(radialKernelMatrix, functionDataValues)
    print(lambdaVector, "\n")
    results = []
    for point in testPointsVector:
        estimation = rbfi.RBFInterpolant(point,
                                    inputNodes,
                                    lambdaVector,
                                    epsilon = 1)
        results.append(estimation)
    print(results, "\n")
    plt.scatter(inputNodes, 
                functionDataValues,
                color='red', 
                label='Known Data Points (Nodes)',
                zorder=5)
    plt.plot(testPoints, results, color='blue', label='RBF Interpolant s(x)')
    plt.title("Radial Basis Function Interpolation (Mesh-Free)")
    plt.xlabel("Dimension x")
    plt.ylabel("Value f(x)")
    plt.legend()
    plt.grid(True)
    plt.show()
    rbfi.performanceAnalysis()

main()
