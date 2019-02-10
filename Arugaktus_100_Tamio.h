#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

constexpr ll mod = 1e9 + 7;

ll lgput(ll x, ll y){
    assert(y >= 0);
    ll r = 1;
    while(y){
        if(y%2) r = (r * x) % mod;
        y /= 2;
        x = (x * x) % mod;
    }
    return r;
}

ll inv_mod(ll x){
    return lgput(x, mod - 2);
}

ll get_cycle_solution(ll k, ll sz){
    ll ret = (lgput(mod-1, sz) * (1 - inv_mod(k) + mod)) % mod;

    ret += (inv_mod(k) * lgput(k-1, sz))%mod;
    ret %= mod;

    ret *= (k-1);
    ret %= mod;

    return ret;
}

constexpr int maxn = 1e5 + 10;
int n, m;
vector<int> vec[maxn] = {};
int depth[maxn] = {};

vector<int> cycles;

void dfs(int curr){
    for(auto next : vec[curr]){
        if(depth[next] == depth[curr] - 1 || depth[next] > depth[curr]);
        else if(depth[next])
            cycles.push_back(depth[curr] - depth[next] + 1);
        else{
            depth[next] = depth[curr] + 1;
            dfs(next);
        }
    }
}

void precalc(){
    memset(depth, 0, sizeof(depth));
    cycles.clear();

    depth[1] = 123;
    dfs(1);
}

int solve_for_k(int k){
    int nr_out = n;
    ll ret = 1;
    for(auto x : cycles)
        ret = (ret * get_cycle_solution(k, x)) % mod,
        nr_out -= x;
    ret = (ret * lgput(k-1, nr_out)) % mod;

    ret = (ret * k) % mod;
    ret = (ret * inv_mod(k-1)) % mod;
    return ret;
}

void do_test(){
    int q;
    cin >> n >> m >> q;

    for(int i = 0, x, y; i < m; ++i)
        cin >> x >> y,
        vec[x].push_back(y),
        vec[y].push_back(x);

    precalc();

    for(int i = 0, k; i < q; ++i)
        cin >> k,
        cout << solve_for_k(k) << '\n';

    for(int i = 1; i <= n; ++i)
        vec[i].clear();
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);


    int t;
    cin >> t;
    while(t--)
        do_test();

    return 0;
}

