/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

#include <fstream>
#include <vector>
#include <cassert>

using namespace std ;

const char IN[] = "metrou5.in" ;
const char OUT[] = "metrou5.out" ;
const int MOD = 1e9 + 7 ;
const int MAX = 1e5 ;

ifstream cin (IN) ;
ofstream cout (OUT) ;

int put (int x, int y) {
	int ret = 1 ;
	for ( ;y; y >>= 1) {
		if (y & 1) {
			ret = 1LL * ret * x % MOD ;
		}
		x = 1LL * x * x % MOD ;
	}
	return ret ;
}

int comb (int x, int y, vector <int> &fact) {
	if (x < 0) return 0 ;
	if (y < 0) return 0 ;
	if (x < y) return 0 ;

	int aux = fact [x] ;
	int aux2 = put(fact [y], MOD - 2) ;
	int aux3 = put(fact [x - y], MOD - 2) ;
	aux2 = 1LL * aux2 * aux3 % MOD ;
	return 1LL * aux * aux2 % MOD ;
}

int main()
{
	int n , k ;
	cin >> n >> k ;
	assert (n >= 1 and n <= MAX) ;
	assert (k >= 1 and k <= MAX) ;
	vector <int> v (n + 2) ;
	for (int i = 1 ; i <= n ; ++ i) {
		cin >> v [i] ;
		assert (v [i] == -1 or (v[i] >= 1 and v [i] <= k)) ;
	}
	vector <int> fact (n + k + 2) ;
	fact [0] = 1 ;
	for (int i = 1 ; i <= n + k + 1 ; ++ i) {
		fact [i] = 1LL * fact [i - 1] * i % MOD ;
	}
	v [0] = 1 ;
	v [n + 1] = k ;
	int Solution = 1 ;
	int last = 0 ;
	for (int i = 1 ; i <= n ; ) {
        if (v [i] != -1) {
            if (last > v [i]) {
            	cout << 0 ;
            	return 0 ;
            }
            last = v [i] ;
             ++ i ;
            continue ;
        }
		int lo = v [i - 1] ; int start = i ;
		while (i <= n and v [i] == -1) {
			++ i ;
		}
		int hi = v [i] ;
		Solution = 1LL * Solution * comb (i - start + hi - lo, hi - lo, fact) % MOD ;
	}
	cout << Solution << '\n' ;
	return 0 ;
}
