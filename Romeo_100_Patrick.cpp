/// Patrick Catalin Alexandru Sava
#include <iostream>
#include <cassert>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX = static_cast<const int>(1e5 + 14);
int aib [MAX];

void init (const int lim)
{
    assert(lim < MAX);
    for (int i = 0; i <= lim; ++ i)
        aib [i] = 0;
}

int lsb (const int x)
{
    return x & -x;
}

void update (int pos, const int n)
{
    for (; pos <= n; pos += lsb(pos))
        aib[pos] += 1;
}

int Q(int pos)
{
    int s = 0;
    while (pos)
        s += aib [pos],
        pos -= lsb(pos);
    return s;
}

int RQ(const int a, const int b)
{
    assert(a <= b);
    return Q(b) - Q(a - 1);
}

void compute (vector < pair <int, pair <int, int> > > &biggestBad,
              const vector < pair <int, int> > &values,
              const int k)
{
    for (int bit = 30; bit >= 0; -- bit)
    {
        int p = 0;
        init(values.size());
        vector < pair <int, pair <int, int> > > chosen;
        vector < pair <int, pair <int, int> > > notChosen;
        for (auto &element : biggestBad)
        {
            while (p < values.size() and values[p].first <= (element.first | (1 << bit)))
                update(values[p++].second, values.size());
            if (RQ(element.second.first, element.second.second) <= k / 2)
            {
                element.first |= (1 << bit);
                chosen.push_back(element);
            }
            else notChosen.push_back(element);
        }
        biggestBad.clear();
        merge(chosen.begin(), chosen.end(), notChosen.begin(), notChosen.end(),
              back_inserter(biggestBad),
              [](const pair <int, pair <int, int> >& p1, const pair <int, pair <int, int> >& p2) -> bool
              {
                  return p1.first < p2.first;
              });
    }
    init(values.size());
    vector <int> ans (values.size() + 1, 0);
    int p = 0;
    for (auto element : values)
    {
        while (p < biggestBad.size() and  biggestBad[p].first < element.first)
            update(biggestBad[p ++].second.first, values.size());
        ans[element.second] = RQ(max(1, element.second - k + 1), element.second);
    }
    for (int i = 1; i <= values.size(); ++ i)
        cout << ans[i] << ' ';
    cout << '\n';
}

int main() {
    ios :: sync_with_stdio(false);
    cin.tie(nullptr);
    int tests;
    assert(cin >> tests);
    assert(1 <= tests and tests <= 10);
    while (tests --)
    {
        int n, k;
        assert(cin >> n >> k);
        assert(k <= n and k % 2 == 0);
        vector < pair <int, int> > values;
        for (int i = 1; i <= n; ++ i)
        {
            int element;
            assert(cin >> element);
            assert(1 <= element and element <= 1000000000);
            values.emplace_back(element, i);
        }
        sort(values.begin(), values.end());
        assert(values.size() == n);
        vector < pair <int, pair <int, int> > > biggestBad;
        int p = 1;
        for (int i = k; i <= n; ++ i)
            biggestBad.push_back({0, {p ++, i}});
        compute(biggestBad, values, k);
    }
    return 0;
}