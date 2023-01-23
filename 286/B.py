n = int(input())
s = input()
res = []
for c in s :
    res.append(c)
    if len(res) >= 2 and res[-1] == 'a' and res[-2] == 'n' :
        res.pop()
        res.append('y')
        res.append('a')
print("".join(res))
