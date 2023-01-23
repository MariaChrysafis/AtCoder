#include <iostream>
#include <vector>
#include <set>

using namespace std;

struct DisjointSetUnion {
    vector<vector<int>> adj;
    vector<int> parent, sz;
    void add_edge (int u, int v) {
        adj[u].push_back(v), adj[v].push_back(u);
    }
    int find_head (int x) {
        return ((x == parent[x]) ? x : find_head(parent[x]));
    }
    void join (int u, int v) {
        u = find_head(u), v = find_head(v);
        if (u != v) {
            if (sz[u] > sz[v]) {
                swap(u, v);
            }
            sz[v] += sz[u];
            parent[u] = v;
        }
    }
    DisjointSetUnion (int n) {
        adj.resize(n);
        sz.assign(n, 1);
        for (int i = 0; i < n; i++) {
            parent.push_back(i);
        }
    }
};

int main() {
    int n, m;
    cin >> n >> m;
    DisjointSetUnion dsu(n);
    vector<pair<int,int>> edges;
    set<pair<int,int>> s;
    for (int i = 0; i < m; i++) {
        int u, v;
        cin >> u >> v;
        --u, --v;
        edges.emplace_back(make_pair(min(u, v), max(u, v)));
        s.insert(edges.back());
    }
    int k;
    cin >> k;
    for (int i = 0; i < k; i++) {
        int x; cin >> x;
        s.erase(edges[--x]);
    }
    for (auto& i: s) {
        dsu.join(i.first, i.second);
    }
    for (auto& p: edges) {
        p.first = dsu.find_head(p.first);
        p.second = dsu.find_head(p.second);
    }
    vector<int> deg;
    deg.assign(n, false);
    for (auto& p: edges) {
        if (p.first != p.second) {
            deg[p.first] ^= 1, deg[p.second] ^= 1;
        }
    }
    int ans = 0;
    for (int i = 0; i < n; i++) {
        ans += deg[i];
    }
    cout << ((ans == 2 || ans == 0) ? "Yes": "No");
}
