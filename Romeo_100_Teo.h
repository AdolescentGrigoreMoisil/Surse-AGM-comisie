#include <bits/stdc++.h>
using namespace std;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests;
    cin >> tests;
    while (tests--) {
        int n, k;
        cin >> n >> k;
        map<int, int> norm;
        vector<int> v(n + 1, 0);
        for (int i = 1; i <= n; i++) {
            int val;
            cin >> val;
            norm[val] = i;
        }
        int idx = 0;
        for (auto it : norm) {
            v[it.second] = n - idx++;
        }
        vector<int> sh(n + 1, 0), ans(n + 1, 0);
        int zero = 0;
        set<int> sm, la;
        for (int i = 1; i < k; i++) {
            sm.insert(v[i]);
        }
        auto pushsm = [&sm, &sh, &zero] (int val) {
            sh[val] = zero;
            sm.insert(val);
        };
        auto popsm = [&sm, &sh, &zero, &ans] (int val) {
            ans[val] += zero - sh[val];
            sm.erase(sm.find(val));
        };
        for (int i = k; i <= n; i++) {
            if (v[i] <= *sm.rbegin()) {
                pushsm(v[i]);
            } else {
                la.insert(v[i]);
            }
            while (sm.size() > la.size()) {
                la.insert(*sm.rbegin());
                popsm(*sm.rbegin());
            }
            while (la.size() > sm.size()) {
                pushsm(*la.begin());
                la.erase(la.begin());
            }
            zero ++;
            if (v[i-k+1] <= *sm.rbegin()) {
                popsm(v[i-k+1]);
            } else {
                la.erase(la.find(v[i-k+1]));
            }
        }
        while (sm.size() > 0) {
            popsm(*sm.begin());
        }
        for (int i = 1; i <= n; i++) {
            cout << ans[v[i]] << ' ';
        }
        cout << '\n';
    }
    return 0;
}