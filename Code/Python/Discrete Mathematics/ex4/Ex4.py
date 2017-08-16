#!usr/bin/env python3
# coding=utf-8
import random


def validInput(a):
    if (not a.isdigit() or int(a) == 0):
        print(a, "不是一个正整数！")
        return False
    return True


def getRandomGraph(n):
    g = [([0] * n) for i in range(n)]
    for i in range(5):
        edg = random.randint(0, n * (n-1) / 2)
    i = 0
    while i < edg:
        a = random.randint(0, n - 1)
        b = random.randint(0, n - 1)
        if g[a][b] or a == b:
            continue
        else:
            g[a][b] = 1
            g[b][a] = 1
            i += 1
    return g


class graph(object):

    """docstring for graph"""

    def __init__(self, G):
        super(graph, self).__init__()
        self.g = G
        self.odd = 0
        self.deg = [0] * len(self.g)
        for i in range(len(self.g)):
            for j in range(len(self.g)):
                if self.g[i][j]:
                    self.deg[i] += 1

    def showGraph(self):
        for i in self.g:
            print(i)

    def isConnected(self, x=0, visit=[]):
        visit.append(x)
        for i in range(len(self.g)):
            if not i in visit and self.g[x][i]:
                self.isConnected(i, visit)
        if len(visit) == len(self.g):
            return True
        else:
            return False

    def isEulerianGraph(self):
        k = 0
        for i in self.deg:
            if i % 2:
                k += 1
        if not k:
            return True
        else:
            return False

    def isSemiEulerianGraph(self):
        k = 0
        for i in self.deg:
            if i % 2:
                k += 1
                self.odd = self.deg.index(i)
        if k == 2:
            return True
        else:
            return False

    def getEulerianPath(self):
        self.p = []
        ret = []
        self.p.append(self.odd)
        while len(self.p):
            brige = 1
            for i in range(len(self.g)):
                if self.g[self.p[-1]][i]:
                    brige = 0
                    break
            if brige:
                ret.append(self.p.pop())
            else:
                self.dfs(self.p[-1])
        return ret[:-1]

    def dfs(self, x):
        self.p.append(x)
        for i in range(len(self.g)):
            if self.g[x][i]:
                self.g[x][i] = 0
                self.g[i][x] = 0
                self.dfs(i)
                break


def main():
    while 1:
        n = input("请输入一个正整数：")
        if (validInput(n)):
            n = int(n)
            break
    G = getRandomGraph(n)
    g = graph(G)
    print("随机生成的图的邻接矩阵为：")
    g.showGraph()
    if not g.isConnected():
        print("该图不是连通图。")
    elif g.isEulerianGraph():
        print("该图是欧拉图，其中一条欧拉回路为：", g.getEulerianPath())
    elif g.isSemiEulerianGraph():
        print("该图是半欧拉图，其中一条欧拉路为：", g.getEulerianPath())
    else:
        print("该图既不是欧拉图也不是半欧拉图")


if __name__ == '__main__':
    main()
