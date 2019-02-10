/// Patrick Catalin Alexandru Sava
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

//ifstream cin ("input");
//ofstream cout ("output");

const int MAX = 23;
int a[MAX];
const int MOD = 1e9 + 7;

int **newOne()
{
    int** result = new int*[MAX];
    for (int i = 0; i < MAX; ++ i)
        result[i] = new int[MAX];
    return result;
}

int** multiplication(const int n, const int m, int** term1, const int q, int** term2)
{
    int** result = newOne();
    for (int i = 1; i <= n; ++ i)
        for (int j = 1; j <= q; ++ j)
            result[i][j] = 0;
    for (int i = 1; i <= n; ++ i)
    {
        for (int j = 1; j <= q; ++ j)
        {
            for (int r = 1; r <= m; ++ r) {
                result[i][j] += static_cast<int>(1LL * term1[i][r] * term2[r][j] % MOD);
                if (result[i][j] >= MOD)
                    result[i][j] -= MOD;
            }
        }
    }
    return result;
}

int** exponentiation (const int k, int** term1, long long power)
{
    int **result = newOne();
    for (int i = 1; i <= k; ++ i) {
        for (int j = 1; j <= k; ++ j)
            result[i][j] = 0;
        result[i][i] = 1;
    }
    for (; power; power >>= 1)
    {
        if (power & 1LL)
            result = multiplication(k, k, result, k, term1);
        term1 = multiplication(k, k, term1, k, term1);
    }

    return result;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int t;
    assert(cin >> t);
    while (t --)
    {
        int k, Q;
        assert(cin >> k >> Q);
        for (int i = 1; i <= k; ++i)
            assert(cin >> a[i]);
        int **p = new int *[MAX];
        for (int i = 0; i < MAX; ++i)
            p[i] = new int[3];
        for (int i = 1; i <= k; ++i)
            assert(cin >> p[i][1]);
        int **matrix = newOne();
        for (int i = 1; i < k; ++i) {
            for (int j = 1; j <= k; ++j)
                matrix[i][j] = 0;
            matrix[i][i + 1] = 1;
        }
        for (int j = 1; j <= k; ++j)
            matrix[k][j] = a[k - j + 1];
        vector<int **> matrices(65);
        for (int bit = 0; bit <= 60; ++bit)
            matrices[bit]= exponentiation(k, matrix, (1LL << bit));
        while (Q--) {
            long long put;
            assert(cin >> put);
            int **ret = new int *[MAX];
            for (int i = 0; i < MAX; ++i)
                ret[i] = new int[3];
            for (int i = 1; i <= k; ++i)
                ret[i][1] = p[i][1];
            --put;
            for (int bit = 0; bit <= 60; ++bit)
                if (put & (1LL << bit)) {
                    int **keep = ret;
                    ret = multiplication(k, k, matrices[bit], 1, ret);
                    for (int j = 0; j < MAX; ++ j)
                        delete keep[j];
                    delete keep;
                }
            cout << ret[1][1] << '\n';
        }
    }
    return 0;
}