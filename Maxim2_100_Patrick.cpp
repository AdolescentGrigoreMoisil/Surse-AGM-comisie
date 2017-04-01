/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100
*/

#include <fstream>
#include <vector>
#include <cassert>
#include <iomanip>

using namespace std ;

const char IN[] = "maxim2.in" ;
const char OUT[] = "maxim2.out" ;
const int MAX = 1e5 ;

ifstream cin (IN) ;
ofstream cout (OUT) ;

bool isKnown (int x) {
	if (x == 0) {
		return false ;
	}
	return true ;
}

double bigger_than (int value, vector <int> &bigger, int unused_size) {
	return 1.0 * (bigger[value]) / (1.0 * (unused_size)) ;
}

double less_than (int value, vector <int> &less, int unused_size) {
	return 1.0 * (less[value]) / (1.0 * (unused_size)) ;
}

int main ()
{
	int n ;
	cin >> n ;
	assert (n >= 1 and n <= MAX) ;
	vector <int> v (n + 1) ;
	vector <int> fv (n + 1) ;
	vector <int> unused ;
	vector <int> bigger (n + 1) ; 
	vector <int> less (n + 1) ; 
	for (int i = 1 ; i <= n ; ++ i) {
		cin >> v [i] ;
		if (v[i] == 0) {
			continue ;
		}
		fv [v[i]] += 1 ;
		if (fv [v[i]] == 2) {
			cout << v [i] << '\n' ;
			return 0 ;
		}
		assert (fv [v[i]] <= 1) ;
	}
	for (int i = 1 ; i <= n ; ++ i) {
		if (fv [i]) {
			continue ;
		}
		else {
			unused.push_back(i) ;
			bigger [i] = 1 ; 
			less [i] = 1 ; 
			//printf ("%d\n", i) ;
		}
	}
	for (int i = 1 ; i <= n; ++ i) {
		less [i] += less [i - 1] ; 
	}
	for (int i = n - 1 ; i >= 1; -- i) {
		bigger[i] += bigger [i + 1] ; 
	}
	if (n == 1) {
		cout << fixed << setprecision(7) << 1.0 << '\n' ;
		return 0 ;
	}
	double Expected = 0 ;
	for (int i = 1 ; i <= n; ++ i) {
		if (i == 1) {
			if (isKnown(v[i])) {
				if (isKnown(v[i+1])) {
					if (v[i] > v[i + 1]) {
						Expected += 1.0 ;
					}
				}
				else {
					Expected += less_than (v[i], less, (int)unused.size()) ;
				}
			}
			else {
				if (isKnown(v[i+1])) {
					Expected += bigger_than (v[i + 1], bigger, (int)unused.size()) ;
				}
				else {
					Expected += 0.5 ; // C(total, 2) / (total * total)
				}
			}
		}
		else if (i == n) {
			if (isKnown(v[i])) {
				if (isKnown(v[i - 1])) {
					if (v[i - 1] < v[i]) {
						Expected += 1.0 ;
					}
				}
				else {
					Expected += less_than (v[i], less, (int)unused.size()) ;
				}
			}
			else {
				if (isKnown(v[i - 1])) {
					Expected += bigger_than (v[i - 1], bigger, (int)unused.size()) ;
				}
				else{
					Expected += 0.5 ;
				}
			}
		}
		else {
			if (isKnown (v[i])) {
				if (isKnown (v[i - 1])) {
					if (isKnown (v [i + 1])) {
						if (v[i] > v[i - 1] and v [i] > v[i + 1]) {
							Expected += 1.0 ;
						}
					}
					else {
						if (v [i] > v [i - 1]) {
							Expected += less_than (v[i], less, (int)unused.size()) ;
						}
					}
				}
				else {
					if (isKnown (v [i + 1])) {
						if (v[i + 1] < v [i]) {
							Expected += less_than (v[i], less, (int)unused.size()) ;
						}
					}
					else {
						int cate = less [v[i]] ;
						int total = (int)unused.size() ;
						Expected += ((1.0*(cate))/((total))) * ((1.0*(cate - 1))/(1.0*(total - 1)));
					}
				}
			}
			else {
				if (isKnown (v [i - 1])) {
					if (isKnown (v [i + 1])) {
						Expected += bigger_than (max(v[i - 1],v[i + 1]), bigger, (int)unused.size()) ;
					}
					else {
						int diff = bigger[v[i-1]] ;
						int cate = less [v[i-1]] ;
						double total = (int)unused.size() ;
						Expected += ((1.0 * diff) * (diff - 1)) / (2.0 * total * (total - 1)) ;
						Expected += ((1.0 * diff) * (1.0 * cate)) / (total * (total - 1)) ;
					}

				}
				else {
					if (isKnown (v [i + 1])) {
						int diff = bigger[v[i+1]] ;
						int cate = less [v[i+1]] ;
						double total = (int)unused.size() ;
						Expected += ((1.0 * diff) * (diff - 1)) / (2.0 * total * (total - 1)) ;
						Expected += ((1.0 * diff) * (1.0 * cate)) / (total * (total - 1)) ;;
					}
					else {
						Expected += 1.0 / 3.0 ;
					}
				}
			}
		}
		//cout << "Expected este " << fixed << setprecision (7) << Expected << '\n' ;
	}
	cout << fixed << setprecision (7) << Expected << '\n' ;
	return 0 ;
}
