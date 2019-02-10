// Patrick Catalin Alexandru Sava
#include <iostream>

using namespace std;

int main() {
    int n;
    cin >> n;
    while (n --)
    {
        int x;
        cin >> x;
        if (x & 1)
            cout << "Mountain\n";
        else cout << "Island\n";
    }
    return 0;
}