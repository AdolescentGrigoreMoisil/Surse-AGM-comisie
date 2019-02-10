#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

ll mod = 1e9 + 7;

template <ll n, ll m>
struct mat{
    ll buf[n][m] = {};

    template <ll k>
    mat<n, k> operator*(mat<m, k>& rhs){
        mat<n, k> ret;
        for(ll i = 0; i < n; ++i)
            for(ll j = 0; j < m; ++j)
                for(ll l = 0; l < k; ++l)
                    ret[i][l] = (ret[i][l] + (*this)[i][j] * rhs[j][l]) % mod;
        return ret;
    }

    ll* operator[](ll x){
        return buf[x];
    }
};

template <ll n>
mat<n, n> from_thing(vector<ll> v){
    reverse(begin(v), end(v));
    mat<n, n> ret;

    for(ll i = 0; i < n-1; ++i){
        ret.buf[i][i + 1] = 1;
    }

    for(ll j = 0; j < n; ++j)
        ret[n-1][j] = v[j];

    return ret;
}

template <ll k>
void solve(vector<ll> v, vector<ll> init, vector<ll> queries){
    mat<k, k> buf[60] = {};
    buf[0] = from_thing<k>(v);
    for(ll i = 1; i < 60; ++i){
        buf[i] = (buf[i-1] * buf[i-1]);
    }

    mat<k, 1> col;

    for(ll i = 0; i < k; ++i)
        col.buf[i][0] = init[i];

    for(auto x : queries){
        if(x <= k){
            cout << (init[x-1] % mod) << endl;
            continue;
        }

        x = x - k;

        auto ret = col;

        for(ll i = 0; i < 60; ++i)
            if(x & (1ll<<i)){
                ret = (buf[i] * ret);
                const int niv= i;
            }

        cout << ret[k-1][0] << endl;
    }
}

int main(){
    int t;
    cin >> t;

    while(t--){
        int k, q;
        cin >> k >> q;
        vector<ll> v(k);
        vector<ll> init(k);
        vector<ll> queries(q);
        for(auto & x : v) cin >> x;
        for(auto & x : init) cin >> x;
        for(auto & x : queries) cin >> x;

        if(k == 1) solve<1>(v, init, queries);
        if(k == 2) solve<2>(v, init, queries);
        if(k == 3) solve<3>(v, init, queries);
        if(k == 4) solve<4>(v, init, queries);
        if(k == 5) solve<5>(v, init, queries);
        if(k == 6) solve<6>(v, init, queries);
        if(k == 7) solve<7>(v, init, queries);
        if(k == 8) solve<8>(v, init, queries);
        if(k == 9) solve<9>(v, init, queries);
        if(k == 10) solve<10>(v, init, queries);
        if(k == 11) solve<11>(v, init, queries);
        if(k == 12) solve<12>(v, init, queries);
        if(k == 13) solve<13>(v, init, queries);
        if(k == 14) solve<14>(v, init, queries);
        if(k == 15) solve<15>(v, init, queries);
        if(k == 16) solve<16>(v, init, queries);
        if(k == 17) solve<17>(v, init, queries);
        if(k == 18) solve<18>(v, init, queries);
        if(k == 19) solve<19>(v, init, queries);
        if(k == 20) solve<20>(v, init, queries);
    }
    return 0;
}
