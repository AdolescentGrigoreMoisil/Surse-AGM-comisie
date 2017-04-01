#include <bits/stdc++.h>
 
using namespace std;
 
int x[100010];
int fact[200100];
int inv[200100];
 
struct special {
    int pos;
    int val;
} p[100010];
 
const int mod = 1e9 + 7;
 
int fastPow(int A, int B) {
    if (B == 0)
        return 1;
    int res = fastPow(A, B / 2);
    res = (long long) res * res % mod;
    if (B % 2)
        res = (long long) res * A % mod;
    return res;
}
 
void init() {
    fact[0] = 1;
    for (int i = 1; i <= 200000; ++i)
        fact[i] = (long long) fact[i - 1] * i % mod;
 
    inv[200000] = fastPow(fact[200000], mod - 2);
    for (int i = 199999; i >= 0; --i)
        inv[i] = (long long) inv[i + 1] * (i + 1) % mod;
}
 
int comb(int n, int k) {
    int res = fact[n];
    res = (long long) res * inv[k] % mod;
    res = (long long) res * inv[n - k] % mod;
    return res;
}
 
int solve(int k, int n) {
   return comb(n + k - 1, k - 1);
}
 
int main() {
    freopen("metrou5.in", "r", stdin);
    freopen("metrou5.out", "w", stdout);
 
    int n, k;
    scanf("%d%d", &n, &k);
    for (int i = 1; i <= n; ++i)
        scanf("%d", &x[i]);
 
    init();
    x[0] = 1;
    x[n + 1] = k;
    int cnt = 0;
    for (int i = 0; i <= n + 1; ++i)
        if (x[i] != -1) {
            ++cnt;
            p[cnt].pos = i;
            p[cnt].val = x[i];
        }
    for (int i = 1; i < cnt; ++i)
        if (p[i + 1].val < p[i].val) {
            printf("0");
            return 0;
        }
    int res = 1;
    for (int i = 1; i < cnt; ++i) {
        int alfabet = p[i + 1].val - p[i].val + 1;
        int places = p[i + 1].pos - p[i].pos - 1;
        res = (long long) res * solve(alfabet, places) % mod;
    }
    printf("%d", res);
    return 0;
}