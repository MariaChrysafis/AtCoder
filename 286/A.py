N, P, Q, R, S = map(int, input().split())
arr = list(map(int, input().split()))
for i in range(P - 1, Q) :
    arr[i], arr[i + R - P] = arr[i + R - P], arr[i]
print(' '.join(map(str, arr)))
