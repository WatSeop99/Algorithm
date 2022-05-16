import utility

'''
# Alg 3.9, 3.10 최적이진검색트리 구축 알고리즘
class Node:
    def __init__(self, data):
        self.l_child = None
        self.r_child = None
        self.data = data

def tree(key, r, i, j):
    k = r[i][j]
    if k == 0:
        return
    else:
        p = Node(key[k])
        p.l_child = tree(key, r, i, k-1)
        p.r_child = tree(key, r, k+1, j)
        return p

def optSearchTree(n, p, a, r):
    INF = 987654321
    for i in range(1, n+1):
        a[i][i-1] = 0
        a[i][i] = p[i]
        r[i][i] = i
        r[i][i-1] = 0
    a[n+1][n] = 0
    r[n+1][n] = 0
    for diagonal in range(1, n):
        for i in range(1, n-diagonal+1):
            j = i+diagonal
            a[i][j] = INF
            for k in range(i, j+1):
                comp = a[i][k-1]+a[k+1][j]+sum(p[i:j+1])
                if a[i][j] > comp:
                    a[i][j] = comp
                    r[i][j] = k

key = [' ', 'A', 'B', 'C', 'D']
p = [0, 0.375, 0.375, 0.125, 0.125]
n = len(p)-1

a = [[0 for j in range(n+2)] for i in range(n+2)]
r = [[0 for j in range(n+2)] for i in range(n+2)]

optSearchTree(n, p, a, r)
utility.printMatrixF(a)
print()
utility.printMatrix(r)
root = tree(key, r, 1, n)
utility.print_inOrder(root)
print()
utility.print_preOrder(root)
'''

'''
# Alg 3.12 DNA 서열 맞춤 알고리즘
a = ['A', 'A', 'C', 'A', 'G', 'T', 'T', 'A', 'C', 'C']
b = ['T', 'A', 'A', 'G', 'G', 'T', 'C', 'A']
m, n = len(a), len(b)
table = [[0 for j in range(n+1)] for i in range(m+1)]
minindex = [[(0, 0) for j in range(n+1)] for i in range(m+1)]

for j in range(n-1, -1, -1):
    table[m][j] = table[m][j+1]+2
for i in range(m-1, -1, -1):
    table[i][n] = table[i+1][n]+2

for i in range(m-1, -1, -1):
    for j in range(n-1, -1, -1):
        penalty = 0 if a[i] == b[j] else 1
        table[i][j] = min(table[i+1][j+1]+penalty, min(table[i+1][j]+2, table[i][j+1]+2))
        if table[i][j] == table[i+1][j+1]+penalty:
            minindex[i][j] = (i+1, j+1)
        elif table[i][j] == table[i+1][j]+2:
            minindex[i][j] = (i+1, j)
        else:
            minindex[i][j] = (i, j+1)        

utility.printMatrix(table)
x, y = 0, 0
while x < m and y < n:
    tx, ty = x, y
    print(minindex[x][y])
    (x, y) = minindex[x][y]
    if x == tx+1 and y == ty+1:
        print(a[tx], ' ', b[ty])
    elif x == tx and y == ty+1:
        print(" - ", ' ', b[ty])
    else:
        print(a[tx], ' ', " -")
'''