// Patrick Catalin Alexandru Sava
// Chess Game Checker
// Hard Problem

#include <iostream>
#include <vector>
#include <cassert>
#include <set>

using namespace std;

//ifstream cin ("input");
//ofstream cout ("output");

typedef enum {WHITE, BLACK} color;

class PieceInterface
{
public:
    PieceInterface(){}
    virtual ~PieceInterface(){}
    virtual string getName() = 0;
};

class Piece : public PieceInterface
{
public:
    vector < pair <int, int> > transition;
    color pieceColor;
    bool canGoInfinite;
    Piece(){}
};

class King : public Piece
{
public:
    King(color currentColor)
    {
        canGoInfinite = false;
        pieceColor = currentColor;
        for (int dx = -1; dx <= 1; ++ dx)
            for (int dy = -1; dy <= 1; ++ dy)
                if (dx == 0 and dy == 0)
                    continue;
                else transition.emplace_back(dx, dy);
    }

    string getName() override {
        return "king";
    }

};

class Queen : public Piece
{
public:
    Queen(color currentColor)
    {
        pieceColor = currentColor;
        canGoInfinite = true;
        for (int dx = -1; dx <= 1; ++ dx)
            for (int dy = -1; dy <= 1; ++ dy)
                if (dx == 0 and dy == 0)
                    continue;
                else transition.emplace_back(dx, dy);
    }

    string getName() override {
        return "queen";
    }
};

class Rook : public Piece
{
public:
    Rook(color currentColor)
    {
        pieceColor = currentColor;
        canGoInfinite = true;
        transition.emplace_back(-1, 0);
        transition.emplace_back(1, 0);
        transition.emplace_back(0, -1);
        transition.emplace_back(0, 1);
    }

    string getName() override {
        return "rook";
    }
};

class Bishop : public Piece
{
public:
    Bishop(color currentColor)
    {
        pieceColor = currentColor;
        canGoInfinite = true;
        transition.emplace_back(-1, -1);
        transition.emplace_back(-1, 1);
        transition.emplace_back(1, -1);
        transition.emplace_back(1, 1);
    }

    string getName() override {
        return "bishop";
    }
};

class Knight : public Piece
{
public:
    Knight(color currentColor)
    {
        pieceColor = currentColor;
        canGoInfinite = false;
        for (int dx = 1; dx <= 2; ++ dx)
        {
            int dy = 3 - dx;
            for (int sign1 = -1; sign1 <= 1; sign1 += 2)
                for (int sign2 = -1; sign2 <= 1; sign2 += 2)
                    transition.emplace_back(dx * sign1, dy * sign2);
        }
    }

    string getName() override {
        return "knight";
    }
};

class Table
{
public:
    Table()
    {
        table.resize(static_cast<unsigned int>(SIZE + 1), vector <Cell> (static_cast<unsigned int>(SIZE + 1)));
    }
    void addPiece(Piece *P, pair <int, int> where)
    {
        assert(isInside(where));
        assert(table[where.first][where.second].isEmpty);
        table[where.first][where.second].currentPiece = P;
        table[where.first][where.second].isEmpty = false;
    }
    void finalAssertion()
    {
        Piece *blackKing = nullptr;
        Piece *whiteKing = nullptr;

        for (int i = 1; i <= SIZE; ++ i)
            for (int j = 1; j <= SIZE; ++ j)
                if (!table[i][j].isEmpty and table[i][j].currentPiece->getName() == "king")
                {
                    if (table[i][j].currentPiece->pieceColor == WHITE)
                    {
                        assert(whiteKing == nullptr);
                        whiteKing = table[i][j].currentPiece;
                    }
                    else
                    {
                        assert(table[i][j].currentPiece->pieceColor == BLACK);
                        assert(blackKing == nullptr);
                        blackKing = table[i][j].currentPiece;
                    }
                }
        assert(blackKing != nullptr and whiteKing != nullptr);
    }
    pair <int, int> getKingPosition(color whichOne)
    {
        for (int i = 1; i <= SIZE; ++ i)
            for (int j = 1; j <= SIZE; ++ j)
                if (!table[i][j].isEmpty
                    and table[i][j].currentPiece->getName() == "king"
                    and table[i][j].currentPiece->pieceColor == whichOne)
                        return {i, j};
        assert(0);
    }

