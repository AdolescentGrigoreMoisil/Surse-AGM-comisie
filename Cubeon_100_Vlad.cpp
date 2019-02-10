/*
 * Vlad-Andrei Munteanu
 * Problem: Cubeon
 * Author: Tamio Nakajima-Vesa
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

long long getPowerOfThree (int x) {
    return 1LL * x * x * x;
}

int getCostPartial (vector <int> &partialSums, int a, int b) {
    return partialSums[b] - partialSums[a];
}

void divideTrick (vector <vector <long long>> &dp, vector <int> &partialSums, int i, int left, int right, int minN, int maxN) {
    if (left > right) return;
    int middle = left + right >> 1;
    int bestN = minN;
    for (int currentBuilding = minN; currentBuilding < min (maxN + 1, middle); ++currentBuilding) {
        if (dp[i][middle] > dp[i - 1][currentBuilding] + getPowerOfThree(getCostPartial(partialSums, currentBuilding, middle))) {
            dp[i][middle] = dp[i - 1][currentBuilding] + getPowerOfThree(getCostPartial(partialSums, currentBuilding, middle));
            bestN = currentBuilding;
        }
    }
    divideTrick(dp, partialSums, i, left, middle - 1, minN, bestN);
    divideTrick(dp, partialSums, i, middle + 1, right, bestN, maxN);
}

void buildAllDP (vector <vector <long long>> &dp, vector <int> &partialSums, const int n, const int k) {
    for (int i = 0; i <= n; ++i) {
        dp[0][i] = getPowerOfThree(getCostPartial(partialSums, 0, i));
    }
    for (int i = 1; i < k; ++i) {
        for (int j = 1; j <= n; ++j) {
            dp[i][j] = 1LL << 60;
        }
        divideTrick (dp, partialSums, i, 1, n, 0, n);
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 20);
    while (tests--) {
        vector <int> partialSums (1, 0);
        int n, k;
        assert (cin >> n >> k);
        assert (1 <= n * k and n * k <= 1000000);
        for (int i = 1; i <= n; ++i) {
            int x;
            assert (cin >> x);
            assert (0 <= x);
            partialSums.push_back(partialSums.back() + x);
        }
        assert (partialSums[n] <= 1000000);
        vector <vector <long long>> dp (static_cast<unsigned int>(k));
        for (auto &x : dp) {
            x.resize(static_cast<unsigned int>(n + 1));
        }
        buildAllDP(dp, partialSums, n, k);
        cout << dp[k - 1][n] << '\n';
    }
    return 0;
}
