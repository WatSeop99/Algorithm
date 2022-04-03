import random
import matplotlib.pyplot as plt

## Problem 1 ##
class sortData:
    def __init__(self, n):
        self.dataList = []
        self.compNum = 0
        for i in range(n):
            num = random.randint(0, n)
            self.dataList.append(num)

    def partition(self, low, high):
        j, pivotitem = low, self.dataList[low]
        for i in range(low+1, high+1):
            if self.dataList[i] < pivotitem:
                j += 1
                self.dataList[i], self.dataList[j] = self.dataList[j], self.dataList[i]
                self.compNum += 1
        pivotpoint = j
        self.dataList[low], self.dataList[pivotpoint] = self.dataList[pivotpoint], self.dataList[low]
        return pivotpoint

    def quickSort(self, low, high):
        if high > low:
            pivotpoint = self.partition(low, high)
            self.quickSort(low, pivotpoint-1)
            self.quickSort(pivotpoint+1, high)

# initial setting
settingN = [100, 200, 300, 400]
avgCompCount = []
# run 4 times.
for i in range(4): # n is in settingN.
    compCount = [] # comparison count number in quick sort.
    for j in range(100): # create 100 sets of data.
        sorting = sortData(settingN[i])
        sorting.quickSort(0, settingN[i]-1)
        compCount.append(sorting.compNum)
    avg = sum(compCount)/100
    print("n = {0}, Average: {1}".format(settingN[i], avg))
    avgCompCount.append(avg)
# graph using avgCompcount[].
# n이 각각 100, 200, 300, 400일 때, 각각 비교횟수의 평균값을 기준으로 그래프가 그려지게 됨.
# 100 ≤ n ≤ 400인 구간에서 그래프가 그려짐. 이때, 4개의 점들을 기준으로 이어진 선은 n이 연속적일 때의 평균 비교횟수의 추이를 나타냄.
# 이는 nlogn과 비슷한 형태인 것을 알 수 있음.
plt.plot(settingN, avgCompCount)
plt.show()

## Problem 2 ##
def prod2(a, b):
    n = len(str(a)) if len(str(a)) > len(str(b)) else len(str(b))
    if a == 0 or b == 0:
        return 0
    elif n <= 2: # threshold = 2
        return a*b
    else:
        m = int(n/2)
        x, y = int(a/pow(10, m)), a%pow(10, m)
        w, z = int(b/pow(10, m)), b%pow(10, m)
        r = prod2(x+y, w+z)
        p = prod2(x, w)
        q = prod2(y, z)
        return p*pow(10, 2*m)+(r-p-q)*pow(10, m)+q

a = 1234567812345678
b = 2345678923456789
print(prod2(a, b))
print(a*b)