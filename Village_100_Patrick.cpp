/// Patrick Catalin Alexandru Sava
#include <iostream>
#include <cassert>
#include <vector>
#include <bitset>
#include <queue>

using namespace std;

//ifstream cin ("input");
//ofstream cout ("output");

const int MAX = 114;

int x [MAX];
int y [MAX];
int a [MAX][MAX];
int b [MAX][MAX];

int cap[MAX*4][MAX*4];
int flow[MAX*4][MAX*4];
vector <int> gr [MAX * 4];
int tata[MAX*4];

bitset <MAX*4> viz ;

inline int bfs (const int target)
{
    queue <int> queueFlow;
    viz.reset();
    queueFlow.push (0);

    while (!queueFlow.empty())
    {
        int nod = queueFlow.front();
        queueFlow.pop();
        if (nod == target)
            continue;
        for (auto x : gr [nod])
        {
            if (cap[nod][x] == flow [nod][x] or viz[x])
                continue;
            queueFlow.push(x);
            tata[x] = nod;
            viz[x] = 1;
        }
    }

    return viz [target];
}

int main() {
    int t;
    assert(cin >> t);
    assert(1 <= t and t <= 100);
    while (t --)
    {
        int n, m;
        assert(cin >> n >> m);
        assert(1 <= n and n <= 100);
        assert(1 <= m and m <= 100);
        for (int i = 1; i <= n; ++ i)
        {
            assert(cin >> x [i]);
            assert(-10000000 <= x [i] and x [i] <= 10000000);
        }
        for (int i = 1; i <= m; ++ i)
        {
            assert(cin >> y [i]);
            assert(-10000000 <= y [i] and y [i] <= 10000000);
        }
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= m; ++ j)
            {
                assert(cin >> a[i][j]);
                assert(-100000 <= a[i][j] and a[i][j] <= 100000);
            }
        }

        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= m; ++ j)
            {
                assert(cin >> b[i][j]);
                assert(-100000 <= b[i][j] and b[i][j] <= 100000);
            }
        }
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = 1; j <= m; ++ j)
            {
                b [i][j] -= a [i][j];
                x [i] -= a [i][j];
                y [j] -= a [i][j];
            }
        }
        const int lim = 4 * MAX;
        for (int i = 0; i < lim; ++ i) {
            for (int j = 0; j < lim; ++j)
                flow[i][j] = 0, cap[i][j] = 0;
            gr[i].clear();
        }

        for (int i = 1; i <= n; ++ i)
        {
            gr[0].push_back(i);
            gr[i].push_back(0);

            cap[0][i] = x [i];
        }
        for (int i = 1; i <= n; ++ i)
        {
            for (int j = n + 1; j <= n + m; ++ j)
            {
                gr [i].push_back(j);
                gr [j].push_back(i);

                cap[i][j] = b [i][j - n];
            }
        }

        for (int j = n + 1; j <= n + m; ++ j)
        {
            gr [j].push_back(n + m + 1);
            gr [n + m + 1].push_back(j);

            cap[j][n + m + 1] = y [j - n];
        }
        const int target = n + m + 1;
        while(bfs(target))
        {
            for (auto x : gr [target])
            {
                if (cap[x][target] == flow[x][target] or !viz[x])
                    continue;

                tata [target] = x;

                int local = 1 << 30 ;

                for (int i = target; i ; i = tata[i])
                    local = min (local, cap[tata[i]][i] - flow [tata[i]][i]);

                if ( local == 0 )
                    continue;

                for (int i = target; i ; i = tata[i])
                {
                    flow[tata[i]][i] += local;
                    flow[i][tata[i]] -= local;
                }
            }
        }
        for (int i = 1; i <= n; ++ i) {
            for (int j = 1; j <= m; ++j)
                cout << flow[i][n + j] + a[i][j] << ' ';
            cout << '\n';
        }
    }
    return 0;
}
