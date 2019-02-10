// Patrick Catalin Alexandru Sava
#include <iostream>
#include <vector>
#include <bitset>
#include <algorithm>
#include <cassert>

using namespace std;

const int MAX = 1e5 + 14;

vector <int> gr [MAX];
int level [MAX];
vector <int> sizes;

void dfs (int nod, int boss, int lvl)
{
    level [nod] = lvl;
    for (auto &x : gr [nod]) {
        if (x == boss) continue;
        if (level[x] == 0)
            dfs(x, nod, lvl + 1);
        else if (lvl + 1 > level [x])
            sizes.push_back(lvl + 1 - level[x]);
    }
}

const int MOD = 1e9 + 7;
int computeCase (int len, int k, int startValue)
{
    assert (startValue == k or startValue == k - 1);
    if (len == 1)
        return startValue;
    vector <int> powers;
    int put = startValue;
    for (int i = 2; i <= len; ++ i)
    {
        put = static_cast<int>(1LL * put * (k - 1) % MOD);
        powers.push_back(put);
    }
    reverse(powers.begin(), powers.end());
    int sign = 1;
    int ans = 0;
    for (auto &x : powers)
    {
        ans = static_cast<int>((ans + 1LL * x * sign % MOD + MOD) % MOD);
        sign *= -1;
    }
    return ans;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    cin >> t;
    while (t --)
    {
        int n, m, q;
        cin >> n >> m >> q;
        for (int i = 1; i <= n; ++ i)
        {
            gr [i].clear();
            level [i] = 0;
        }
        sizes.clear();

        while (m --)
        {
            int x, y;
            cin >> x >> y;
            gr [x].push_back(y);
            gr [y].push_back(x);
        }

        dfs (1, -1, 1);
        int s = 0;
        for (auto i : sizes) {
            s += i;
        }
        s = n - s;
        while (s --)
            sizes.push_back(1);
        while (q --)
        {
            int k;
            cin >> k;
            int p = 0;
            int ans = computeCase(sizes[p ++], k, k);
            while(p < sizes.size())
                ans = static_cast<int>(1LL * ans * computeCase(sizes[p ++], k, k - 1) % MOD);
            cout << ans << '\n';
        }
    }
    return 0;
}
