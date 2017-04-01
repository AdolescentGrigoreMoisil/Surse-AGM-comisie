/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL 
University of Bucharest
Expected : 100*/

#include <fstream>
#include <vector>
#include <cassert>
#include <unordered_map>

using namespace std ;

const char IN [] = "arduino.in" ;
const char OUT [] = "arduino.out" ; 
const long long MOD = 1e9 + 7 ; 

ifstream cin (IN) ;
ofstream cout (OUT) ;

unsigned long long Solve (vector <int> &partial_sol, vector <pair<pair<int, int>, vector<int>>> &restrictions, int n, int m, int sim, int cur_lvl) {
	if (cur_lvl == n) {
		unordered_map <int, int> H ;
		for (auto x : restrictions) {
			H.clear() ;
			for (auto y: x.second) {
				H[partial_sol[y-1]] += 1 ;
			}
			if (H.size() != x.first.first) {
				return 0 ; 
			}
		}
		H.clear() ;
		for (auto x: partial_sol) {
			H [x] += 1 ;
		}
		/*for (auto x: partial_sol) {
			cout << x << ' ' ; 
		}
		cout << "\n====================================\n" ;
		*/int k = H.size() ; 
		unsigned long long sol = 1 ; 
		int mcur = m ;
		while (k --) {
			sol = 1LL * sol * mcur % MOD ;
			mcur -= 1 ;
		}
		//cout << "sol este " << sol << '\n' ;
		return sol ; 
	}
	unsigned long long S = 0 ;
	for (int i = 1; i <= sim + 1; ++ i) {
		partial_sol[cur_lvl] = i;
		if (i <= sim)
			S += Solve (partial_sol, restrictions, n, m, sim, cur_lvl + 1) ;
		else S += Solve (partial_sol, restrictions, n, m, sim + 1, cur_lvl + 1) ;
		S %= MOD ; 
	}
	return S ;
}

long long BackForDummies (vector <int> &partial_sol, vector <pair<pair<int, int>, vector<int>>> &restrictions, int n, int m, int cur_lvl) {
	if (cur_lvl == n) {
		unordered_map <int, int> H ; 
		for (auto x : restrictions) {
			H.clear() ; 
			for (auto y : x.second) {
				H [partial_sol[y-1]] += 1 ;
			}
			if (H.size() != x.first.first) return 0 ; 
		}
		return 1 ;
	}
	long long S = 0 ;
	for (int i = 1; i <= m; ++ i) {
		partial_sol [cur_lvl] = i ; 
		S = S + BackForDummies (partial_sol, restrictions, n, m, cur_lvl + 1) ;
		S %= MOD ;
	}
	return S ;
}

int main() {
	/*vector <int> dp [11] ;
	for (int i = 0; i <= 10; ++ i) {
		dp [i].resize(11) ;
	}
	dp [1][1] = 1 ; 
	for (int i = 2; i <= 10; ++ i) {
		for (int j = 1; j <= i; ++ j) {
			dp [i][j] = dp [i - 1][j - 1] + dp [i - 1][j] * j ;
		}
	}
	for (int i = 1; i <= 10; ++ i) {
		for (int j = 1; j <= 10; ++ j) {
			cout << dp [i][j] << ' ' ;
		}
		cout << '\n' ;
	}*/
	int n, m ;
	cin >> n >> m ;
	assert (n >= 1 and n <= 10) ; 
	assert (m >= 1 and m <= 1000) ;
	int res ;
	cin >> res ;
	assert (res >= 1 and res <= 100) ; 
	vector <pair<pair<int, int>, vector<int>>> restrictions ;
	restrictions.resize (res) ; 
	int S = 0 ; 
	for (int i = 0; i < res; ++ i) {
		int nr ; 
		cin >> nr ; 
		int k ; 
		cin >> k ;
		restrictions[i].second.resize (k) ;
		for (int j = 0; j < k; ++ j) {
			cin >> restrictions[i].second[j] ;
		}
		restrictions[i].first = make_pair (nr, k) ;
		S += k ; 
		assert (S <= 100 and S >= 0) ;
	}
	vector <int> partial_sol ;
	partial_sol.resize(n) ;
	//cout << BackForDummies (partial_sol, restrictions, n, m, 0) << '\n' ;
	cout << Solve (partial_sol, restrictions, n, m, 0, 0) << '\n' ;
	//assert (BackForDummies (partial_sol, restrictions, n, m, 0) == Solve (partial_sol, restrictions, n, m, 0, 0)) ;
	return 0 ;
}