    bool checkChessAgainst(color opponent, vector < pair<int, int> > positions)
    {
        for (auto target: positions)
        {
            bool ok = false;
            for (int i = 1; i <= SIZE && !ok; ++ i)
            {
                for (int j = 1; j <= SIZE && !ok; ++ j)
                {
                    if (table[i][j].isEmpty)
                        continue;
                    if (table[i][j].currentPiece->pieceColor == opponent)
                        continue;

                    int sup = !table[i][j].currentPiece->canGoInfinite ? 1 : SIZE;
                    for (auto &trans : table[i][j].currentPiece->transition)
                    {
                        if (ok)
                            break;

                        for (int boundary = 1; boundary <= sup; ++ boundary)
                        {
                            int new_x = i + trans.first * boundary;
                            int new_y = j + trans.second * boundary;

                            if (make_pair(new_x, new_y) == target)
                            {
                                ok = true;
                                break;
                            }

                            if (!isInside({new_x, new_y}))
                                break;

                            if (!table[new_x][new_y].isEmpty)
                            {
                                if (table[new_x][new_y].currentPiece->getName() == "king"
                                    and table[new_x][new_y].currentPiece->pieceColor == opponent)
                                    ok = true;
                                break;
                            }
                        }
                   }
                }
            }
            if (!ok)
                return false;
        }
        return true;
    }

    bool check(color opponent)
    {
        auto pos = getKingPosition(opponent);
        return checkChessAgainst(opponent, {pos});
    }

    set <pair<Piece*, pair <int, int> > > getSet()
    {
        set <pair<Piece*, pair <int, int> > > currentPieces;
        for (int i = 1; i <= SIZE; ++ i)
            for (int j = 1; j <= SIZE; ++ j)
                if (!table [i][j].isEmpty)
                    currentPieces.insert({table[i][j].currentPiece, {i, j}});
        return currentPieces;
    }

    bool moveAnyPieceAndCheckForChess(color opponent)
    {
        auto currentPieces = getSet();

        for (int i = 1; i <= SIZE; ++ i)
        {
            for (int j = 1; j <= SIZE; ++ j)
            {
                if (table[i][j].isEmpty)
                    continue;
                if (table[i][j].currentPiece->pieceColor != opponent)
                    continue;
                
                int sup = !table[i][j].currentPiece->canGoInfinite ? 1 : SIZE;

                for (auto &trans : table[i][j].currentPiece->transition)
                {
                    for (int boundary = 1; boundary <= sup; ++ boundary) {
                        int new_x = i + trans.first * boundary;
                        int new_y = j + trans.second * boundary;

                        if (!isInside({new_x, new_y}))
                            continue;

                        if (!table[new_x][new_y].isEmpty
                            and table[new_x][new_y].currentPiece->pieceColor == opponent)
                            break;

                        if (table[new_x][new_y].isEmpty) {
                            currentPieces.insert({table[i][j].currentPiece, {new_x, new_y}});
                            assert(currentPieces.find({table[i][j].currentPiece, {i, j}}) != currentPieces.end());
                            currentPieces.erase(currentPieces.find({table[i][j].currentPiece, {i, j}}));
                            auto aux = populate(currentPieces);
                            if (!aux->check(opponent))
                                return false;
                            assert(currentPieces.find({table[i][j].currentPiece, {new_x, new_y}}) !=
                                   currentPieces.end());
                            currentPieces.erase(currentPieces.find({table[i][j].currentPiece, {new_x, new_y}}));
                            currentPieces.insert({table[i][j].currentPiece, {i, j}});
                            continue;
                        }

                        if (table[new_x][new_y].currentPiece->getName() == "king"
                            and table [i][j].currentPiece->getName() == "king") 
                            return true;

                        assert(table[new_x][new_y].currentPiece->pieceColor == rev(opponent));
                        auto arrivalOld = make_pair(table[new_x][new_y].currentPiece, make_pair(new_x, new_y));
                        auto beforeOld = make_pair(table[i][j].currentPiece, make_pair(i, j));

                        assert(currentPieces.find(arrivalOld) != currentPieces.end());
                        assert(currentPieces.find(beforeOld) != currentPieces.end());
                        currentPieces.erase(arrivalOld);
                        currentPieces.erase(beforeOld);
                        auto newP = make_pair(table[i][j].currentPiece, make_pair(new_x, new_y));
                        currentPieces.insert(newP);
                        auto aux = populate(currentPieces);
                        if (!aux->check(opponent))
                            return false;
                        currentPieces.erase(newP);
                        currentPieces.insert(arrivalOld);
                        currentPieces.insert(beforeOld);
                        break; 
                    }
                }
            }
        }
        return true;
    }

    bool checkMate(color opponent)
    {
        auto pos = getKingPosition(opponent);
        vector < pair<int, int> > positions;
        positions.push_back(pos);
        assert(table[pos.first][pos.second].currentPiece->getName() == "king");
        for (auto &trans : table[pos.first][pos.second].currentPiece->transition)
        {
            int new_x = pos.first + trans.first;
            int new_y = pos.second + trans.second;

            if (!isInside({new_x, new_y}))
                continue;
            if (table[new_x][new_y].isEmpty or
                (!table[new_x][new_y].isEmpty and table[new_x][new_y].currentPiece->pieceColor == rev(opponent)))
                positions.emplace_back(new_x, new_y);
        }
        bool danger = checkChessAgainst(opponent, positions);
        if (!danger)
            return false;
        return moveAnyPieceAndCheckForChess(opponent);
    }

