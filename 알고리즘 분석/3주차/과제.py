import random
import math

## Problem 1 ##
class data:
    def __init__(self, n):
        self.dataList = []
        # create random element and append it.
        for i in range(n):
            num = random.randint(1, n)
            self.dataList.append(num)
        self.dataList.sort()
        self.length = len(self.dataList) # length of array.
    
    # return comparison counting no.
    def bs(self, item, low, high):
        if low > high:
            return 0
        else:
            location = -1
            count = 0
            while low <= high and location == -1:
                mid = int((low+high)/2)
                if item == self.dataList[mid]:
                    location = mid
                elif item < self.dataList[mid]:
                    high = mid-1
                else:
                    low = mid+1
                count += 1
            return count

# intial setting
n = 128 # n = 256, 512
bsData = data(n)
# count and caculate avg comparison.
countSum = 0
for i in range(1000):
    x = random.randint(1, n)
    countSum += bsData.bs(x, 0, bsData.length-1)
print("Average : {}".format(countSum/1000))


## Problem 2 ##
class dataSort:
    def __init__(self, data):
        self.S = data[:]
        self.depth = 0 # 분할 시 깊이(lg(arr))
        self.alloSpace = 0 # 할당된 공간

    def merge(self, h, m, U, V, S):
        i = j = k = 0
        while i < h and j < m:
            if U[i] < V[j]:
                S[k] = U[i]
                i += 1
            else:
                S[k] = V[j]
                j += 1
            k += 1
        if i >= h:
            S[k:h+m] = V[j:m]
        else:
            S[k:h+m] = U[i:h]

    def mergeSort(self, n, S):
        if n > 1:
            h = int(n/2)
            m = n-h
            U, V = S[:h], S[h:n]
            self.mergeSort(h, U)
            self.mergeSort(m, V)
            self.merge(h, m, U, V, S)
            # 분할된 배열들을 병합하면서 추가적인 공간을 사용함.
            # 이때, 추가 공간은 현재 재귀 깊이에서 처음 할당된 공간만을 사용함.
            if self.depth < int(math.log(n, 2)):
                self.depth += 1
                self.alloSpace += len(U)+len(V)

    def sort(self):
        n = len(self.S)
        self.mergeSort(n, self.S)

# initial setting
s = [8, 3, 15, 2, 9, 1, 5, 7, 4, 16, 10, 11, 12, 13, 6, 14]
sortList = dataSort(s)
# sorting
sortList.sort()
print("Allocated space: {0}".format(sortList.alloSpace))
print(sortList.S)