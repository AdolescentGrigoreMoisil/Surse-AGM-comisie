/*
 * Vlad-Andrei Munteanu
 * Problem: NoPolyNoLIfe
 * Author: Tamio Nakajima-Vesa
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

int main() {
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 100000);
    while (tests--) {
        int n;
        assert (cin >> n);
        assert (3 <= n and n <= 1000000000);
        cout << (n % 2 == 1 ? "Mountain\n" : "Island\n");
    }
    return 0;
}