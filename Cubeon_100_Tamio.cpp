#include <bits/stdc++.h>
using namespace std;

using ll = long long;
constexpr ll mod = 1e9 + 7;

using cd = complex<double>;

constexpr ll maxn = 1e6 + 10;

ll n, k;
ll v[maxn], sp[maxn];
vector<ll> cur, nxt;

void precalc(){
    for(ll i = 1; i <= n; ++i)
        sp[i] = (sp[i-1] + v[i]);
}

ll cost(ll st, ll dr){
    assert(1 <= st);
    assert(st <= dr);
    assert(dr <= n);
    ll tmp = sp[dr] - sp[st-1];
    return (tmp * tmp * tmp + cur[st-1]);
}

ll bruteaza(ll x, ll prev_st, ll prev_dr){
    ll opt = prev_st;
    for(ll i = prev_st; i <= prev_dr && i <= x; ++i)
        if(cost(i, x) < cost(opt, x))
            opt = i;


    nxt[x] = cost(opt, x);
    return opt;
}

void divide(ll st, ll dr, ll prev_st, ll prev_dr){
    if(st > dr) return;

    ll mid = (st + dr) / 2;
    ll opt_mid = bruteaza(mid, prev_st, prev_dr);

    divide(st, mid - 1, prev_st, opt_mid);
    divide(mid + 1, dr, opt_mid, prev_dr);
}

void get_next_from_curr(){
    divide(1, n, 1, n);
}

void do_test(){
    cin >> n >> k;
    cerr  << '%' << n << ' ' << k << endl;
    for(ll i = 0; i < n; ++i)
        cin >> v[i+1];
    precalc();

    cur.resize(n+1, 0), nxt.resize(n+1, 0);
    fill(begin(cur), end(cur), 0);
    fill(begin(nxt), end(nxt), 0);

    for(ll i = 1; i <= n; ++i)
        cur[i] = cost(1, i);

    for(ll i = 2; i <= k; ++i){
        get_next_from_curr();
        swap(cur, nxt);
    }

    cout << (cur.back()) << endl;
}

int main(){
    ll t;
    cin >> t;

    while(t--)
        do_test();

   return 0;
}
