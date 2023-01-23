N, A, B = map(int, input().split())
s = input()
ans = []
c = 0
for i in range(0, N) :
    res = 0
    for j in range(0, N) :
        res += (s[(i + j) % N] != s[(i + N - j - 1) % N])
    ans.append(int(res/2) * B + c * A)
    c += 1
print(min(ans))
