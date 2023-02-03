#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>

using namespace std;
vector<vector<int>> evens (vector<int> v) {
    vector<vector<int>> vec;
    vec.emplace_back();
    for (int i = 0; i < v.size(); i++) {
        if (v[i] % 2 == 1) {
            vec.push_back({v[i]});
            vec.emplace_back();
        } else {
            vec.back().push_back(v[i]);
        }
    }
    for (int i = 0; i < vec.size(); i++) {
        if (vec[i].size() >= 3) {
            sort(vec[i].begin(), vec[i].end());
        }
    }
    return vec;
}
bool has (vector<int> a) {
    int n = a.size();
    for (int i = 0; i < n - 2; i++) {
        if ((a[i] + a[i + 1] + a[i + 2]) % 2 == 0 and !(a[i] % 2 == 0 and a[i + 1] % 2 == 0 and a[i + 2] % 2 == 0)) {
            return true;
        }
    }
    return false;
}
int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    vector<int> a(n);
    map<int,int> myMap;
    vector<int> ea, eb;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        if (a[i] % 2 == 0) {
            ea.push_back(a[i]);
        }
        myMap[a[i]]++;
    }
    vector<int> b(n);
    for (int i = 0; i < n; i++) {
        cin >> b[i];
        if (b[i] % 2 == 0) {
            eb.push_back(b[i]);
        }
        myMap[b[i]]--;
    }
    for (auto& p: myMap) {
        if (p.second != 0) {
            cout << "No";
            exit(0);
        }
    }
    if (has(a) and has(b)) {
        if (ea.size() == 2 and ea != eb) {
            cout << "No";
            exit(0);
        }
        cout << "Yes";
        exit(0);
    }
    if (has(a) and !has(b)) {
        swap(a, b);
    }
    if (!has(a) and has(b)) {
        cout << "No";
        exit(0);
    }
    if (evens(a) == evens(b)) {
        cout << "Yes";
        exit(0);
    }
    cout << "No";
}
