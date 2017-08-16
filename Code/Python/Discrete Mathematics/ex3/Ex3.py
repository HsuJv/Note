#!usr/bin/env python3
# coding=utf-8


def gcd(a, b):
    if (b == 0):
        return a
    return gcd(b, a % b)


def validInput(a):
    if (not a.isdigit() or int(a) == 0):
        print(a, "不是一个自然数！")
        return False
    return True


def main():
    while 1:
        n = input("请输入一个自然数：")
        if (validInput(n)):
            n = int(n)
            break
    a = []
    b = []
    for i in range(1, n + 1):
        if (n % i == 0):
            a.append(i)
    print("由{0}的整除关系构成的格的盖住为：".format(n))
    for i in a:
        for j in a:
            if (not i == j and j % i == 0):
                b.append([i, j])
    for i in b:
        u, v = i
        for j in a:
            if (j > v and j % v == 0 and [u, j] in b):
                del b[b.index([u, j])]
    for i in b:
        u, v = i
        print("<{0}, {1}>".format(u, v))

    for i in a:
        if (not gcd(i, n/i) == 1):
            break
    else:
        print("该偏序关系构成的格是一个有补格")
        n = 0
    if (n):
        print("该偏序关系构成的格不是一个有补格")

if __name__ == '__main__':
    main()
