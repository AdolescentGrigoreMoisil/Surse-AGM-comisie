#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

string buf;
vector<string> pats;
vector<int> final_sol;

constexpr ll mod = 9999991111111;
constexpr ll basis = 10007;

ll char_hash(char x){
    static bool b = false;
    static ll ret[256] = {};
    if(!b){
        b = true;
        ret['a'] = 1;
        for(auto ch = 'b'; ch <= 'z'; ++ch)
            ret[ch] = (ret[ch - 1] * basis)%mod;
    }

    return ret[x];
}

ll string_hash(string& s){
    ll ret = 0;
    for(auto x : s) ret = (ret + char_hash(x)) % mod;
    return ret;
}

void solve_len(int len, vector<int>& which){
    set<ll> which_set;
    for(auto x : which)
        which_set.insert(string_hash(pats[x]));

    map<ll, int> sol;

    ll curr = 0;
    for(int i = 0; i < len; ++i)
        curr = (curr + char_hash(buf[i])) % mod;

    ll nr = len;
    if(which_set.find(curr) != end(which_set)) sol[curr] = len;
    ll prev = curr;

    for(int i = len; i < buf.size(); ++i){
        if(buf[i] == buf[i-len])
            ++nr;
        else{
            curr = (curr + char_hash(buf[i]) - char_hash(buf[i-len]) + mod) % mod;
            nr = len;
        }

        if(which_set.find(curr) != end(which_set)) 
            sol[curr] = max<ll>(sol[curr], nr);
        prev = curr;
    }

    for(auto x : which)
        final_sol[x] = sol[string_hash(pats[x])];

}

void do_test(){
    buf.clear();
    pats.clear();
    final_sol.clear();

    cin >> buf;

    int nr;
    cin >> nr;
    pats.resize(nr);
    final_sol.resize(nr);

    for(auto& x : pats)
        cin >> x;

    map<int, vector<int>> by_size;

    for(int i =0 ; i < pats.size(); ++i)
        by_size[pats[i].size()].push_back(i);

    for(auto x : by_size)
        solve_len(x.first, x.second);

    for(int i = 0; i < pats.size(); ++i){
        cout << (final_sol[i] == 0 ? min(pats[i].size() - 1, buf.size()) : final_sol[i]) << '\n';
    }
}

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--) do_test();


    return 0;
}
