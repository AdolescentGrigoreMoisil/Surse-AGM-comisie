/*
Correct solution.
*/
#include <bits/stdc++.h>

using namespace std;

const int MAP_SIZE = 30;

int myRow, myCol;
int enemyRow, enemyCol;

int getDist(int a, int b, int c, int d) {
  int maxLeft = max(a, c);
  int minRight = min(b, d);
  return maxLeft - minRight;
}

string getDirection(int targetRow, int targetCol) {
  int rowDist = getDist(myRow, myRow + 1, targetRow, targetRow + 1);
  int colDist = getDist(myCol, myCol + 1, targetCol, targetCol + 1);
  if (rowDist > colDist) {
    if (myRow < targetRow) {
      myRow++;
      return "DOWN";
    } else {
      myRow--;
      return "UP";
    }
  } else {
    if (myCol < targetCol) {
      myCol++;
      return "RIGHT";
    } else {
      myCol--;
      return "LEFT";
    }
  }
}

void runTestEasy() {
  string answer;

  cin >> myRow >> myCol; // getline(cin, answer);

  int fakeMoves = 0;
  int initRow = myRow;
  int initCol = myCol;

  bool reachedMid = false;
  const int midRow = MAP_SIZE / 2;
  const int midCol = MAP_SIZE / 2;

  do {
    if (myRow == midRow && myCol == midCol) {
      reachedMid = true;
    }
    if (!reachedMid) {
      string direction = getDirection(midRow, midCol);
      cout << "MOVE " << direction << '\n';
      cout.flush();
    } else {
      cout << "RADAR\n";
      cout.flush();
      cin >> answer;
      assert(answer == "POSITION");
      cin >> enemyRow >> enemyCol;
      // getline(cin, answer);

      string direction = getDirection(enemyRow, enemyCol);
      cout << "MOVE " << direction << '\n';
      cout.flush();
    }
    // getline(cin, answer);
    cin >> answer;
    cerr << "read " << answer << endl;
    if (answer == "NOT") {
      cin >> answer;
    } else {
      break;
    }
  } while (true);
}

int main() {
	// assert(freopen("date.in", "r", stdin));
	// assert(freopen("date.out", "w", stdout));
	cin.sync_with_stdio(false);

  runTestEasy();

	return 0;
}
