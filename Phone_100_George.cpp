/*
 * Problem: phone
 * Author: George Marcus
 * Expected: AC
 */
#include <bits/stdc++.h>

using namespace std;

int N, X;
string S;

string toString(long long val) {
  stringstream ss;
  ss << val;
  string str;
  ss >> str;
  return str;
}

long long parseNumber(int start, int size) {
  long long ret = 0;
  for (int i = start; i < start + size; i++) {
    ret = 10 * ret + S[i] - '0';
  }
  return ret;
}

int scanNumber(int start, long long value) {
  int pos = start;
  long long currentValue = 0;
  while (pos < N && currentValue < value) {
    currentValue = 10 * currentValue + S[pos] - '0';
    pos++;
  }
  if (currentValue == value) {
    return pos;
  } else {
    if (pos == N) {
      return -2;
    } else {
      return -1;
    }
  }
}

bool solve() {
  if (X == 1) {
    return true;
  }
  if (X == 2) {
    for (int i = 1; i < N; i++) {
      if (S[i] != '0') {
        return true;
      }
    }
    return false;
  }

  for (int middleSize = 1; middleSize <= N; middleSize++) {
    for (int middleStart = 1; middleStart + middleSize - 1 < N - 1; middleStart++) {
      long long middleNumber = parseNumber(middleStart, middleSize);
      int numberCount = 1;
      if (middleNumber == 1) {
        continue;
      }
      // first number
      long long firstNumber = middleNumber - 1;
      string firstNumberStr = toString(firstNumber);
      int firstSize = (int) firstNumberStr.size();
      int firstEndingSize = middleStart;
      if (firstSize < firstEndingSize) {
        continue;
      }
      string firstEnding = firstNumberStr.substr(firstSize - firstEndingSize);
      if (firstEnding != S.substr(0, firstEndingSize)) {
        continue;
      }
      numberCount++;

      // middle numbers and ending
      long long currentNumber = middleNumber;
      int pos = middleStart + middleSize;
      bool ok = true;
      do {
        long long nextNumber = currentNumber + 1;
        int nextPos = scanNumber(pos, nextNumber);
        if (nextPos == -1) {
          ok = false;
          break;
        } else if (nextPos == -2) {
          // check if it can be the last number
          string lastNumberStr = toString(nextNumber);
          int lastStartSize = N - pos;
          string lastStart = lastNumberStr.substr(0, lastStartSize);
          numberCount++;
          if (lastStart != S.substr(pos)) {
            ok = false;
          }
          break;
        } else {
          pos = nextPos;
          currentNumber = nextNumber;
          numberCount++;
        }
      } while (pos < N);

      if (ok && numberCount == X) {
        return true;
      }
    }
  }
  return false;
}

int main() {
	// assert(freopen("date.in", "r", stdin));
	// assert(freopen("date.out", "w", stdout));
	cin.sync_with_stdio(false);

  int T;
  cin >> T;

  while (T--) {
  	cin >> N >> X;
    cin >> S;

    bool ans = solve();
    if (ans) {
      cout << "YES\n";
    } else {
      cout << "NO\n";
    }
  }

	return 0;
}
