/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

#include <fstream>
#include <vector>
#include <cassert>

using namespace std ;

ifstream cin ("treap.in") ;
ofstream cout ("treap.out") ;

const int MAXNODES = 150000 ;
const int MAXX = (1e6) + (1e5) ;
const int MAXPRIORITY = 1e9 ;
const int MAXKEY = 1e9 ;

void Dfs (int node, int father, vector <int> *&gr, vector <bool> &viz, vector <int> &prio, vector <int> &key, vector <bool> &dp, vector <int> &less_than, vector <int> &bigger_than){
	viz [node] = true ;
	int sons = 0 ;
	for (auto x : gr [node]) {
		if (viz [x] == false) {
			sons += 1 ;
			Dfs (x, node, gr, viz, prio, key, dp, less_than, bigger_than) ;
		}
	}
	if (sons == 0) {
		dp [node] = true ;
		less_than [node] = key [node] ;
		bigger_than [node] = key [node] ;
	}
	else {
		dp [node] = true ;
		int bigger = 0 ;
		int less_or_equal = 0 ;
		int maxim = 0 ;
		int minim = 1e9 ;
		for (auto x : gr [node]) {
			if (x == father) {
				continue ;
			}
			if (dp [x] == false) {
				dp [node] = false ;
			}
			if (prio [x] > prio [node]) {
				dp [node] = false ;
			}
			if (key [x] > key [node] and less_than [x] > key [node]) {
				bigger += 1 ;
			}
			if (key [x] <= key [node] and bigger_than [x] <= key [node]) {
				less_or_equal += 1 ;
			}
			maxim = max (bigger_than [x], maxim) ;
			minim = min (less_than [x], minim) ;
		}
		if (less_or_equal == 2 or bigger == 2 or (sons != less_or_equal + bigger)) {
			dp [node] = false ;
		}
		bigger_than [node] = max (maxim, bigger_than [node]) ;
		less_than [node] = min (minim, less_than [node]) ;
		less_than [node] = min (less_than [node], key [node]) ;
		bigger_than [node] = max (bigger_than [node], key [node]) ;
	}
}

int main()
{
	int n ;
	cin >> n ;
	assert (n >= 1 and n <= MAXNODES) ;
	vector <int> *gr = new vector <int> [n + 1] ;
	int edges = n - 1 ;
	while (edges --) {
		int x, y ;
		cin >> x >> y ;
		assert (x >= 1 and x <= MAXNODES) ;
		assert (y >= 1 and y <= MAXNODES) ;
		gr [x].push_back (y) ;
		gr [y].push_back (x) ;
	}
	vector <bool> viz (n + 1, false) ;
	vector <int> key (n + 1) ;
	vector <int> prio (n + 1) ;
	vector <int> less_than (n + 1, 1e9) ;
	vector <int> bigger_than (n + 1, 0) ;
	for (int i = 1 ; i <= n ; ++ i) {
		int x ;
		cin >> x ;
		assert (x >= 1 and x <= MAXKEY) ;
		key [i] = x ;
	}
	for (int i = 1 ; i <= n ; ++ i) {
		int x ;
		cin >> x ;
		assert (x >= 1 and x <= MAXPRIORITY) ;
		prio [i] = x ;
	}
	vector <bool> dp (n + 1, false) ;
	Dfs (1, 0, gr, viz, prio, key, dp, less_than, bigger_than) ;
	for (int i = 1 ; i <= n ; ++ i) {
		if (i != n)
			cout << (int)dp[i] << ' ' ;
		else
			cout << (int)dp[i] << '\n' ;
	}
	return 0 ;
}
