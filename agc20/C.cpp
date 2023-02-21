#include <iostream>
#include <set>
#include <vector>
#include <map>
#include <algorithm>
#include <queue>
#include <cassert>
#include <bit>
#include <bitset>
#include <cmath>

using namespace std;

int main() {
    ios::sync_with_stdio(0);
    cin.tie(0);
    int n;
    cin >> n;
    int a[n];
    int sum = 0;
    bitset<4000001> bs;
    bs[0] = true;
    for (int i = 0; i < n; i++) {
        cin >> a[i];
        bs |= (bs << a[i]);
        sum += a[i];
    }
    for (int i = (sum + 1)/2; i < 4000001; i++) {
        if (bs[i]) {
            cout << i;
            return 0;
        }
    }
}