    string solve(color currentlyMoving = WHITE)
    {
        auto currentPieces = getSet();
        for (int i = 1; i <= SIZE; ++ i)
        {
            for (int j = 1; j <= SIZE; ++ j)
            {
                if (table [i][j].isEmpty)
                    continue;
                if (table [i][j].currentPiece->pieceColor != currentlyMoving)
                    continue;
                int sup = !table [i][j].currentPiece->canGoInfinite ? 1 : SIZE;

                for (auto &trans: table[i][j].currentPiece->transition)
                {
                    for (int boundary = 1; boundary <= sup; ++ boundary)
                    {
                        int new_x = i + trans.first * boundary;
                        int new_y = j + trans.second * boundary;

                        if (!isInside({new_x, new_y}))
                            continue;
                        if (!table[new_x][new_y].isEmpty
                            and table[new_x][new_y].currentPiece->pieceColor == currentlyMoving)
                            break;
                        auto before = make_pair(table[i][j].currentPiece, make_pair(i, j));
                        auto after = make_pair(table[new_x][new_y].currentPiece, make_pair(new_x, new_y));

                        if (table[new_x][new_y].isEmpty) {
                            currentPieces.erase(before);
                            currentPieces.insert({table[i][j].currentPiece, {new_x, new_y}});
                            auto aux = populate(currentPieces);
                            if (!aux->check(currentlyMoving) and aux->checkMate(rev(currentlyMoving))) {
                                return "Checkmate!";
                            }
                            currentPieces.insert(before);
                            currentPieces.erase({table[i][j].currentPiece, {new_x, new_y}});
                        } else {
                            currentPieces.erase(before);
                            currentPieces.erase(after);
                            currentPieces.insert({table[i][j].currentPiece, {new_x, new_y}});
                            auto aux = populate(currentPieces);
                            if (!aux->check(currentlyMoving) and aux->checkMate(rev(currentlyMoving)))
                                return "Checkmate!";
                            currentPieces.insert(before);
                            currentPieces.insert(after);
                            currentPieces.erase({table[i][j].currentPiece, {new_x, new_y}});
                            break;
                        }
                    }
                }
            }
        }
        return "Bad Luck!";
    }

    Table* populate(set < pair<Piece*, pair <int, int> > > &currentPieces)
    {
        Table* newTable = new Table();
        for (auto &element : currentPieces)
            newTable -> addPiece(element.first, element.second);
        newTable->finalAssertion();
        return newTable;
    }
private:
    const int SIZE = 8;
    int isInside (pair <int, int> position)
    {
        return 1 <= position.first and position.first <= SIZE and
               1 <= position.second and position.second <= SIZE;
    }
    class Cell
    {
    public:
        Piece* currentPiece;
        bool isEmpty;
        Cell()
        {
            currentPiece = nullptr;
            isEmpty = true;
        }
    };
    vector < vector <Cell> > table;
    color rev (color opponent)
    {
        if (opponent == WHITE)
            return BLACK;
        return WHITE;
    }
};

color convertToColor (string foo)
{
    if (foo == "black")
        return BLACK;
    return WHITE;
}
int main() {
    int numberOfPieces;
    assert(cin >> numberOfPieces);
    const int maximumNumberOfPieces = 16;
    assert(2 <= numberOfPieces and numberOfPieces <= 16);
    Table *T = new Table();
    pair <int, int> bishopWhite = {-1, -1};
    pair <int, int> bishopBlack = {-1, -1};
    while(numberOfPieces --)
    {
        string piece, colorOfPiece;
        int x, y;
        cin >> piece >> colorOfPiece;
        cin >> x >> y;

        assert(1 <= x and x <= 8);
        assert(1 <= y and y <= 8);

        assert(piece == "king" or piece == "queen" or piece == "rook" or piece == "knight" or piece == "bishop");
        assert(colorOfPiece == "black" or colorOfPiece == "white");

        Piece *P;
        if (piece == "king")
            P = new King(convertToColor(colorOfPiece));
        else if (piece == "queen")
            P = new Queen(convertToColor(colorOfPiece));
        else if (piece == "rook")
            P = new Rook(convertToColor(colorOfPiece));
        else if (piece == "knight")
            P = new Knight(convertToColor(colorOfPiece));
        else
        {
            assert(piece == "bishop");
            P = new Bishop(convertToColor(colorOfPiece));
            if (convertToColor(colorOfPiece) == BLACK) {
                if (bishopBlack == make_pair(-1, -1))
                    bishopBlack = {x, y};
                else assert((bishopBlack.first + bishopBlack.second) % 2 != (x + y) % 2);
            }
            else{
                if (bishopWhite == make_pair(-1, -1))
                    bishopWhite = {x, y};
                else assert((bishopWhite.first + bishopWhite.second) % 2 != (x + y) % 2);
            }
        }

        T -> addPiece(P, {x, y});
    }
    T -> finalAssertion();
    cout << T -> solve() << '\n';
    return 0;
}
