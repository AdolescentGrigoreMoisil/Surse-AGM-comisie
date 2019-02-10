/*
Correct solution.
Uses C-style input/output.
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

char answer[1000];
char buf[1000];
void runTestEasy() {
  scanf("%d %d", &myRow, &myCol); fgets(buf, sizeof(buf), stdin);

  bool reachedMid = false;
  const int midRow = MAP_SIZE / 2;
  const int midCol = MAP_SIZE / 2;

  do {
    if (myRow == midRow && myCol == midCol) {
      reachedMid = true;
    }
    if (!reachedMid) {
      string direction = getDirection(midRow, midCol);
      printf("MOVE %s\n", direction.c_str());
      fflush(stdout);
    } else {
      printf("RADAR\n");
      fflush(stdout);
      scanf("%s %d %d", answer, &enemyRow, &enemyCol); fgets(buf, sizeof(buf), stdin);
      assert(strcmp(answer, "POSITION") == 0);

      string direction = getDirection(enemyRow, enemyCol);
      printf("MOVE %s\n", direction.c_str());
      fflush(stdout);
    }
    fgets(answer, sizeof(answer), stdin);
  } while (strcmp(answer, "NOT DEAD\n") == 0);
}

int main() {
	// assert(freopen("date.in", "r", stdin));
	// assert(freopen("date.out", "w", stdout));
	// cin.sync_with_stdio(false);

  runTestEasy();

	return 0;
}
