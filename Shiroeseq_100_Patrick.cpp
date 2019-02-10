// Patrick Catalin Alexandru Sava
#include <iostream>
#include <cassert>
#include <vector>
#include <map>
#include <unordered_set>
#include <set>
#include <unordered_map>

using namespace std;

//ifstream cin ("input");
//ofstream cout ("output");

bool isBetween (int inf, int number, int sup)
{
    return inf <= number and number <= sup;
}

class PolynomialHash
{
public:
    PolynomialHash() {}
    PolynomialHash(string &seq)
    {
        fv.resize(27);
        fill(fv.begin(), fv.end(), 0);
        for (auto &letter : seq)
            fv[letter - 'a' + 1] += 1;
        base = 97;
        mod = {666013, 700001};
        poly.resize(30);
        const int inf = 1;
        const int sup = 'z' - 'a' + 1;
        partialPower.resize(sup + 1);
        partialPower[0] = {1, 1};
        for (int let = inf; let <= sup; ++ let)
        {
            poly[let].first = static_cast<int>(1LL * partialPower[let - 1].first * fv[let] % mod.first);
            poly[let].second = static_cast<int>(1LL * partialPower[let - 1].second * fv[let] % mod.second);
            partialPower[let].first = static_cast<int>(1LL * partialPower[let - 1].first * base % mod.first);
            partialPower[let].second = static_cast<int>(1LL * partialPower[let - 1].second * base % mod.second);
            value.first += poly[let].first;
            if (value.first >= mod.first)
                value.first -= mod.first;
            value.second += poly[let].second;
            if (value.second >= mod.second)
                value.second -= mod.second;
        }
    }
    void decreaseLetter (char let)
    {
        int where = let - 'a' + 1;
        value.first -= partialPower[where - 1].first;
        value.first = (value.first % mod.first + mod.first) % mod.first;

        value.second -= partialPower[where - 1].second;
        value.second = (value.second % mod.second + mod.second) % mod.second;

        fv [where] -= 1;
    }

    void increaseLetter (char let)
    {
        int where = let - 'a' + 1;
        value.first += partialPower[where - 1].first;
        value.first = value.first % mod.first;

        value.second += partialPower[where - 1].second;
        value.second = value.second % mod.second;

        fv [where] += 1;
    }

    pair <int, int> getHash()
    {
        return value;
    }

private:
    vector <int> fv;
    int base;
    pair <int, int> mod;
    pair <int, int> value;
    vector <pair <int, int>> partialPower;
    vector <pair <int, int>> poly;
};

long long wrap (pair <int, int> p)
{
    return 1LL * p.first + 1000000LL * p.second;
}

long long wrapHash (long long a, long long b)
{
    return a * 700003000000LL + b;
}

unordered_map < long long, int> bestAns;

void solveTest()
{
    string s;
    assert(cin >> s);
    for (auto &element: s)
        assert(isBetween('a', element, 'z'));
    int k;
    assert(cin >> k);
    vector <string> pattern(k + 1);
    int sumLen = 0;
    vector <bool> lens(s.size() + 1, false);
    unordered_set < long long > targetedHashes;
    for (int currentIndex = 1; currentIndex <= k; ++ currentIndex) {
        assert(cin >> pattern[currentIndex]);
        sumLen += pattern[currentIndex].size();
        if (pattern[currentIndex].size() <= s.size()) {
            PolynomialHash aux(pattern[currentIndex]);
            targetedHashes.insert(wrap(aux.getHash()));
            lens[pattern[currentIndex].size()] = true;
        }
    }
    bestAns.clear();
    assert(isBetween(0, sumLen, 50000));
    for (int len = 1; len <= s.size(); ++ len)
    {
        if (lens[len] == false)
            continue;

        string pref = s.substr(0, static_cast<unsigned int>(len));
        PolynomialHash aux(pref);
        int curLen = len;
        bestAns[wrapHash(len, wrap(aux.getHash()))] = curLen;
        auto prev = aux.getHash();
        int head = len;
        int tail = 0;
        while (head < s.size())
        {
            aux.increaseLetter(s[head ++]);
            aux.decreaseLetter(s[tail ++]);
            if (aux.getHash() == prev) {
                if (targetedHashes.find(wrap(prev)) != targetedHashes.end())
                    bestAns[wrapHash(len, wrap(prev))] = max(++curLen, bestAns[wrapHash(len, wrap(prev))]);
                assert(s[head - 1] == s[tail - 1]);
            }
            else
            {
                prev = aux.getHash();
                curLen = len;
                if (targetedHashes.find(wrap(prev)) != targetedHashes.end())
                    bestAns[wrapHash(len, wrap(aux.getHash()))] = max(curLen, bestAns[wrapHash(len, wrap(aux.getHash()))]);
            }
        }
    }
    for (int currentIndex = 1; currentIndex <= k; ++ currentIndex)
    {
        if (pattern[currentIndex].size() > s.size())
            cout << (int)pattern[currentIndex].size() - 1 << '\n';
        else
        {
            PolynomialHash aux(pattern[currentIndex]);
            int bestAnsSoFar = bestAns[wrapHash(pattern[currentIndex].size(),wrap(aux.getHash()))];
            if (bestAnsSoFar == 0)
                cout << (int)pattern[currentIndex].size() - 1 << '\n';
            else cout << bestAnsSoFar << '\n';
        }
    }
}

int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    int numberOfTests;
    assert (cin >> numberOfTests);
    assert (isBetween(1, numberOfTests, 10));
    for (int currentTest = 1; currentTest <= numberOfTests; ++ currentTest)
        solveTest();
    return 0;
}
