#include <iostream>
#include <vector>
#include <map>
#include <cmath>

using namespace std;
struct Node {
    int64_t mat[3][3];
    int64_t oc[3];
    Node () {
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                mat[i][j] = 0;
            }
            oc[i] = 0;
        }
    }
};
bool equal (Node node1, Node node2) {
    for (int i = 0; i < 3; i++) {
        if (node1.oc[i] != node2.oc[i]) {
            return false;
        }
        for (int j = 0; j < 3; j++) {
            if (j != i && node1.mat[i][j] != node2.mat[i][j]) {
                return false;
            }
        }
    }
    return true;
}
vector<int> norm = {0, 1, 2};
int64_t get_inversions (Node node) {
    int64_t ans = 0;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < i; j++) {
            ans += node.mat[i][j];
        }
    }
    return ans;
}
struct SegmentTree {
    vector<Node> nodes;
    vector<vector<int>> lazy;
    Node merge (Node node1, Node node2) {
        Node node = Node();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                node.mat[i][j] += node1.oc[i] * node2.oc[j] + node1.mat[i][j] + node2.mat[i][j];
            }
            node.oc[i] = node1.oc[i] + node2.oc[i];
        }
        return node;
    }
    void push_tag (int ind, vector<int> v) {
        auto cur = Node();
        for (int i = 0; i < 3; i++) {
            for (int j = 0; j < 3; j++) {
                cur.mat[v[i]][v[j]] += nodes[ind].mat[i][j];
            }
            cur.oc[v[i]] += nodes[ind].oc[i];
        }
        nodes[ind] = cur;
        lazy[ind] = compose(v, lazy[ind]);
    }
    void push_down (int ind) {
        push_tag(2 * ind + 1, lazy[ind]);
        push_tag(2 * ind + 2, lazy[ind]);
        lazy[ind] = norm;
    }
    Node query (int l, int r) {
        return query(0, 0, (int)nodes.size()/2 - 1, l, r);
    }
    vector<int> compose (vector<int> v1, vector<int> v2) { //v1(v2(i))
        return {v1[v2[0]], v1[v2[1]], v1[v2[2]]};
    }
    void change (int dum, int tl, int tr, int l, int r, vector<int> new_id) {
        if (tl > r || tr < l) {
            return;
        }
        if (tl >= l && tr <= r) {
            push_tag(dum, new_id);
            return;
        }
        push_down(dum);
        change(2 * dum + 1, tl, (tl + tr)/2, l, r, new_id);
        change(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r, new_id);
        nodes[dum] = merge(nodes[2 * dum + 1], nodes[2 * dum + 2]);
    }
    Node query (int dum, int tl, int tr, int l, int r) {
        if (tl > r || tr < l) {
            return {};
        }
        if (tl >= l && tr <= r) {
            return nodes[dum];
        }
        push_down(dum);
        return merge(query(2 * dum + 1, tl, (tl + tr)/2, l, r), query(2 * dum + 2, (tl + tr)/2 + 1, tr, l, r));
    }
    void change (int l, int r, vector<int> new_id) {
        change(0, 0, nodes.size()/2 - 1, l, r, new_id);
    }
    SegmentTree (vector<int> v) {
        while (pow(2, (int)log2(v.size())) != v.size()) {
            v.push_back(1);
        }
        nodes.resize(2 * v.size());
        lazy.assign(nodes.size(), norm);
        build(v, 0, 0, (int)v.size() - 1);
    }
    void build (vector<int>& v, int dum, int tl, int tr) {
        if (tl == tr) {
            nodes[dum] = Node();
            nodes[dum].oc[v[tl]] = 1;
        } else {
            build(v, 2 * dum + 1, tl, (tl + tr)/2);
            build(v, 2 * dum + 2, (tl + tr)/2 + 1, tr);
            nodes[dum] = merge(nodes[dum * 2 + 1], nodes[2 * dum + 2]);
        }
    }
};
int main() {
    int N, Q;
    cin >> N >> Q;
    vector<int> arr(N);
    for (int i = 0; i < N; i++) {
        cin >> arr[i];
    }
    SegmentTree st(arr);
    for (int i = 0; i < Q; i++) {
        int t;
        cin >> t;
        if (t == 1) {
            int L, R;
            cin >> L >> R;
            --L, --R;
            cout << get_inversions(st.query(L, R)) << '\n';
        } else {
            int L, R, S, T, U;
            cin >> L >> R >> S >> T >> U;
            --L, --R;
            st.change(L, R, {S, T, U});
        }
    }
}
