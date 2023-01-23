N, X = map(int, input().split())
arr = []
dp = [False] * (X + 1)
dp[0] = True
assert dp[0]
for i in range(0, N) :
    a, b = map(int, input().split())
    while b != 0 :
        b -= 1
        for j in range(X, -1, -1) :
            if j - a >= 0 and dp[j - a] :
                dp[j] = True
if dp[X] :
    print("Yes")
else :
    print("No")
# print(dp[X])
