import utility


def order(p, i, j):
    if i == j:
        print("A{0}".format(i), end="")
    else:
        k = p[i][j]
        print("(", end="")
        order(p, i, k)
        order(p, k+1, j)
        print(")", end="")


# initial setting.
INF = 987654321
d = [3, 5, 4, 6, 7, 2, 3, 4]
n = len(d)-1
m = [[0 for j in range(1, n+2)] for i in range(1, n+2)]
p = [[0 for j in range(1, n+2)] for i in range(1, n+2)]


for diagonal in range(n):  # 행렬 크기만큼 반복.
    for i in range(1, n-diagonal+1):
        j = i+diagonal
        if i == j:  # 같은 행렬의 곱셈은 계산에 들어가지 않음.
            continue
        m[i][j] = INF
        for k in range(i, j):
            comp = m[i][k]+m[k+1][j]+d[i-1]*d[k]*d[j]
            if m[i][j] > comp:
                m[i][j] = comp
                p[i][j] = k

# utility 모듈은 실습자료에 있는 코드를 그대로 사용함.
utility.printMatrix(m)
print()
utility.printMatrix(p)
order(p, 1, 6)
