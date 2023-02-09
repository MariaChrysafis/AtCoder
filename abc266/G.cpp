#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
const int MOD = 998244353;
int64_t mult (int64_t x, int64_t y) {
    return (x * y) % MOD;
}
int64_t add (int64_t x, int64_t y) {
    return (x + y) % MOD;
}
int64_t binPow (int64_t x, int y) {
    int64_t res = x, ans = 1;
    while (y > 0) {
        if (y & 1) {
            ans = mult(ans, res);
        }
        res = mult(res, res), y /= 2;
    }
    return ans;
}
int64_t inv (int64_t x) {
    return binPow(x, MOD - 2);
}
vector<int64_t> fact;
int64_t combo (int64_t x, int64_t y) {
    return ((x < y) ? 0 : (fact[x] * inv((fact[y] * fact[x - y]) % MOD)) % MOD);
}
int64_t f_fast (int r, int g, int rg) {
    if (!rg) {
        return 1;
    }
    if (!r || !g) {
        return 0;
    }
    return (combo(g, rg) * combo(r, rg)) % MOD;
}
int64_t stars_and_bars (int64_t stars, int64_t bars) {
    return combo(stars + bars - 1, bars - 1);
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    fact.push_back(1);
    for (int i = 0; i < (int)5e6; i++) {
        fact.push_back((fact.back() * fact.size()) % MOD);
    }
    int r, g, b, rg;
    cin >> r >> g >> b >> rg;
    int64_t ans = 0;
    for (int net_rg = rg; net_rg <= r + g + b; net_rg++) {
        int get_rid = net_rg - rg;
        ans = add(ans, mult(mult(f_fast(r, g, net_rg), stars_and_bars(b - get_rid, r + g - rg + 1)), combo(net_rg, rg)));
    }
    cout << ans;
}
