#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
const int MOD = 998244353;
int64_t binPow (int64_t x, int64_t y) {
    int64_t ans = 1, res = x;
    while (y > 0) {
        if (y & 1) {
            ans *= res, ans %= MOD;
        }
        res *= res, res %= MOD;
        y /= 2;
    }
    return ans;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int64_t N, M;
    cin >> N >> M;
    cout << (binPow(N, M) * binPow(M, N - 1)) % MOD;
}
