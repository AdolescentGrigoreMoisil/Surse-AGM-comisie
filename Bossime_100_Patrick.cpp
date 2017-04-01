/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

#include <fstream>

using namespace std ;

ifstream cin ("bossime.in") ;
ofstream cout ("bossime.out") ;

int main()
{
	int t ; 
	cin >> t ; 
	while (t --) {
		long long a, b ; 
		cin >> a >> b ; 
		if (a % 9 != b % 9) {
			cout << "Imposibil\n" ; 
			continue ;
		}
		if (a < b) {
			swap (a, b) ;
		}
		long long diff = a - b ; 
		diff /= 9 ; 
		cout << (long long)(1e12) + diff - b << '\n' ; 
	}
	return 0 ; 
}