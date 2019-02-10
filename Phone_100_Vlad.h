/*
 * Vlad-Andrei Munteanu
 * Problem: Phone
 * Author: George Marcus
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
//    freopen ("input", "r", stdin);
    int t;
    cin >> t;
    while (t--) {
        int n, x;
        cin >> n >> x;
        string s;
        cin >> s;
        if (x <= 1) {
            cout << "YES\n";
            continue;
        }
        if (x <= 2) {
            if (n <= 1) {
                cout << "NO\n";
                continue;
            }
            bool ok = false;
            for (int i = 1; i < n; ++i) {
                if (s[i] != '0') {
                    ok = true;
                }
            }
            if (ok) {
                cout << "YES\n";
            }
            else {
                cout << "NO\n";
            }
            continue;
        }
        bool ok = false;
        for (int i = 1; i < n; ++i) {
            for (int j = 1; j <= n - i; ++j) {
                long long result = 0;
                for (int cur = i + 1; cur <= i + j; ++cur) {
                    result = result * 10 + s[cur - 1] - '0';
                }
                long long aux = result - 1;
                if (aux < 0) {
                    continue;
                }
                string ans;
                for (int k = 1; k <= i; ++k) {
                    if (aux == 0) break;
                    ans = (char)(aux % 10 + '0') + ans;
                    aux /= 10;
                }
                if (ans.size() != i) continue;
                for (int k = 2; k < x; ++k) {
                    string pluss;
                    long long cp = result;
                    while (result) {
                        pluss += (char) (result % 10 + '0');
                        result /= 10;
                    }
                    reverse (pluss.begin(), pluss.end());
                    ans += pluss;
                    result = cp + 1;
                }
                if (s.size() <= ans.size()) continue;
                string pluss;
                long long cp = result;
                while (result) {
                    pluss += (char) (result % 10 + '0');
                    result /= 10;
                }
                reverse (pluss.begin(), pluss.end());
                ans += pluss;
                while (ans.size() > s.size()) ans.pop_back();
                ok = (ans == s);
                if (ok) break;
            }
            if (ok) break;
        }
        if (ok) cout << "YES\n";
        else cout << "NO\n";
    }
    return 0;
}