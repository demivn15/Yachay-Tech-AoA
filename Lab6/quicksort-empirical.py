import matplotlib.pyplot as plt
import numpy as np
import csv

dataArray = []
sizeArray = []
timeArray = []

with open("quicksort-empirical.csv", mode ="r")as file:
  csvFile = csv.reader(file)
  for line in csvFile:
      dataArray.append(line)

def quickSortComplexity(n): return n * np.log(n)

for measure in dataArray:
    sizeArray.append(measure[0])
    timeArray.append(measure[1])

sizeArray_int = [int(item) for item in sizeArray]
timeArray_float = [float(item) for item in timeArray]
timeTheoretical = quickSortComplexity(sizeArray_int)

print(sizeArray_int)
print(timeArray_float)

plt.plot(sizeArray_int, timeTheoretical, color = "orange", label = "Theoretical complexity")
plt.ylabel("O(n)")
plt.xlabel("n")
plt.legend()
plt.savefig("quicksort-empirical.png")
plt.clf()

plt.plot(sizeArray_int, timeArray_float, "r-o", label = "Empirical complexity")
plt.ylabel("Time (s)")
plt.xlabel("Array Size")
plt.legend()
plt.savefig("quicksort-empirical-2.png")

