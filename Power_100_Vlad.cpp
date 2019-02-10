/*
 * Vlad-Andrei Munteanu
 * Problem: Power
 * Author: Costin Andrei Oncescu
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

vector <vector <int>> mulMatrix (const vector <vector <int>> &A, const vector <vector <int>> &B, const int MOD) {
    vector <vector <int>> C (A.size());
    for (int i = 0; i < C.size(); ++i) {
        C[i].resize (B[0].size());
        for (int j = 0; j < C[i].size(); ++j) {
            C[i][j] = 0;
            for (int k = 0; k < A[i].size(); ++k) {
                C[i][j] = static_cast<int>((C[i][j] + 1LL * A[i][k] * B[k][j]) % MOD);
            }
        }
    }
    return C;
}

vector <vector <vector <int>>> init (const vector <vector <int>> &A, const int MOD) {
    vector <vector <vector <int>>> result;
    result.push_back(A);
    for (int i = 1; i <= 60; ++i) {
        result.push_back(mulMatrix(result.back(), result.back(), MOD));
    }
    return result;
}

vector <vector <int>> generateMatrix (vector <int> &generator) {
    vector <vector <int>> result;
    for (int i = 0; i < (int)generator.size() - 1; ++i) {
        vector <int> newOne (generator.size(), 0);
        newOne[i + 1] = 1;
        result.push_back(newOne);
    }
    reverse (generator.begin(), generator.end());
    result.push_back(generator);
    return result;
}

int finalResult (const vector <vector <vector <int>>> &powersOfMatrix, vector <vector <int>> pVector, long long n, const int MOD) {
    n -= 1;
    for (int i = 0; i <= 60; ++i) {
        if (n & (1LL << i)) {
            pVector = mulMatrix(powersOfMatrix[i], pVector, MOD);
        }
    }
    return pVector[0][0];
}

int fastBrute (const vector <vector <vector <int>>> &powersOfMatrix, const vector <vector <int>> &pVector, long long n, const int MOD) {
    n -= 1;
    vector <vector <int>> result;
    for (int i = 0; i < pVector.size(); ++i) {
        vector <int> current (pVector.size(), 0);
        current[i] = 1;
        result.push_back(current);
    }
    for (int i = 0; i <= 60; ++i) {
        if (n & (1LL << i)) {
            result = mulMatrix(result, powersOfMatrix[i], MOD);
        }
    }
    result = mulMatrix(result, pVector, MOD);
    return result[0][0];
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 10);
    while (tests--) {
        vector <int> generator;
        int k, q, MOD = static_cast<int>(1e9 + 7);
        assert (cin >> k >> q);
        assert (1 <= k and k <= 20);
        assert (1 <= q and q <= 1000);
        for (int i = 1; i <= k; ++i) {
            int x;
            assert (cin >> x);
            assert (0 <= x and x <= 1000000000);
            generator.push_back(x);
        }
        vector <vector <int>> mainMatrix = generateMatrix(generator);
        vector <vector <vector <int>>> powersOfMatrix = init (mainMatrix, MOD);
        vector <vector <int>> pVector (static_cast<unsigned int>(k));
        for (int i = 1; i <= k; ++i) {
            int x;
            cin >> x;
            pVector[i - 1].push_back(x);
        }
        for (int i = 0; i < q; ++i) {
            long long n;
            assert (cin >> n);
            assert (1 <= n and n <= 1000000000000000000LL);
            cout << finalResult(powersOfMatrix, pVector, n, MOD) << '\n';
//            cout << fastBrute(powersOfMatrix, pVector, n, MOD) << '\n';
        }
    }
    return 0;
}
