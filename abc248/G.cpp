#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;
const int MX = 1e5 + 10;
const int MOD = 998244353;
int a[MX];
struct Tree {
    vector<vector<int>> adj;
    void add_edge (int u, int v) {
        this->adj[u].push_back(v), this->adj[v].push_back(u);
    }
    set<int> vis;
    vector<int64_t> sz, cc, pl;
    void dfs (int cur, int prev, int g) {
        vis.insert(cur);
        sz[cur] = 1, cc[cur] = 0, pl[cur] = 0;
        for (int i: adj[cur]) {
            if (i != prev and a[i] % g == 0) {
                dfs(i, cur, g);
                pl[cur] += pl[i];
                pl[cur] += sz[cur] * cc[i] + sz[i] * cc[cur] + sz[i] * sz[cur];
                cc[cur] += cc[i] + sz[i];
                sz[cur] += sz[i];
            }
        }
    }
    Tree (int n) {
        this->adj.resize(n), this->sz.resize(n), this->cc.assign(n, 1), this->pl.assign(n, 1);
    }
};
int main() {
    //freopen("deleg.out", "r", stdin);
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int mu[MX];
    bool isPrime[MX];
    for (int i = 1; i < MX; i++) {
        isPrime[i] = true;
        mu[i] = 0;
    }
    for (int i = 2; i < MX; i++) {
        if (isPrime[i]) {
            for (int j = i; j < MX; j += i) {
                mu[j]++;
                isPrime[j] = false;
            }
        }
    }
    for (int i = 0; i < MX; i++) {
        if (mu[i] % 2 == 0) {
            mu[i] = 1;
        } else {
            mu[i] = -1;
        }
    }
    for (int64_t i = 2; i < MX; i++) {
        for (int64_t j = i * i; j < MX; j += i * i) {
            mu[j] = 0;
        }
    }
    for (int i = 0; i < n; i++) {
        cin >> a[i];
    }
    Tree myTree(n);
    for (int i = 0; i < n - 1; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        myTree.add_edge(u, v);
    }
    map<int,vector<int>> myMap;
    for (int i = 0; i < n; i++) {
        myMap[a[i]].push_back(i);
    }
    int64_t gamma[MX];
    for (int i = 1; i < MX; i++) { //look at nodes that are divisible by i
        int64_t ans = 0;
        for (int j = i; j < MX; j += i) {
            for (int x: myMap[j]) {
                if (!myTree.vis.count(x)) {
                    myTree.dfs(x, x, i);
                    ans += myTree.pl[x];
                    ans %= MOD;
                    ans += (myTree.sz[x] * (myTree.sz[x] - 1))/2;
                    ans %= MOD;
                }
            }
        }
        myTree.vis.clear();
        gamma[i] = ans;
    }
    int64_t res = 0;
    for (int64_t i = 1; i < MX; i++) {
        int64_t ans = 0;
        for (int j = i; j < MX; j += i) {
            ans += mu[j/i] * gamma[j];
        }
        res += (ans * i) % MOD;
        res %= MOD;
    }
    cout << res << '\n';
}
