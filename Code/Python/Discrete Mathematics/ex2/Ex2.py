a = []  # 元素集合
r = []  # 关系


def init():
    global a, r
    A = input("输入关系的域中包含的元素，以空格隔开：")
    a = A.split()
    print("每行输入两个元素x y，表示关系xRy，以'#'终止")
    R = input()
    while('#' not in R):
        if (len(R.split()) != 2):
            print("输入元素个数不正确，请重输：")
            R = input()
            continue
        x, y = R.split()
        if (x not in a or y not in a):
            print("输入的元素不在集合A中，请重输：")
            R = input()
            continue
        r.append([x, y])
        R = input()


def isReflexive():
    global a, r
    for i in a:
        if ([i, i] not in r):
            return False
    return True


def isSymmetric():
    global a, r
    for i in a:
        for j in a:
            if ([i, j] in r and [j, i] not in r):
                return False
    return True


def isTransitive():
    for i in a:
        for j in a:
            for k in a:
                if ([i, j] in r and [j, k] in r and [i, k] not in r):
                    return False
    return True


def isIrreflexive():
    global a, r
    for i in a:
        if ([i, i] in r):
            return False
    return True


def isAntisymmetric():
    global a, r
    for i in a:
        for j in a:
            if ([i, j] in r and [j, i] in r and i != j):
                return False
    return True


def main():
    init()  # 初始化
    if (isReflexive()):  # 自反性
        print("该关系是自反的；")
    else:
        print("该关系不是自反的；")
    if(isSymmetric()):  # 对称性
        print("该关系是对称的；")
    else:
        print("该关系不是对称的；")
    if(isTransitive()):  # 传递性
        print("该关系是传递的；")
    else:
        print("该关系不是传递的；")
    if (isIrreflexive()):  # 反自反性
        print("该关系是反自反的；")
    else:
        print("该关系不是反自反的；")
    if(isAntisymmetric()):  # 反对称性
        print("该关系是反对称的。")
    else:
        print("该关系不是反对称的。")


if __name__ == '__main__':
    main()
