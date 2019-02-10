/*
 * Vlad-Andrei Munteanu
 * Problem: Romeo
 * Author: Teodor Ionescu
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

int aib[100001];

void initAib (int n) {
    for (int i = 0; i <= n; ++i) {
        aib[i] = 0;
    }
}

int mub (int x) {
    return x & (-x);
}

void update (int pos, int n) {
    while (pos <= n) {
        aib[pos] += 1;
        pos += mub (pos);
    }
}

int getPrefix (int pos) {
    int sum = 0;
    while (pos) {
        sum += aib[pos];
        pos -= mub (pos);
    }
    return sum;
}

int getSum (int a, int b) {
    return getPrefix(b) - getPrefix(a - 1);
}

void updateBit (int currentBit, vector <pair <pair <int, int>, int>> &intervals, vector <pair <int, int>> &values, int n, int target) {
    initAib(n);
    vector <pair <pair <int, int>, int>> updated, notUpdated;
    int currentPosition = 0;
    for (auto x : intervals) {
        int left = x.first.first;
        int right = x.first.second;
        int value = x.second;
        value |= (1 << currentBit);
        while (currentPosition < n and values[currentPosition].first <= value) {
            update(values[currentPosition].second, n);
            currentPosition += 1;
        }
        if (getSum(left, right) <= (right - left + 1 - target)) {
            updated.push_back({{left, right}, value});
        }
        else {
            notUpdated.push_back({{left, right}, value ^ (1 << currentBit)});
        }
    }
    intervals.clear();
    int currentInUpdated = 0, currentInNotUpdated = 0;
    while (currentInUpdated < updated.size() or currentInNotUpdated < notUpdated.size()) {
        if (currentInNotUpdated == notUpdated.size() or (currentInUpdated < updated.size() and updated[currentInUpdated].second < notUpdated[currentInNotUpdated].second)) {
            intervals.push_back(updated[currentInUpdated]);
            currentInUpdated += 1;
        }
        else {
            intervals.push_back(notUpdated[currentInNotUpdated]);
            currentInNotUpdated += 1;
        }
    }
    updated.clear();
    notUpdated.clear();
}

void parallelBinarySearch (vector <pair <pair <int, int>, int>> &intervals, vector <pair <int, int>> &values, int n, int target) {
    for (int power = 20; power >= 0; --power) {
        updateBit(power, intervals, values, n, target);
    }
}

vector <pair <int, int>> normalize (vector <int> &values) {
    vector <pair <int, int>> normalized;
    for (int i = 0; i < values.size(); ++i) {
        normalized.emplace_back(values[i], i + 1);
    }
    int currentValue = 1;
    sort (normalized.begin(), normalized.end());
    for (auto &x : normalized) {
        x.first = currentValue;
        currentValue += 1;
    }
    return normalized;
}

void solve (vector <pair <pair <int, int>, int>> &intervals, vector <pair <int, int>> &values, vector <int> &answer, int n, int k) {
    answer.resize(static_cast<unsigned int>(n + 1));
    initAib(n);
    int currentPosition = 0;
    for (auto x : values) {
        while (currentPosition < intervals.size() and intervals[currentPosition].second < x.first) {
            update(intervals[currentPosition].first.first, n);
            currentPosition += 1;
        }
        answer[x.second] = getSum(max (1, x.second - k + 1), x.second);
    }
}


int main() {
//    freopen ("input", "r", stdin);
//    freopen ("output", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    int tests;
    assert (cin >> tests);
    assert (1 <= tests and tests <= 10);
    while (tests--) {
        vector <int> answer;
        vector <pair <int, int>> values;
        vector <pair <pair <int, int>, int>> intervals;
        vector <int> v;
        int n, k, target;
        assert (cin >> n >> k);
        assert (1 <= n and n <= 100000);
        assert (1 <= k and k <= n and k % 2 == 0);
        target = k / 2;
        for (int i = 1; i <= n; ++i) {
            int x;
            assert (cin >> x);
            assert (1 <= x and x <= 1000000000);
            v.push_back(x);
            if (i + k - 1 <= n) {
                intervals.push_back({{i, i + k - 1}, 0});
            }
        }
        values = normalize(v);
        parallelBinarySearch(intervals, values, n, target);
        solve (intervals, values, answer, n, k);
        for (int i = 1; i < answer.size(); ++i) {
            auto x = answer[i];
            cout << x << ' ';
        }
        cout << '\n';
    }
    return 0;
}
