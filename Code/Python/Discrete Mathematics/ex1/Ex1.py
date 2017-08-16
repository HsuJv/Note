def outd(l):
    o = "(" + l[0] + ")"
    for i in l[1:]:
        o += "|(" + i + ")"
    return o


def outc(l):
    o = "(" + l[0] + ")"
    for i in l[1:]:
        o += "&(" + i + ")"
    return o


def calc(expr, vv):
    """to calc the value of the expression
       expr represents the string of the expression from left to right
       vv represents the value of the variables"""

    case = {
        "!": lambda x: not x,
        "&": lambda x, y: x & y,
        "|": lambda x, y: x | y,
        "->": lambda x, y: (not x) | y,
        "<>": lambda x, y: x == y,
    }
    var = []
    opr = []
    pre = 0

    for i in range(len(expr)):
        if expr[i].isalpha():
            if i > 0 and expr[i-1] == '!':
                var.append(case['!'](vv[expr[i]]))
            else:
                var.append(vv[expr[i]])
            if pre == i or pre == i-1:
                pre = i
            else:
                opr.append(expr[pre+1:i])
                pre = i
    for i in range(len(opr)):
        if opr[i][-1] == '!':
            opr[i] = opr[i][:-1]
    ans = var[0]
    for i in range(len(opr)):
        ans = case[opr[i]](ans, var[i+1])
    return ans


def main():
    expr = input()
    var = []
    for i in expr:
        if i.isalpha():
            if i not in var:
                var.append(i)

    for i in var:
        print(i, end='\t')
    print(expr)

    expr = list(expr)
    for i in range(len(expr)-1, -1, -2):
        if expr[i] == '!':
            if expr[i] == expr[i-1] and expr[i-1] == expr[i-2]:
                del expr[i-1]
                del expr[i-1]
            elif expr[i+1] == expr[i] and expr[i] == expr[i-1]:
                del expr[i+1], expr[i]
    expr = ''.join(i for i in expr)

    cou = len(var)  # the count of the variable
    conj = []  # & F T->F
    disj = []  # | T F->T
    for i in range(1 << cou):
        vv = {}  # the value of the variable
        for j in range(cou, 0, -1):
            if i & (1 << (j-1)):
                print("T", end='\t')
                vv[var[cou-j]] = 1
            else:
                print("F", end='\t')
                vv[var[cou-j]] = 0
        if calc(expr, vv):
            print("T")
            temp = []
            for i in var:
                if vv[i]:
                    temp.append(i)
                else:
                    temp.append("!"+i)
            disj.append('&'.join(temp))
        else:
            print("F")
            temp = []
            for i in var:
                if not vv[i]:
                    temp.append(i)
                else:
                    temp.append("!"+i)
            conj.append('|'.join(temp))

    print("disj:", outd(disj))
    print("conj:", outc(conj))

if __name__ == '__main__':
    main()
