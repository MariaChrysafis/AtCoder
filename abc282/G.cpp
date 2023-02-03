#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <queue>
#include <map>
#include <bitset>

using namespace std;
const int64_t MX = 102;
int64_t pre[102][102][102];
int64_t cur[102][102][102];
int64_t grid[102][102][102];
int query (int k, int x1, int y1, int x2, int y2, int MOD) {
    int64_t ans = 0;
    for (int a = x1; a <= x2; a++) {
        for (int b = y1; b <= y2; b++) {
            ans += pre[k][a][b];
            ans %= MOD;
        }
    }
    return ans;
}
void solve (int N, int K, int64_t MOD) {
    for (int k = 0; k < MX; k++) {
        for (int a = 0; a < MX; a++) {
            for (int b = 0; b < MX; b++) {
                pre[k][a][b] = (k == 0 && a < N && b < N);
                cur[k][a][b] = 0;
            }
        }
    }
    for (int n = 0; n < N - 1; n++) {
        for (int k = 0; k < N; k++) {
            for (int a = 0; a < MX; a++) {
                for (int b = 0; b < MX; b++) {
                    if (!b && !a) {
                        grid[k][a][b] = pre[k][0][0];
                    } else if (a && !b) {
                        grid[k][a][b] = grid[k][a - 1][b] + pre[k][a][b];
                    }  else if (b && !a) {
                        grid[k][a][b] = grid[k][a][b - 1] + pre[k][a][b];
                    } else {
                        grid[k][a][b] = grid[k][a - 1][b] + grid[k][a][b - 1] - grid[k][a - 1][b - 1] + pre[k][a][b];
                    }
                    grid[k][a][b] %= MOD;
                }
            }
        }
        for (int k = 0; k <= n; k++) {
            for (int a2 = 0; a2 < N - n - 1; a2++) {
                for (int b2 = 0; b2 < N - n - 1; b2++) {
                    if (k + 1 < N) {
                        cur[k + 1][a2][b2] += grid[k][a2][b2];
                        cur[k + 1][a2][b2] += grid[k][MX - 1][MX - 1] + grid[k][a2][b2];
                        cur[k + 1][a2][b2] -= grid[k][a2][MX - 1] + grid[k][MX - 1][b2];
                        cur[k + 1][a2][b2] += 3 * MOD;
                        cur[k + 1][a2][b2] %= MOD;
                    }
                    cur[k][a2][b2] += (grid[k][MX - 1][b2] - grid[k][a2][b2] + MOD) % MOD;
                    cur[k][a2][b2] += (grid[k][a2][MX - 1] - grid[k][a2][b2] + MOD) % MOD;
                    cur[k][a2][b2] %= MOD;
                }
            }
        }
        for (int k = 0; k < N; k++) {
            for (int a = 0; a < N; a++) {
                for (int b = 0; b < N; b++) {
                    pre[k][a][b] = cur[k][a][b];
                    cur[k][a][b] = 0;
                }
            }
        }
    }
    cout << pre[K][0][0];

}
int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int64_t N, K, MOD;
    cin >> N >> K >> MOD;
    solve(N, K, MOD);
}
