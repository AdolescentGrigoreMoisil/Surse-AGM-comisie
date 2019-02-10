#include <bits/stdc++.h>

using namespace std;

bool moveSub (const string &direction) {
    cerr << direction << endl;
    cout << "MOVE " << direction << '\n';
    cout.flush();
    string answer;
    cin >> answer;
    if (answer == "DEAD") {
        return false;
    }
    cin >> answer;
    assert(answer == "DEAD");
    return true;
}

bool moveUp (int &x, int &y) {
    string direction = "UP";
    x -= 1;
    return moveSub(direction);
}

bool moveDown (int &x, int &y) {
    string direction = "DOWN";
    x += 1;
    return moveSub(direction);
}

bool moveLeft (int &x, int &y) {
    string direction = "LEFT";
    y -= 1;
    return moveSub(direction);
}

bool moveRight (int &x, int &y) {
    string direction = "RIGHT";
    y += 1;
   return  moveSub(direction);
}

pair <int, int> getPosition () {
    cout << "RADAR\n";
    cout.flush();
    int x, y;
    string answer;
    cin >> answer >> x >> y;
    return make_pair (x, y);
}

int getDistance (int x1, int y1, int x2, int y2) {
    int maxX = max (x1, x2);
    int minY = min (y1, y2);
    return maxX - minY;
}

void playGame (int x, int y) {
    bool keepGoing = true;
    while (x != 15) {
        if (x < 15) {
            keepGoing &= moveDown(x, y);
        }
        else {
            keepGoing &= moveUp(x, y);
        }
        if (!keepGoing) return;
    }
    while (y != 15) {
        if (y < 15) {
            keepGoing &= moveRight(x, y);
        }
        else {
            keepGoing &= moveLeft(x, y);
        }
        if (!keepGoing) return;
    }
    while (true) {
        pair <int, int> enemyPos = getPosition();
        int xDifference = getDistance(x, x + 1, enemyPos.first, enemyPos.first + 1);
        int yDifference = getDistance(y, y + 1, enemyPos.second, enemyPos.second + 1);
        // cerr << x << ' ' << y << ' ' << enemyPos.first << ' ' << enemyPos.second << endl;
        if (xDifference == 0 and yDifference == 0) {
          break;
        }
        if (xDifference <= yDifference) {
            if (y < enemyPos.second) {
                keepGoing &= moveRight(x, y);
            }
            else {
                keepGoing &= moveLeft(x, y);
            }
        }
        else {
            if (x < enemyPos.first) {
                keepGoing &= moveDown(x, y);
            }
            else {
                keepGoing &= moveUp(x, y);
            }
        }
        if (!keepGoing) return;
    }
}

int main() {
    int currentX, currentY;
    cin >> currentX >> currentY;
    playGame(currentX, currentY);
    return 0;
}
