import utility
import copy

'''
# Alg 3.1, 3.2 이항계수 구하기
def bin(n, k):
    if k == 0 or n == k:
        return 1
    else:
        return bin(n-1, k-1)+bin(n-1, k)

def bin2(n, k):
    b = [[0 for j in range(k+1)] for i in range(n+1)]
    for i in range(n+1):
        for j in range(min(i, k)+1):
            if j == 0 or j == i:
                b[i][j] = 1
            else:
                b[i][j] = b[i-1][j-1]+b[i-1][j]
    return b[n][k]

print(bin(10, 5), bin2(10, 5))
'''

'''
# Alg 3.3, 3.4, 3.5 floyd 알고리즘
def allShortestPath(g, n):
    p = [[0 for j in range(n)] for i in range(n)]
    d = copy.deepcopy(g)
    for k in range(n):
        for i in range(n):
            for j in range(n):
                if d[i][k]+d[k][j] < d[i][j]:
                    p[i][j] = k+1
                    d[i][j] = d[i][k]+d[k][j]
    return d, p

def path(p, q, r):
    q -= 1
    r -= 1
    if p[q][r] != 0:
        path(p, q+1, p[q][r])
        print("v{0}".format(p[q][r]), end = " ")
        path(p, p[q][r], r+1)

inf = 1000
g = [[0, 1, inf, 1, 5], [9, 0, 3, 2, inf], [inf, inf, 0, 4, inf], [inf, inf, 2, 0, 3], [3, inf, inf, inf, 0]]
d, p = allShortestPath(g, 5)
utility.printMatrix(g)
print()
utility.printMatrix(d)
print()
utility.printMatrix(p)
path(p, 5, 3)
'''

'''
# Alg 3.6, 3.7 연쇄행렬 최소곱셈 알고리즘
def order(p, i, j):
    i -= 1
    j -= 1
    if i == j:
        print("A{0}".format(i+1), end = "")
    else:
        k = p[i][j]+1
        print("(", end = "")
        order(p, i+1, k)
        order(p, k+1, j+1)
        print(")", end = "")

INF = 987654321
d = [5, 2, 3, 4, 6, 7, 8]
n = len(d)-1
m = [[0 for j in range(1, n+2)] for i in range(1, n+2)]
p = [[0 for j in range(1, n+2)] for i in range(1, n+2)]

for diagonal in range(n):
    for i in range(1, n-diagonal+1):
        j = i+diagonal
        if i == j:
            continue
        m[i][j] = INF
        for k in range(i, j):
            comp = m[i][k]+m[k+1][j]+d[i-1]*d[k]*d[j]
            if m[i][j] > comp:
                m[i][j] = comp
                p[i][j] = k

utility.printMatrix(m)
print()
utility.printMatrix(p)
order(p, 1, 6)
'''
