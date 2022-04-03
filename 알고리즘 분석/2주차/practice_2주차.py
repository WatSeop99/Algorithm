'''
# Alg 1.1 순차검색 알고리즘
def seqsearch(s, x):
    location = 0
    while location < len(s) and s[location] != x:
        location += 1
    if location >= len(s):
        location = -1
    return location

s = [3, 5, 2, 1, 7, 9]
loc = seqsearch(s, 4)
print(loc)
'''

'''
# Alg 1.2 배열의 수 더하기
def sum1(s):
    result = 0
    for a in s:
        result += a
    return result

s = [3, 5, 2, 1, 7, 9]
answer = sum1(s)
print(answer)

def sum2(s):
    result = 0
    for i in range(len(s)):
        result += s[i]
    return result

s = [3, 5, 2, 1, 7, 9]
answer = (sum2(s))
print(answer)
'''

'''
# Alg 1.3 교환정렬
s = [3, 2, 5, 7, 1, 9, 4, 6, 8]
n = len(s)
for i in range(0, n-1):
    for j in range(i+1, n):
        if (s[j] < s[i]):
            s[i], s[j] = s[j], s[i]
print(s)
'''

'''
# Alg 1.4 행렬곱셈
def matrix_multiplication(a, b):
    c = [[0 for col in range(len(a))] for row in range(len(a))]
    for i in range(0, len(a)):
        for j in range(0, len(a)):
            for k in range(0, len(a)):
                c[i][j] += a[i][k]*b[k][j]
    return c

a = [[1, 2], [3, 4]]
b = [[4, 1], [1, 0]]
print(matrix_multiplication(a, b))
'''

'''
# Alg 1.5 이분검색 알고리즘
def bs(data, item, low, high):
    location = -1
    while low <= high and location == -1:
        mid = int((high+low)/2)
        if item == data[mid]:
            location = mid
        elif item < data[mid]:
            high = mid-1
        else:
            low = mid+1
    return location

data = [1, 3, 5, 6, 7, 9, 10, 14, 17, 19]
n = 10
location = bs(data, 17, 0, n-1)
print(location)
'''

'''
# Alg 1.6 피보나치 수 구하기(재귀적 방법)
def fib1(n):
    if n <= 1:
        return n
    return fib1(n-1)+fib1(n-2)

for i in range(0, 10):
    print(f'{i:2d} {fib1(i):6d}')
'''

'''
# Alg 1.7 피보나치 수 구하기(반복적 방법)
def fib2(n):
    if (n > 1):
        f = [0 for i in range(n+1)]
        f[1] = 1
        for i in range(2, n+1):
            f[i] = f[i-1]+f[i-2]
        return f[n]
    return n

for i in range(0, 10):
    print(f'{i:2d} {fib2(i):6d}')
'''

'''
import time

def fib1(n):
    if n <= 1:
        return n
    return fib1(n-1)+fib1(n-2)

def fib2(n):
    if (n > 1):
        f = [0 for i in range(n+1)]
        f[1] = 1
        for i in range(2, n+1):
            f[i] = f[i-1]+f[i-2]
        return f[n]
    return n

n = 50
print("fib1 time")
stime = time.time()
for i in range(n):
    fib1(i)
    etime = time.time()
    print(f'{i:2d}{etime-stime:10.5f} ')
print("fib2 time")
stime = time.time()
for i in range(n):
    fib2(i)
    etime = time.time()
    print(f'{i:2d}{etime-stime:10.5f} ')
'''