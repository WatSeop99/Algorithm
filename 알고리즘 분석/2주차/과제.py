import time, random

global arr, arr1, arr2

# insertion sorting algorithm
def insertionSort(size):
    for i in range(1, size):
        x = arr1[i]
        j = i-1
        while j >= 0 and arr1[j] > x:
            arr1[j+1] = arr1[j]
            j -= 1
        arr1[j+1] = x

# quick sorting algorithm
def partition(low, high):
    pivotItem = arr2[low]
    j = low
    for i in range(low+1, high+1):
        if arr2[i] <= pivotItem:
            j += 1
            arr2[i], arr2[j] = arr2[j], arr2[i]
    pivot = j
    arr2[low], arr2[pivot] = arr2[pivot], arr2[low]
    return pivot

def quickSort(low, high):
    if high > low:
        pivot = partition(low, high)
        quickSort(low, pivot-1)
        quickSort(pivot+1, high)

# n = 5000일 때(n = 10000일 때)
n = 5000 # n = 10000
arr = []
for i in range(n):
    num = random.randint(1, n)
    while num in arr:
        num = random.randint(1, n)
    arr.append(num)
arr1 = list(arr) # array for insertion sort
arr2 = list(arr) # array for quick sort
# insertion sort
stime = time.time()
insertionSort(len(arr1))
etime = time.time()
print('insertion sort : {0:.5f}'.format(etime-stime))
# quick sort
stime = time.time()
quickSort(0, len(arr2)-1)
etime = time.time()
print('quick sort : {0:.5f}'.format(etime-stime))