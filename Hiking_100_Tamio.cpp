#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

constexpr int maxn = 300000 + 10;

vector<int> vec[maxn];
int component_index[maxn] = {};
int coloring[maxn] = {};

void do_coloring(int curr, int color, int component){
    coloring[curr] |= color;
    component_index[curr] = component;

    color ^= 3;

    for(auto next : vec[curr]){
        if((coloring[next] | color) == coloring[next])
            continue;
        do_coloring(next, color, component);
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int n, m, q;
    cin >> n >> m >> q;

    assert(1 <= n && n <= 100000);
    assert(1 <= m && m <= 200000);
    assert(1 <= q && q <= 100000);
    

    int intermediates = n+1, curr_component = 1;
    for(int i = 0; i < m; ++i){
        int x, y, l;
        cin >> x >> y >> l;
        assert(1 <= x && x <= n);
        assert(1 <= y && y <= n);
        assert(1 <= l && l <= 1e9);
        assert(x != y);
        static set<pair<int, int>> p;
        assert(p.find(minmax(x, y)) == end(p));
        p.insert(minmax(x, y));

        if(l % 2 == 0){
            vec[x].push_back(intermediates);
            vec[y].push_back(intermediates);
            vec[intermediates].push_back(x);
            vec[intermediates].push_back(y);
            ++intermediates;
        }
        else{
            vec[x].push_back(y);
            vec[y].push_back(x);
        }
    }


    for(int i = 1; i <= n; ++i)
        if(coloring[i] == 0)
            do_coloring(i, 1, ++curr_component);

    for(int i = 0; i < q; ++i){
        int x, y, l;
        cin >> x >> y >> l;
        assert(1 <= x && x <= n);
        assert(1 <= y && y <= n);
        assert(l == 0 || l == 1);

        if(component_index[x] != component_index[y]){
            cout << 0 << '\n';
        }
        else if(coloring[x] == 3){
            cout << 1 << '\n';
        }
        else if(l == 0){
            cout << (coloring[x] == coloring[y]) << '\n';
        }
        else{
            cout << (coloring[x] != coloring[y]) << '\n';
        }
    }

    return 0;
}

