import utility

## Problem 1 ##


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


# initial setting for data1, data2.
keyData1 = [' ', 'A', 'B', 'C', 'D', 'E']
keyData2 = [' ', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H']
pData1 = [0]
for i in range(1, 6):
    pData1.append(round(i/15, 3))
pData2 = [0]
for i in range(8):
    pData2.append(round(1/8, 3))
n1 = len(pData1)-1
n2 = len(pData2)-1
a1 = [[0 for j in range(n1+2)] for i in range(n1+2)]
r1 = [[0 for j in range(n1+2)] for i in range(n1+2)]
a2 = [[0 for j in range(n2+2)] for i in range(n2+2)]
r2 = [[0 for j in range(n2+2)] for i in range(n2+2)]

# process data.
optSearchTree(n1, pData1, a1, r1)
optSearchTree(n2, pData2, a2, r2)

# print result for data1.
print("<< data1 >>")
utility.printMatrixF(a1)
print()
utility.printMatrix(r1)
root1 = tree(keyData1, r1, 1, n1)
utility.print_inOrder(root1)
print()
utility.print_preOrder(root1)
print()
# print result for data2.
print("<< data2 >>")
utility.printMatrixF(a2)
print()
utility.printMatrix(r2)
root2 = tree(keyData2, r2, 1, n2)
utility.print_inOrder(root2)
print()
utility.print_preOrder(root2)

## Problem 2 ##
# initial setting for data.
a = ['G', 'A', 'C', 'T', 'T', 'A', 'C', 'C']
b = ['C', 'A', 'C', 'G', 'T', 'C', 'C', 'A', 'C', 'C']
m, n = len(a), len(b)
table = [[0 for j in range(n+1)] for i in range(m+1)]
minindex = [[(0, 0) for j in range(n+1)] for i in range(m+1)]
for j in range(n-1, -1, -1):
    table[m][j] = table[m][j+1]+2
for i in range(m-1, -1, -1):
    table[i][n] = table[i+1][n]+2

# fill table and minindex.
for i in range(m-1, -1, -1):
    for j in range(n-1, -1, -1):
        penalty = 0 if a[i] == b[j] else 1
        table[i][j] = min(table[i+1][j+1]+penalty,
                          min(table[i+1][j]+2, table[i][j+1]+2))
        if table[i][j] == table[i+1][j+1]+penalty:
            minindex[i][j] = (i+1, j+1)
        elif table[i][j] == table[i+1][j]+2:
            minindex[i][j] = (i+1, j)
        else:
            minindex[i][j] = (i, j+1)

# print table and minindex.
print()
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
