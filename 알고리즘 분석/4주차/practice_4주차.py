import numpy as np

'''
# Alg 2.6, 2.7 빠른정렬
def partition(s, low, high):
    j, pivotitem = low, s[low]
    for i in range(low+1, high+1):
        if s[i] < pivotitem:
            j += 1
            s[i], s[j] = s[j], s[i]
    pivotpoint = j
    s[low], s[pivotpoint] = s[pivotpoint], s[low]
    return pivotpoint

def quickSort(s, low, high):
    if high > low:
        pivotpoint = partition(s, low, high)
        quickSort(s, low, pivotpoint-1)
        quickSort(s, pivotpoint+1, high)

s = [3, 5, 2, 9, 10, 14, 4, 8]
quickSort(s, 0, 7)
print(s)
'''

'''
# Alg 2.8 쉬트라센 알고리즘
def strassen(n, A, B):
    threshold = 2
    if n <= threshold:
        C = np.array(A) @ np.array(B)
    else:
        A11 = np.array([[A[rows][cols] for cols in range(int(n/2))] for rows in range(int(n/2))])
        A12 = np.array([[A[rows][cols] for cols in range(int(n/2), n)] for rows in range(int(n/2))])
        A21 = np.array([[A[rows][cols] for cols in range(int(n/2))] for rows in range(int(n/2), n)])
        A22 = np.array([[A[rows][cols] for cols in range(int(n/2), n)] for rows in range(int(n/2), n)])
        B11 = np.array([[B[rows][cols] for cols in range(int(n/2))] for rows in range(int(n/2))])
        B12 = np.array([[B[rows][cols] for cols in range(int(n/2), n)] for rows in range(int(n/2))])
        B21 = np.array([[B[rows][cols] for cols in range(int(n/2))] for rows in range(int(n/2), n)])
        B22 = np.array([[B[rows][cols] for cols in range(int(n/2), n)] for rows in range(int(n/2), n)])
        M1 = M2 = M3 = M4 = M5 = M6 = M7 = np.array([])
        M1 = strassen(int(n/2), (A11+A22), (B11+B22))
        M2 = strassen(int(n/2), (A21+A22), B11)
        M3 = strassen(int(n/2), A11, (B12-B22))
        M4 = strassen(int(n/2), A22, (B21-B11))
        M5 = strassen(int(n/2), (A11+A22), B22)
        M6 = strassen(int(n/2), (A21-A11), (B11+B12))
        M7 = strassen(int(n/2), (A12-A22), (B21+B22))
        C = np.vstack([np.hstack([M1+M4-M5+M7, M3+M5]), np.hstack([M2+M4, M1+M3-M2+M6])])
    return C

n = 4
A = [[1, 2, 0, 2], [3, 1, 0, 0], [0, 1, 1, 2], [2, 0, 2, 0]]
B = [[0, 3, 0, 2], [1, 1, 4, 0], [1, 1, 0, 2], [0, 5, 2, 0]]
C = np.array(A) @ np.array(B)
D = [[0 for cols in range(n)] for rows in range(n)]
print(C)
D = strassen(n, A, B)
print(D)
# 보수 필요
'''

'''
# Alg 2.10 큰 정수 곱셈2
def prod2(a, b):
    n = len(str(a)) if len(str(a)) > len(str(b)) else len(str(b))
    if a == 0 or b == 0:
        return 0
    elif n <= 4:
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
'''