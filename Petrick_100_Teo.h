#include <bits/stdc++.h>
using namespace std;

typedef pair<int, int> Cell;
typedef pair<Cell, Cell> Move;
struct Piece {
    Piece (string _type, int _col): type(_type), col(_col) { }
    string type;
    int col;
};
typedef map<Cell, Piece*> Tabla;
map<string, vector<int>> mdlin, mdcol;

vector<Move> moves(Tabla t, int col) {
    vector<Move> answer;
    for (auto it : t) {
        if (it.second != nullptr && it.second->col == col) {
            const Piece &p = *it.second;
            const vector<int> &dlin = mdlin[p.type];
            const vector<int> &dcol = mdcol[p.type];
            auto inside_grid = [] (Cell c) {
                return 1 <= c.first && c.first <= 8 &&
                        1 <= c.second && c.second <= 8;
            };
            for (int k = 0; k < dlin.size(); k++) {
                Cell cur = it.first;
                auto adv = [&cur, &dlin, &dcol, &k] () {
                    cur = {cur.first + dlin[k], cur.second + dcol[k]};
                };
                adv();
                while (inside_grid(cur) && (t[cur] == nullptr || t[cur]->col == !col)) {
                    answer.push_back({it.first, cur});
                    if (p.type == "knight" || p.type == "king") {
                        break;
                    }
                    if (t[cur] != nullptr) {
                        break;
                    }
                    adv();
                }
            }
        }
    }
    return answer;
}

bool insah(Tabla t, int col) {
    Cell kpos = Cell(0, 0);
    for (auto it : t) {
        if (it.second != nullptr && it.second->col == col && it.second->type == "king") {
            kpos = it.first;
        }
    }
    assert(kpos != Cell(0, 0));
    vector<Move> adv = moves(t, !col);
    for (auto it : adv) {
        if (it.second == kpos) {
            return true;
        }
    }
    return false;
}

Tabla apply(Tabla t, Move m) {
    t[m.second] = t[m.first];
    t[m.first] = nullptr;
    return t;
}

int main() {
    mdlin["knight"] = {-1, -1, 1, 1, -2, 2, -2, 2};
    mdcol["knight"] = {-2, 2, -2, 2, -1, -1, 1, 1};
    mdlin["rook"] = {-1, 1, 0, 0};
    mdcol["rook"] = {0, 0, -1, 1};
    mdlin["bishop"] = {-1, 1, -1, 1};
    mdcol["bishop"] = {-1, 1, 1, -1};
    mdlin["queen"] = {-1, 1, 0, 0, -1, 1, -1, 1};
    mdcol["queen"] = {0, 0, -1, 1, -1, 1, 1, -1};
    mdlin["king"] = mdlin["queen"];
    mdcol["king"] = mdcol["queen"];

    Tabla initial;
    int m; cin >> m;
    for (int i = 1; i <= m; i++) {
        string type, col;
        Cell c;
        cin >> type >> col >> c.first >> c.second;
        initial[c] = new Piece(type, (col == "white" ? 0 : 1));
    }

    assert(!insah(initial, 1));
    for (auto it : moves(initial, 0)) {
        Tabla one = apply(initial, it);
        if (insah(one, 1) && !insah(one, 0)) {
            bool ok = 1;
            for (auto jt : moves(one, 1)) {
                Tabla two = apply(one, jt);
                ok &= insah(two, 1);
            }
            if (ok) {
                cout << "Checkmate!\n";
                return 0;
            }
        }
    }
    cout << "Bad Luck!\n";
    return 0;
}