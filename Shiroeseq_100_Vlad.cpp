/*
 * Vlad-Andrei Munteanu
 * Problem: Shiroeseq
 * Author: Tamio Nakajima-Vesa
 * Expected: Accepted
 */

#include <random>
#include <bits/stdc++.h>

using namespace std;


vector <pair <pair <int, int>, int>> maximum [666013];

void buildPrimes (vector <int> &primes) {
    vector <bool> visited (10000, true);
    for (int i = 2; i < visited.size(); ++i) {
        if (visited[i]) {
            primes.push_back(i);
            for (int j = i + i; j < visited.size(); j += i) {
                visited[i] = false;
            }
        }
    }
    shuffle(primes.begin(), primes.end(), std::mt19937(std::random_device()()));
}

int fastExp (int a, int b, const int MOD) {
    if (b == 0) return 1;
    if (b % 2) return static_cast<int>(1LL * a * fastExp(a, b - 1, MOD) % MOD);
    return fastExp (static_cast<int>(1LL * a * a % MOD), b / 2, MOD);
}

void insert (int hash1, int hash2, int value, bool init) {
    int position = static_cast<int>((1LL * hash1 * 1002001 + hash2) % 666013);
    for (auto &x : maximum[position]) {
        if (x.first == make_pair(hash1, hash2)) {
            x.second = max (x.second, value);
            return;
        }
    }
    if (init) {
        maximum[position].push_back({{hash1, hash2}, value});
    }
}

int getValue (int hash1, int hash2) {
    int position = static_cast<int>((1LL * hash1 * 1002001 + hash2) % 666013);
    for (auto &x : maximum[position]) {
        if (x.first == make_pair(hash1, hash2)) {
            return x.second;
        }
    }
    return 0;
}

void solve (string &source, vector <int> &targets, vector <string> &patterns, vector <int> &answer, vector <int> &primes, vector <int> &revMod1, vector <int> &revMod2) {
    set <pair <int, int>> toDelete;
    int currentLength = patterns[targets.back()].size();
    const int MOD1 = 666013;
    const int MOD2 = 1000000007;
    for (auto x : targets) {
        string currentPattern = patterns[x];
        int patternHash1 = 1;
        int patternHash2 = 1;
        for (auto y : currentPattern) {
            patternHash1 = static_cast<int>(1LL * patternHash1 * primes[y - 'a'] % MOD1);
            patternHash2 = static_cast<int>(1LL * patternHash2 * primes[y - 'a' + 26] % MOD2);
        }
        insert(patternHash1, patternHash2, currentLength - 1, true);
    }
    int hash1 = 1;
    int hash2 = 1;
    int currentBack = 0;
    for (int i = 0; i < source.size(); ++i) {
        if (i < currentLength) {
            hash1 = static_cast<int>(1LL * hash1 * primes[source[i] - 'a'] % MOD1);
            hash2 = static_cast<int>(1LL * hash2 * primes[source[i] - 'a' + 26] % MOD2);
        }
        else if (source[i - currentLength] == source[i]) {
            continue;
        }
        else {
            insert (hash1, hash2, i - currentBack, false);
            currentBack = i - currentLength + 1;
            hash1 = static_cast<int>(1LL * hash1 * revMod1[source[currentBack - 1] - 'a'] % MOD1);
            hash2 = static_cast<int>(1LL * hash2 * revMod2[source[currentBack - 1] - 'a' + 26] % MOD2);
            hash1 = static_cast<int>(1LL * hash1 * primes[source[i] - 'a'] % MOD1);
            hash2 = static_cast<int>(1LL * hash2 * primes[source[i] - 'a' + 26] % MOD2);
        }
    }
    insert (hash1, hash2, (int) source.size() - currentBack, false);
    for (auto x : targets) {
        string currentPattern = patterns[x];
        int patternHash1 = 1;
        int patternHash2 = 1;
        for (auto y : currentPattern) {
            patternHash1 = static_cast<int>(1LL * patternHash1 * primes[y - 'a'] % MOD1);
            patternHash2 = static_cast<int>(1LL * patternHash2 * primes[y - 'a' + 26] % MOD2);
        }
        answer[x] = max (getValue(patternHash1, patternHash2), currentLength - 1);
        toDelete.insert({patternHash1, patternHash2});
    }
    for (auto x : toDelete) {
        int position = static_cast<int>((1LL * x.first * 1002001 + x.second) % 666013);
        maximum[position].clear();
    }
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    vector <int> primes;
    vector <int> revMod1;
    vector <int> revMod2;
    const int MOD1 = 666013;
    const int MOD2 = 1000000007;
    buildPrimes(primes);
    for (auto x : primes) {
        revMod1.push_back(fastExp(x, MOD1 - 2, MOD1));
        revMod2.push_back(fastExp(x, MOD2 - 2, MOD2));
    }
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 10);
    while (tests--) {
        vector <vector <int>> buckets (100001);
        vector <int> answer;
        vector <string> patterns;
        string source;
        assert (cin >> source);
        assert (1 <= source.size() and source.size() <= 50000);
        int patternsNo, sumOfSizes = 0;
        assert (cin >> patternsNo);
        answer.resize(static_cast<unsigned int>(patternsNo));
        for (int i = 1; i <= patternsNo; ++i) {
            string current;
            assert (cin >> current);
            assert (current.size() <= source.size());
            sumOfSizes += current.size();
            patterns.push_back(current);
            buckets[current.size()].push_back(i - 1);
        }
        assert (sumOfSizes <= 50000);
        for (int i = 1; i <= source.size(); ++i) {
            if (buckets[i].empty()) continue;
            solve (source, buckets[i], patterns, answer, primes, revMod1, revMod2);
        }
        for (auto x : answer) {
            cout << x << '\n';
        }
    }
    return 0;
}
