#Patrick Catalin Alexandru Sava

t = int(input())
for i in range(t):
    n, x = input().split()
    n = int(n)
    x = int(x)
    string = input()
    if x == 1:
        if string[0] == '0':
            print("NO")
        else:
            print("YES")
        continue
    if x == 2:
        if sorted(string)[0] == sorted(string)[len(string) - 1] and string[0] == '0':
            print("NO")
        else:
            print("YES")
        continue
    ok = False
    for start in range(n):
        p = string[:start]
        if ok:
            break
        for finish in range(start + 1, n):
            if string[start] == '0':
                continue
            num = string[start:finish]
            rem = x - 1
            if p != '':
                rem -= 1
                aux = int(num)
                aux -= 1
                if aux == 0:
                    continue
                if not str(aux).endswith(p):
                    continue
            numPrime = p + num
            curNum = int(num)
            while rem > 1:
                curNum += 1
                numPrime += str(curNum)
                rem -= 1

            if string[:len(numPrime)] != numPrime:
                continue

            curNum += 1
            curNum = str(curNum)
            if string[len(numPrime):] != '' and curNum.startswith(string[len(numPrime):]):
                print("YES")
                ok = True
                break

    if not ok:
        print("NO")
