/*Patrick Catalin Alexandru Sava
Atooom Industry and Resources SRL
University of Bucharest
Expected : 100*/

#include <fstream>
#include <vector>
#include <cassert>

using namespace std ;

const char IN[] = "simulare.in" ;
const char OUT[] = "simulare.out" ;
const int NMAX = 2014 ;
const int GMAX = 1014 ;

ifstream cin (IN) ;
ofstream cout (OUT) ;

void Dfs1 (int node, int tata, vector <int> *&gr, vector <int> &subtree, vector<bool> &visited) {
	subtree [node] = 1 ;
	for (auto x: gr[node]) {
		if (visited [x] == false and x != tata) {
			Dfs1 (x, node, gr, subtree, visited) ;
			subtree [node] += subtree [x] ;
		}
	}
}

int Centroid (int node, int tata, int target, vector <int>*&gr, vector <int> &subtree, vector <bool> &visited) {
	int sumOfSons = 0 ;
	bool ok = true ;
	for (auto x: gr[node]) {
		if (x == tata or visited [x] == true) {
			continue ;
		}
		int rec = Centroid (x, node, target, gr, subtree, visited) ;
		if (rec) {
			return rec ;
		}
		if (subtree [x] > target / 2 + 1) {
			ok = false ;
		}
		sumOfSons += subtree [x] ;
	}
	if (ok == false or target - sumOfSons > target / 2 + 1) {
		return 0 ;
	}
	return node ;
}

void Dfs2 (int node, int tata, int current_centroid, vector <int> *gr, vector <bool> &visited,
	vector <int> *&rootsOfNode, vector <pair<int, int>> &Obj, vector <vector<int>> *&dp) {
	rootsOfNode[node].push_back (current_centroid) ;
	dp[node].push_back (vector <int> (GMAX)) ;
	for (int i = 0; i < GMAX; ++ i) {
		dp [node].back()[i] = dp [tata].back()[i] ;
	}
	for (int i = GMAX - 1; i >= 0 ; -- i) {
		if (Obj[node].second + i < GMAX) {
			dp [node].back()[Obj[node].second + i] = max (dp [node].back()[Obj [node].second + i], dp[node].back()[i] + Obj[node].first);
		}
	}
	for (auto x: gr [node]) {
		if (tata != x and visited [x] == false) {
			Dfs2 (x, node, current_centroid, gr, visited, rootsOfNode, Obj, dp) ;
		}
	}
}

void Solver (int node, vector <int> *&gr, vector <int> &subtree, vector <bool> &visited,
	vector <int> *&rootsOfNode, vector <pair<int, int>> &Obj, vector <vector<int>> *&dp) {
	Dfs1 (node, 0, gr, subtree, visited) ;
	int centr = Centroid (node, 0, subtree[node], gr, subtree, visited) ;
	rootsOfNode[centr].push_back (centr) ;
	dp[centr].push_back (vector <int> (GMAX)) ;
	for (auto x: gr [centr]) {
		if (visited [x] == false) {
			Dfs2 (x, centr, centr, gr, visited, rootsOfNode, Obj, dp) ;
		}
	}
	visited[centr] = true;
	for (auto x: gr [centr]) {
		if (visited [x] == false) {
			Solver (x, gr, subtree, visited, rootsOfNode, Obj, dp) ;
		}
	}
}

int main()
{
	int n, m ;
	cin >> n >> m ;
	assert (n >= 1 and n <= 2000) ;
	assert (m >= 1 and m <= 20000) ;
	vector <pair<int, int>> Obj (n + 1) ;
	vector <int> *gr = new vector <int> [n + 1] ;
	vector <bool> visited (n + 1, false) ;
	vector <int> subtree (n + 1, 0) ;
	vector <int> *rootsOfNode = new vector <int> [n + 1] ;
	vector <vector<int>> *dp = new vector <vector<int>> [n + 1] ;
	for (int i = 1 ; i <= n; ++ i) {
		int deal, weight ;
		cin >> deal >> weight ;
		assert (deal >= 1 and deal <= 1000000) ; 
		assert (weight >= 1 and weight <= 1000) ; 
		Obj[i] = make_pair (deal, weight) ;
	}
	for (int i = 1 ; i < n; ++ i) {
		int x, y ;
		cin >> x >> y ;
		assert (x >= 1 and x <= n) ;
		assert (y >= 1 and y <= n) ;
		gr[x].push_back(y) ;
		gr[y].push_back(x) ;
	}
	Solver (1, gr, subtree, visited, rootsOfNode, Obj, dp) ;
	vector <int> bestsuff ;
	while (m --) {
		int x, y, g ;
		cin >> x >> y >> g ;
		assert (x >= 1 and x <= n) ;
		assert (y >= 1 and y <= n) ;
		assert (g >= 1 and g <= 1000) ;
		bestsuff.resize(g + 1) ;
		fill(bestsuff.begin(), bestsuff.end(), 0) ;
		if (x == y) {
			if (Obj[x].second > g) {
				cout << 0 << '\n' ;
			}
			else {
				cout << Obj[x].first << '\n' ;
			}
			continue ;
		}
		else {
			for (int i = 0; ;) {
				if (i < rootsOfNode[x].size() and i < rootsOfNode[y].size() and rootsOfNode [x][i] == rootsOfNode [y][i]) {
					++ i ;
				}
				else {
					-- i ;
					int Solution = 0 ;
					for (int j = 0; j <= g; ++ j) {
						bestsuff [j] = max (bestsuff [(((j-1)>=0)?(j-1):(0))], dp[x][i][j]) ;
					}
					for (int fixed_weight = 0; fixed_weight <= g; ++ fixed_weight) {
						int max_diff = g - fixed_weight ;
						Solution = max (Solution, dp [y][i][fixed_weight] + bestsuff [max_diff]) ;
					}
					for (int fixed_weight = 0; fixed_weight <= g; ++ fixed_weight) {
						int max_diff = g - fixed_weight - Obj[rootsOfNode[x][i]].second ;
						if (max_diff < 0) {
							continue ; 
						}  
						Solution = max (Solution, dp [y][i][fixed_weight] + bestsuff [max_diff] + Obj[rootsOfNode[x][i]].first) ;
					}
					cout << Solution << '\n' ;
					goto jump ;
				}
			}
		}
		jump :
			continue ;
	}
	return 0 ;
}
