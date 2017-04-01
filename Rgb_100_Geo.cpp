/*
 * George Marcus
 * Sursa oficiala :-)
 */
 
#include <bits/stdc++.h>
 
using namespace std;
 
vector<int> pts[3];
 
void init() {
  for (int i = 0; i < 3; i++) {
    pts[i].clear();
  }
}
 
void add(int c, int x) {
  pts[c].push_back(x);
}
 
int main() {
  assert(freopen("rgb.in", "r", stdin));
  assert(freopen("rgb.out","w", stdout));
   
  int T;
  assert(cin >> T);
 
  while (T--) {
    init();
 
    int numR, numG, numB;
    int colorR = 0, colorG = 1, colorB = 2;
     
    assert(cin >> numR >> numG >> numB);
    assert(1 <= numR && numR <= 100);
    assert(1 <= numG && numG <= 100);
    assert(1 <= numB && numB <= 100);
     
    if (numR > numG) {
      swap(numR, numG);
      swap(colorR, colorG);
    }
    if (numR > numB) {
      swap(numR, numB);
      swap(colorR, colorB);
    }
    if (numG > numB) {
      swap(numG, numB);
      swap(colorG, colorB);
    }
     
    if (numB > 2 * numR) {
      cout << -1 << endl;
      continue;
    }
     
    int extraG = numG - numR;
    int extraB = numB - numR;
    int offset = 100;
    for (int i = 0; i < numR; i++) {
      int x = i * offset;
      if (extraG > 0) {
        add(colorG, x);
        extraG--;
      }
      if (extraB > 0) {
        add(colorB, x + 1);
        extraB--;
      }
      add(colorR, x + 2);
      add(colorG, x + 3);
      add(colorB, x + 4);
    }
    assert(extraG == 0 && extraB == 0);
     
    assert((int) pts[0].size() + (int) pts[1].size() + (int) pts[2].size() == numR + numG + numB);
    for (int c = 0; c < 3; c++) {
      for (size_t i = 0; i < pts[c].size(); i++) {
        if (i > 0) {
          cout << ' ';
        }
        cout << pts[c][i];
      }
      cout << endl;
    }
  }
   
  return 0;
}