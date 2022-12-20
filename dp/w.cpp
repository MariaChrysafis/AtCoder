#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <cassert>
#include <bitset>
#include <queue>
#include <cmath>
#include <map>
#include <stack>
#include <ctime>
using namespace std;

struct segmentTree {
    vector<int64_t> vec;
    vector<int64_t> addLater;

    void push(int v) {
        addLater[2 * v + 1] += addLater[v];
        vec[2 * v + 1] += addLater[v];
        addLater[2 * v] += addLater[v];
        vec[2 * v] += addLater[v];
        addLater[v] = 0;
    }

    const int64_t INF = 0;

    int64_t upd(int dum, int tl, int tr, int l, int r, int64_t val) {
        if (tr < l || tl > r) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            addLater[dum] += val;
            return (vec[dum] += val);
        }
        push(dum);
        int mid = (tl + tr) >> 1;
        upd(2 * dum, tl, mid, l, r, val);
        upd(2 * dum + 1, mid + 1, tr, l, r, val);
        return (vec[dum] = max(vec[2 * dum], vec[2 * dum + 1]));
    }

    void upd(int l, int r, int64_t val) {
        upd(1, 0, (int) vec.size() / 2 - 1, l, r, val);
    }

    int64_t get(int dum, int tl, int tr, int &l, int &r) {
        if (tl > r || tr < l) {
            return INF;
        }
        if (tl >= l && tr <= r) {
            return vec[dum];
        }
        push(dum);
        int tm = (tl + tr) >> 1;
        return max(get(dum * 2, tl, tm, l, r), get(dum * 2 + 1, tm + 1, tr, l, r));
    }

    int64_t get(int l, int r) {
        return get(1, 0, (int) vec.size() / 2 - 1, l, r);
    }

    void resz(int n) {
        int sz = ((1 << (int) ceil(log2(n))));
        vec.resize(sz * 2);
        addLater.resize(sz * 2);
    }

};

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N, M;
    cin >> N >> M;
    vector<pair<int64_t,int64_t>> intervals[N];
    for (int i = 0; i < M; i++) {
        int64_t l, r, a;
        cin >> l >> r >> a;
        l--, r--;
        intervals[r].emplace_back(l, a);
    }
    for (int i = 0; i < N; i++) {
        sort(intervals[i].begin(), intervals[i].end());
    }
    segmentTree cur;
    cur.resz(N + 1);
    for (int i = 1; i <= N; i++) {
        cur.upd(i, i, cur.get(0, i));
        for (auto& p: intervals[i - 1]) {
            cur.upd(p.first + 1, i, p.second);
        }
    }
    cout << cur.get(0, N);
}
