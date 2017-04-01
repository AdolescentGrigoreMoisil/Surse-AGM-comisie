/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

// Tractor sau Tractoras ?

#include <fstream>
#include <cstring>
#include <map>
#include <vector>
#include <cassert>

using namespace std ;

ifstream cin ("tst.in") ;
ofstream cout ("tst.out") ;

const int MAX = 5014 ;

char sir [MAX] ;

int main ()
{
	cin >> (sir + 1) ;
	int n = strlen (sir + 1) ;
	assert (n >= 1 and n <= 5000) ;
	vector <int> pi (n + 1, 0) ;
	vector <int> nearest (n + 1, n + 1) ;
	long long Solution = 0 ;
	for (int i = 1; i <= n; ++ i) {
		assert (sir [i] >= 'a' and sir [i] <= 'z') ;
		for (int j = 0 ; j <= n ; ++ j) {
			pi [j] = 0 ;
			nearest [j] = n + 1 ;
		}
		for (int j = i + 1; j <= n; ++ j) {
			int k = pi [j - 1] ;
			while (sir [i + k] != sir [j] and k) {
				k = pi [i + k - 1] ;
			}
			if (sir [i + k] == sir [j]) {
				++ k ;
			}
			pi [j] = k ;
		}
		for (int j = n ; j > i ; -- j) {
			nearest [i + pi [j] - 1] = j ;
		}
		for (int j = i + 1 ; j <= n ; ++ j) {
			if (sir [j] == sir [i]) {
				nearest [i] = j ;
				break ;
			}
		}
		for (int j = i ; j <= n ; ++ j) {
			Solution = Solution + 1LL * i * (nearest [j] - j) ;
			//cout << "secventa " << i << ' ' << j << " apare de " << 1LL * i * (nearest [j] - j) << '\n' ;
		}
	}
	cout << Solution << '\n' ;
	return 0 ; 
	long long Brute = 0 ;
	for (int i = 1 ; i <= n; ++ i) {
		for (int j = i ; j <= n ; ++ j) {
			map <string, int> H ;
			H.clear() ;
			for (int k = i ; k <= j ; ++ k) {
				string aux = "" ;
				for (int r = k ; r <= j ; ++ r) {
					aux += sir [r] ;
					H [aux] += 1 ;
				}
			}
			Brute += H.size() ;
		}
	}
	cout << Brute << '\n' ;
	return 0 ;
}
