/*
 * Vlad-Andrei Munteanu
 * Problem: Akanemat
 * Author: Tamio Nakajima-Vesa
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

vector <char> generator (vector <char> permutation, int step) {
    for (int i = 2; i <= 5; ++i) {
        vector <char> newPerm;
        for (int j = permutation.size() - step; j < permutation.size(); ++j) {
            newPerm.push_back(permutation[j]);
        }
        for (int j = permutation.size() - 5; j < permutation.size() - step; ++j) {
            newPerm.push_back(permutation[j]);
        }
        for (auto x : newPerm) {
            permutation.push_back(x);
        }
    }
    return permutation;
}

void initialize (vector <vector <vector <char>>> &container) {
    vector <vector <char>> source;
    vector <char> currentPermutation = {'a', 'b', 'c', 'd', 'e'};
    for (int i = 1; i <= 120; ++i) {
        source.push_back(generator (currentPermutation, 2));
        source.push_back(generator (currentPermutation, 3));
        next_permutation(currentPermutation.begin(), currentPermutation.end());
    }
    for (int i = 3; i <= 5; ++i) {
        vector <vector <char>> currentResult;
        for (auto &x : source) {
            vector <char> aux;
            for (int j = 0; j < x.size(); ++j) {
                if (j % 5 >= i) continue;
                aux.push_back(x[j]);
            }
            currentResult.push_back(aux);
        }
        sort (currentResult.begin(), currentResult.end());
        container.push_back(currentResult);
    }
}

vector <vector <char>> generateMatrix (const vector <char> &generate, int n, int m) {
    vector <vector <char>> answer;
    for (int i = 0; i < n; ++i) {
        if (i >= 5) {
            answer.push_back(answer[i - 5]);
            continue;
        }
        vector <char> currentLine;
        for (int j = 0; j < m; ++j) {
            if (j >= 5) {
                currentLine.push_back(currentLine[j - 5]);
            }
            else {
                currentLine.push_back(generate[i * min (5, m) + j]);
            }
        }
        answer.push_back(currentLine);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector < vector < vector <char>>> container;
    initialize(container);
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 100000);
    long long sumOfTests = 0;
    while (tests--) {
        int n, m;
        long long k;
        assert (cin >> n >> m >> k);
        assert (3 <= n and n <= 1000000);
        assert (3 <= m and m <= 1000000);
        assert (0 <= k and k <= 1000000000000000000LL);
        sumOfTests += n * m;
        assert (sumOfTests <= 1000000);
        int where = min (m - 3, 2);
        if (k >= container[where].size()) {
            cout << -1 << '\n';
        }
        else {
            vector <vector <char>> answer = generateMatrix(container[where][k], n, m);
            for (auto &x : answer) {
                for (auto &y : x) {
                    cout << y;
                }
                cout << '\n';
            }
        }
    }
    return 0;
}