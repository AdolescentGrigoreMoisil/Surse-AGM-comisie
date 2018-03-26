/*Patrick Catalin Alexandru Sava
The University of Manchester
Expected : Accepted
Complexity : O(T * N * log(N))*/
 
#include <bits/stdc++.h>
 
using namespace std;
 
int main() {
    ifstream fin ("cbinput.in");
    ofstream fout ("cbinput.out");
    const int NMAX = 1000;
    const int KMAX = 1000;
    const int TMAX = 100;
    const int NOTUSED = -1;
    auto isBetween = [](int A, int B, int C) -> bool {
        return A <= B and B <= C;
    };
    int testCases;
    assert(fin >> testCases);
    assert(isBetween(1, testCases, TMAX));
    for (int currentTest = 1; currentTest <= testCases ; ++ currentTest) {
        int N, K;
        assert(fin >> N >> K);
        assert(isBetween(1, N, NMAX));
        assert(isBetween(1, K, KMAX));
        vector <int> solution (N + 1, NOTUSED);
        for (int currentValue = K ; currentValue >= 1 ; -- currentValue) {
            int _left = 1;
            int _right = N;
 
            while (_left <= _right) {
                int middle = (_left + _right) >> 1;
                if (solution [middle] != NOTUSED) {
                    _right = middle - 1;
                }
                else if (currentValue - 1 > middle - 1) {
                    _left = middle + 1;
                }
                else {
                    assert(solution[middle] == NOTUSED);
                    while (middle <= N and solution [middle] == NOTUSED) {
                        solution [middle] = currentValue;
                        middle += 1;
                    }
                    break;
                }
            }
        }
 
        for (int index = 1; index <= N; ++ index) {
            if(solution[index] == NOTUSED) {
                solution[index] = 1;
            }
            fout << solution[index] << ' ';
        }
        fout << '\n';
    }
    return 0;
}
