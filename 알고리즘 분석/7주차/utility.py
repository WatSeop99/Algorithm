def printMatrix(d):
    m = len(d)
    n = len(d[0])
    for i in range(m):
        for j in range(n):
            print(f'{d[i][j]:4d}', end=" ")
        print()


def printMatrixF(d):
    n = len(d[0])
    for i in range(n):
        for j in range(n):
            print(f'{d[i][j]:5.2f}', end=" ")
        print()


def print_inOrder(root):
    if not root:
        return
    print_inOrder(root.l_child)
    print(root.data)
    print_inOrder(root.r_child)


def print_preOrder(root):
    if not root:
        return
    print(root.data)
    print_preOrder(root.l_child)
    print_preOrder(root.r_child)


def print_postOrder(root):
    if not root:
        return
    print_postOrder(root.l_child)
    print_postOrder(root.r_child)
    print(root.data)
