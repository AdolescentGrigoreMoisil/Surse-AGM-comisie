/*
 * Vlad-Andrei Munteanu
 * Problem: Arugaktus
 * Author: Tamio Nakajima-Vesa
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

void dfs (int node, int father, int currentLevel, const vector <vector <int>> &graph, vector <int> &levels, vector <int> &lengths, vector <int> &inStack) {
    levels[node] = currentLevel;
    inStack[node] = 1;
    for (int i = 0; i < (int)graph[node].size(); ++ i) {
        auto x = graph[node][i];
        if (x == father) continue;
        if (levels[x]) {
            if (inStack[x]) {
                lengths.push_back(currentLevel - levels[x] + 1);
            }
        }
        else {
            dfs (x, node, currentLevel + 1, graph, levels, lengths, inStack);
        }
    }
    inStack[node] = 0;
}

int solveOneK (vector <int> &lengths, vector <int> &precomputed, const int MOD, int k) {
    int answer = 1;
    precomputed[0] = 1;
    for (int i = 1; i < precomputed.size(); ++i) {
        precomputed[i] = static_cast<int>(1LL * (k - 1) * precomputed[i - 1] % MOD);
    }
    int rootLength = lengths.back();
    lengths.pop_back();
    for (auto x : lengths) {
        if (x == 1) {
            answer = static_cast<int>(1LL * answer * (k - 1) % MOD);
        }
        else {
            int sum = 0;
            int currentSign = 1;
            for (int currentPower = x; currentPower >= 2; --currentPower) {
                sum = (sum + currentSign * precomputed[currentPower]) % MOD;
                currentSign *= -1;
            }
            if (sum < 0) sum += MOD;
            answer = static_cast<int>(1LL * answer * sum % MOD);
        }
    }
    lengths.push_back(rootLength);
    if (rootLength == 1) {
        answer = static_cast<int>(1LL * answer * k % MOD);
    }
    else {
        int sum = 0;
        int currentSign = 1;
        for (int currentPower = rootLength; currentPower >= 2; --currentPower) {
            sum = static_cast<int>((sum + 1LL * currentSign * precomputed[currentPower - 1] * k) % MOD);
            currentSign *= -1;
        }
        if (sum < 0) sum += MOD;
        answer = static_cast<int>(1LL * answer * sum % MOD);
    }
    return answer;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 20);
    while (tests--) {
        vector <vector <int>> graph;
        vector <int> levels, precomputed, lengths;
        vector <int> inStack;
        const int MOD = 1000000007;
        int n, m, q;
        assert (cin >> n >> m >> q);
        assert (1 <= n and n <= 100000);
        assert (1 <= m and m <= 200000);
        assert (1 <= q and q <= 10);
        graph.resize(static_cast<unsigned int>(n + 1));
        levels.resize(static_cast<unsigned int>(n + 1), 0);
        precomputed.resize(static_cast<unsigned int>(n + 1), 1);
        inStack.resize(static_cast<unsigned int>(n + 1), false);
        for (int i = 1; i <= m; ++i) {
            int x, y;
            assert (cin >> x >> y);
            assert(1 <= x and x <= n);
            assert(1 <= y and y <= n);
            graph[x].push_back(y);
            graph[y].push_back(x);
        }
        dfs (1, -1, 1, graph, levels, lengths, inStack);
        int total = 0;
        for (auto x : lengths) {
            total += x;
        }
        while (total < n) {
            total += 1;
            lengths.push_back(1);
        }
        for (auto x : lengths) {
            assert (x % 2);
        }
        for (int i = 1; i <= q; ++i) {
            int k;
            assert (cin >> k);
            assert (1 <= k and k <= 1000000000);
            cout << solveOneK(lengths, precomputed, MOD, k) << '\n';
        }
    }
    return 0;
}