// Patrick Catalin Alexandru Sava
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

int main() {
    int my_x, my_y;
    assert(cin >> my_x >> my_y);
    string aux;
    int x = 15;
    int y = 15;
    while (!(x == my_x and y == my_y)) {

        if (my_x < x) {
            cout << "MOVE DOWN\n";
            cout.flush();
            my_x += 1;
        } else if (my_x > x) {
            cout << "MOVE UP\n";
            cout.flush();
            my_x -= 1;
        } else if (my_y < y) {
            cout << "MOVE RIGHT\n";
            cout.flush();
            my_y += 1;
        } else if (my_y > y) {
            cout << "MOVE LEFT\n";
            cout.flush();
            my_y -= 1;
        }
        string sol;
        assert(cin >> sol);
        if (sol == "NOT")
        {
            assert(cin >> sol);
            assert (sol == "DEAD");
        }
        else {
            assert (sol == "DEAD");
            return 0;
        }
    }


    while(1)
    {
        cout << "RADAR\n"; cout.flush();
        string position;
        assert(cin >> position);
        assert(position == "POSITION");
        assert(cin >> x >> y);
        if (abs (my_x - x) > abs (my_y - y)) {
            if (my_x < x) {
                cout << "MOVE DOWN\n";
                cout.flush();
                my_x += 1;
            } else if (my_x > x) {
                cout << "MOVE UP\n";
                cout.flush();
                my_x -= 1;
            }
        }
        else {
            if (my_y < y) {
                cout << "MOVE RIGHT\n";
                cout.flush();
                my_y += 1;
            } else if (my_y > y) {
                cout << "MOVE LEFT\n";
                cout.flush();
                my_y -= 1;
            }
        }
        string response;
        assert(cin >> response);
        if (response == "NOT") {
            assert(cin >> response);
            assert(response == "DEAD");
        }
        else
        {
            assert(response == "DEAD");
            break;
        }
    }

    return 0;
}
