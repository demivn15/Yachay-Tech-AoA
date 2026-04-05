import matplotlib.pyplot as plt
import numpy as np
import csv

dataArray = []
sizeArray = []
timeArray = []

try:
    with open("backwards-subtitution-running-time.csv", mode="r") as file:
        csvFile = csv.reader(file)
        for line in csvFile:
            dataArray.append(line)
except FileNotFoundError:
    print("Error: 'backwards-subtitution-running-time.csv' not found.")

def backwardsSubstitutionRunningTime(n): 
    return n ** 2  

for measure in dataArray:
    sizeArray.append(measure[0])
    timeArray.append(measure[1])

sizeArray_int = [int(item) for item in sizeArray]
timeArray_float = [float(item) for item in timeArray]

timeTheoretical = [backwardsSubstitutionRunningTime(n) for n in sizeArray_int]

print("Matrix Sizes:", sizeArray_int)
print("Empirical Times:", timeArray_float)

plt.figure(figsize=(10, 5))
plt.plot(sizeArray_int, timeTheoretical, color="orange", label="Theoretical Complexity $O(n^2)$")
plt.ylabel("Operations")
plt.xlabel("Matrix Size (n)")
plt.title("Theoretical Running Time")
plt.legend()
plt.savefig("backwards-substitution-theoretical.png")
plt.clf()

plt.plot(sizeArray_int, timeArray_float, "r-o", label="Empirical Execution Time")
plt.ylabel("Time (s)")
plt.xscale("log")
plt.yscale("log")
plt.xlabel("Matrix Size (n)")
plt.title("Measured Execution Time")
plt.legend()
plt.savefig("backwards-substitution-empirical.png")
