#include <bits/stdc++.h>
using namespace std;

using ll = long long;
using cd = complex<double>;

int permut[6] = {1, 1, 2, 6, 24, 120};

string get_permut(int x){
    string s, avail = "abcde";
    for(int i = 4; i >= 0; --i){
        s.push_back(avail[x / permut[i]]);
        avail.erase(x / permut[i], 1);
        x %= permut[i];
    }
    return s;
}

void solve_3(int n, int k){
    string first_sol[5] = {
        "abc",
        "cde",
        "eab",
        "bcd",
        "dea",
    };

    string second_sol[5] = {
        "abc",
        "dea",
        "bcd",
        "eab",
        "cde",
    };

    vector<string> stub;

    for(int i = 0; i < 120; ++i){
        string str = get_permut(i);
        for(int which = 0; which < 2; ++which){
            string sss;
            for(int i = 0; i < 5 && i < n; ++i)
                for(auto x : (which ? second_sol : first_sol)[i])
                    sss.push_back(str[x - 'a']);
            stub.push_back(sss);
        }
    }

    sort(begin(stub), end(stub));

    stub.erase(
            unique(begin(stub), end(stub)),
            end(stub));


    if(stub.size() <= k){
        cout << -1 << endl;
        return;
    }
    auto x = stub[k];

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < 3; ++j)
            cout << stub[k][(3 * i + j) % stub[k].size()];
        cout << '\n';
    }
}


void solve_4(int n, int k){
    string first_sol[5] = {
        "abcd",
        "cdea",
        "eabc",
        "bcde",
        "deab",
    };

    string second_sol[5] = {
        "abcd",
        "deab",
        "bcde",
        "eabc",
        "cdea",
    };

    vector<string> stub;

    for(int i = 0; i < 120; ++i){
        string str = get_permut(i);
        for(int which = 0; which < 2; ++which){
            string sss;
            for(int i = 0; i < 5 && i < n; ++i)
                for(auto x : (which ? second_sol : first_sol)[i])
                    sss.push_back(str[x - 'a']);
            stub.push_back(sss);
        }
    }

    sort(begin(stub), end(stub));

    stub.erase(
            unique(begin(stub), end(stub)),
            end(stub));


    if(stub.size() <= k){
        cout << -1 << endl;
        return;
    }
    auto x = stub[k];

    for(int i = 0; i < n; ++i){
        for(int j = 0; j < 3; ++j)
            cout << stub[k][(3 * i + j) % stub[k].size()];
        cout << '\n';
    }

}

void solve_small(int n, int m, int k){
    if(m == 3)
        solve_3(n, k);

    if(m == 4)
        solve_4(n, k);
}

/*
 * abcde
 * cdeab
 * eabcd
 * bcdea
 * deabc
 */

int main(){
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while(t--){
        int n, m, k;
        cin >> n >> m >> k;

        if(k >= 240){
            cout << -1 << '\n';
            continue;
        }

        if(m == 3 || m == 4){
            solve_small(n, m, k);
            continue;
        }

        string str = get_permut(k / 2);

        int delta = 2;

        assert(str.size() == 5);
        if((k%2 == 1) == (str[delta] < str[5 - delta]))
            delta = 5 - delta;

        cerr << str << endl;

        for(int i = 0; i < n; ++i){
            for(int j = 0; j < m; ++j)
                cout << str[((j + delta * i) % 5 + 5)%5];
            cout << '\n';
        }
    }


    return 0;
}

