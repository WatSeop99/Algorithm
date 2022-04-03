'''
# Alg 2.1 이분검색 알고리즘(재귀적 방법)
def bs(data, item, low, high):
    if low > high:
        return -1
    else:
        mid = int((low+high)/2)
        if item == data[mid]:
            return mid
        elif item < data[mid]:
            return bs(data, item, low, mid-1)
        else:
            return bs(data, item, mid+1, high)

data = [1, 3, 5, 6, 7, 9, 10, 14, 17, 19]
n = 10
location = bs(data, 17, 0, n-1)
print(location)
'''

'''
# Alg 2.1 이분검색 알고리즘(객체지향 방법)
class data:
    def __init__(self, data):
        self.dataList = data[:]
        self.length = len(self.dataList)

    def binsearch(self, item):
        location = -1
        low = 0
        high = self.length-1
        while low <= high and location == -1:
            mid = int((high+low)/2)
            if item == self.dataList[mid]:
                location = mid
            elif item < self.dataList[mid]:
                high = mid-1
            else:
                low = mid+1
        return location

sample = [1, 3, 5, 6, 7, 9, 10, 14, 17, 19]
bsData = data(sample)
item = 17
print(bsData.binsearch(item))
'''

'''
# Alg 2.1 이분검색 알고리즘(데이터 비교 횟수 반환)
def bs(data, item, low, high):
    if low > high:
        return 0
    else:
        location = -1
        count = 0
        while low <= high and location == -1:
            mid = int((low+high)/2)
            if item == data[mid]:
                location = mid
            elif item < data[mid]:
                high = mid-1
            else:
                low = mid+1
            count += 1
        return count

data = [1, 3, 5, 6, 7, 9, 10, 14, 17, 19]
n = 10
count = bs(data, 17, 0, n-1)
print(count)
'''

'''
# Alg 2.2, 2.3 합병정렬
def merge(h, m, U, V, S):
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

def mergeSort(n, S):
    if n > 1:
        h = int(n/2)
        m = n-h
        U = S[:h]
        V = S[h:n]
        mergeSort(h, U)
        mergeSort(m, V)
        merge(h, m, U, V, S)

s = [3, 5, 2, 9, 10, 14, 4, 8]
mergeSort(8, s)
print(s)
'''

'''
# Alg 2.2, 2.3 합병정렬(반복적 방법)
def merge(low, mid, high, S):
    U = [0 for i in range(high+1)]
    i = k = low
    j = mid+1
    while i <= mid and j <= high:
        if S[i] < S[j]:
            U[k] = S[i]
            i += 1
        else:
            U[k] = S[j]
            j += 1
        k += 1
    if i > mid:
        U[k:high+1] = S[j:high+1]
    else:
        U[k:high+1] = S[i:mid+1]
    S[low:high+1] = U[low:high+1]

# 기존의 top-down 방식의 합병정렬을 반복적으로 수행하기 위해서는
# bottom-up 방식으로 관점을 바꿔 각각의 원소들을 2^n개씩 정렬하고, 합치는 방향으로 전개함
def mergeSort(n, S):
    # m = 합병정렬되는 배열 원소 개수
    for m in range(1, n+1, 2):
        # i = 정렬되는 배열들의 초기 원소 인덱스
        # i = 0, 2, 4, 6, ... if m = 1
        # i = 0, 4, 8, 12, ... if m = 2
        # i = 0, 8, 16, ... if m = 4
        # ...
        for i in range(0, n+1, 2*m):
            low = i
            high = i+m-1 if i+m-1 < n else n
            mid = int((low+high)/2)
            merge(low, mid, high, S)

s = [3, 5, 2, 9, 10, 14, 4, 8]
mergeSort(7, s)
print(s)
'''

'''
# Alg 2.4, 2.5 합병정렬2
def merge2(S, low, mid, high):
    U = [0 for i in range(high+1)]
    i = k = low
    j = mid+1
    while i <= mid and j <= high:
        if S[i] < S[j]:
            U[k] = S[i]
            i += 1
        else:
            U[k] = S[j]
            j += 1
        k += 1
    if i > mid:
        U[k:high+1] = S[j:high+1]
    else:
        U[k:high+1] = S[i:mid+1]
    S[low:high+1] = U[low:high+1]

def mergeSort2(S, low, high):
    if low < high:
        mid = int((low+high)/2)
        mergeSort2(S, low, mid)
        mergeSort2(S, mid+1, high)
        merge2(S, low, mid, high)

s = [3, 5, 2, 9, 10, 14, 4, 8]
mergeSort2(s, 0, 7)
print(s)
'''