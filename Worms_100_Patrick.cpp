/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

#include <fstream>
#include <iomanip>
#include <cmath>
#include <queue>
#include <stack>
#include <algorithm>
#include <cassert>

using namespace std ;

ifstream cin ("worms.in") ;
ofstream cout ("worms.out") ;

const int eps = 1e-9 ; 

class Poli {
	public :
	Poli () {
		poli.resize(8) ;
	}
	void Set (int x, int y) {
		poli [x] = y ; 
		assert (poli [x] >= 0 and poli [x] <= 10) ;
	}
	void Inc (int x) {
		poli [x] += 1 ;
		if (x)
			assert (poli [x] >= 0 and poli [x] <= 10) ;
		else assert (poli [x] >= 0 and poli [x] <= 11) ;
	}
	double Root () 
	{
		double st = -10 ; 
		double dr = 10 ; 
		double sol ;
		int bulan = 50 ;
		while (bulan --) {
			double mij = (st + dr) / 2.0 ;
			if (eval(mij) < eps) {
				st = mij ;  
			}
			else {
				dr = mij ;
			}
			sol = mij ;
		}
		return sol ; 
	}
	private :
	vector <int> poli ; 
	double eval (double x) {
		double put = 1 ;
		double S = 0 ; 
		for (auto y : poli) {
			S = S + put * y ;
			put = put * x ;
		}
		return S ;
	}
};

void Dfs (int n, vector <int> *&gr, vector <int> &grad, vector <double> *&values) {
	queue <int> Q ;
	for (int i = 1 ; i <= n; ++ i) {
		if (grad [i] <= 5) {
			Q.push(i) ; 
		}
	}
	assert (!Q.empty()) ;
	stack <int> S ; 
	S.push (Q.front()) ;
	Q.pop() ;
	vector <bool> inQ (n + 1, false) ;
	vector <int> *Down = new vector <int> [n + 1] ; 
	vector <double> Solution (n + 1) ; 
	vector <bool> Erased (n + 1, false) ;
	while (!S.empty()) {
		int node = S.top() ; 
		Erased [node] = true ; 
		bool entered = false ;
		for (auto x : gr [node]) {
			if (Erased [x] == true) {
				continue ; 
			}
			else {
				Down [node].push_back (x) ;
				-- grad [x] ; 
				if (grad [x] <= 5 and inQ [x] == false) {
					Q.push (x) ;
					inQ [x] = true ;
				}
			}
		}
		if (!Q.empty()) {
			S.push (Q.front()) ;
			Q.pop () ;
			entered = true ; 
		}
		if (entered == true) {
			continue ; 
		}
		else {
			S.pop() ; 
			if (Down [node].size() == 0) {
			    random_shuffle(values [node].begin(), values [node].end()) ;
				Solution [node] = values [node][0] ; 
			}
			else {
				for (auto x: values [node]) {
					bool found = false ; 
					for (auto y : Down [node]) {
						if (fabs (Solution[y] - x) <= eps) {
							found = true ; 
							break ; 
						}
					}
					if (found == false) {
						Solution [node] = x ; 
						break ; 
					}
				}
			}
		}
	}
	for (int i = 1 ; i <= n ; ++ i) {
		cout << fixed << setprecision (10) << Solution [i] << '\n' ; 
		assert (Erased [i] == true) ;
	}
}

int main()
{
	Poli *P = new Poli () ;
	for (int i = 0; i < 8 ; ++ i) {
		int x ; 
		cin >> x ;
		P -> Set (i, x) ;
	}
	P -> Inc (0) ;
	int n, m ; 
	cin >> n >> m ; 
	assert (n >= 1 and n <= 10000) ; 
	assert (m >= 1 and m <= 30000) ;
	vector <int> *gr = new vector <int> [n + 1] ; 
	vector <int> grad (n + 1, 0) ; 
	while (m --) {
		int x, y ; 
		cin >> x >> y ; 
		assert (x >= 1 and x <= n) ; 
		assert (y >= 1 and y <= n) ;
		gr [x].push_back (y) ; 
		gr [y].push_back (x) ;
		grad [x] += 1 ; 
		grad [y] += 1 ;
	}
	int q ; 
	cin >> q ; 
	double value = P -> Root() ;
	//cout << fixed << setprecision(10) << value << '\n' ; 
	vector <double> *values = new vector <double> [n + 1] ; 
	while (q --) {
		int type ; 
		cin >> type ; 
		if (type == 1) {
			int x ; 
			cin >> x ;
			assert (x >= 0 and x <= 3) ;
			P -> Inc (x << 1) ;
			value = P -> Root () ;
			//cout << fixed << setprecision(10) << value << '\n' ; 
		}
		else {
			int node ; 
			cin >> node ; 
			assert (node >= 1 and node <= n) ; 
			values[node].push_back (value) ;
		}
	}
	Dfs (n, gr, grad, values) ;
	return 0;
}