/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

#include <fstream>
#include <vector>
#include <algorithm>

using namespace std ;

ifstream cin ("rgb.in") ;
ofstream cout ("rgb.out") ;

int main()
{
	int t ;
	cin >> t ;
	while (t --) {
		int a, b, c , dist ;
		vector <string> cba ;
		vector <int> positions [3] ;
		vector <int> sorted ;
		cba.clear() ;
		cin >> a >> b >> c ;
		sorted.clear() ;
		sorted.push_back(a) ;
		sorted.push_back(b) ;
		sorted.push_back(c) ;
		sort (sorted.begin(), sorted.end()) ;
		int aa = sorted[0] ;
		int bb = sorted[1] ;
		int cc = sorted[2] ;
		while (aa --) {
            -- bb ;
            -- cc ;
			cba.push_back ("cba") ;
		}
		int i = 0 ;
		while (bb --) {
			cc -- ;
			if (i == (int)cba.size()) {
				goto stop ;
			}
			cba [i] += "cb" ;
			i += 1 ;
		}
		while (cc --) {
			if (i == (int)cba.size()) {
				goto stop ;
			}
			cba [i] += "c" ;
			i += 1 ;
		}
		positions [0].clear() ;
		positions [1].clear() ;
		positions [2].clear() ;
		dist = 0 ;
		for (auto x : cba) {
			for (auto y : x) {
				positions [y - 'a'].push_back (++ dist) ;
			}
			dist += 10000 ;
		}
		i = 0 ;
		repeat :
		if (a == positions[i].size()) {
			for (auto x : positions [i]) {
				cout << x << ' ' ;
			}
			cout << '\n' ;
			positions [i].clear() ;
		}
		else {
			++ i ;
			goto repeat ;
		}
		i = 0 ;
		repeat2 :
		if (b == positions[i].size()) {
			for (auto x : positions [i]) {
				cout << x << ' ' ;
			}
			cout << '\n' ;
			positions [i].clear() ;
		}
		else {
			++ i ;
			goto repeat2 ;
		}
		i = 0 ;
		repeat3 :
		if (c == positions[i].size()) {
			for (auto x : positions [i]) {
				cout << x << ' ' ;
			}
			cout << '\n' ;
		}
		else {
			++ i ;
			goto repeat3 ;
		}
		//cout << "===============================================\n" ;
		continue ;
		stop :
		cout << -1 << '\n' ;
		//cout << "===============================================\n" ;
	}
	return 0 ;
}
