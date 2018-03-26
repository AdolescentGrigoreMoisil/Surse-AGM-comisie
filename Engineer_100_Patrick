/*
 * Patrick Catalin Alexandru Sava
 * The University of Manchester
 * Expected: Accepted
 * Persistent Segment Tree with dynamic allocation
 */
  
#include <bits/stdc++.h>
  
using namespace std;
  
const char IN[] = "engineer.in";
const char OUT[] = "engineer.out";
const int MAX = 1100;
const int QMAX = 1000;
const int VALMAX = 1e9;
  
ifstream fin (IN);
ofstream fout(OUT);
  
class PersistentSegmentTree
{
public:
    PersistentSegmentTree(int n, int m, int maxValue)
    {
        this -> n = n;
        this -> m = m;
        this -> maxValue = maxValue;
        for (int i = 0 ; i <= n ; ++ i)
        {
            roots.push_back(vector <node*> (m + 1));
            roots[i][0] = new node();
        }
    }
    void Update (pair <int, int> cell, int value)
    {
        updateOnLine(cell, value);
    }
    int Query (pair <int, int> upperLeft, pair <int, int> lowerRight, int kthElement)
    {
        return solveQuery(upperLeft, lowerRight, kthElement);
    }
  
private:
    struct node
    {
        node *leftSon;
        node *rightSon;
        int sum;
        node()
        {
            leftSon = NULL;
            rightSon = NULL;
            sum = 0;
        }
        node(node *&leftSon, node *&rightSon, int sum)
        {
            this -> leftSon = leftSon;
            this -> rightSon = rightSon;
            this -> sum = sum;
        }
    };
    int n, m, maxValue;
    vector < vector <node *> > roots;
  
    node* copyNode (node *&currentNode)
    {
        if (currentNode != NULL)
        {
            return new node(currentNode->leftSon, currentNode->rightSon, currentNode->sum);
        }
        else
        {
            return new node();
        }
    }
  
    node* incrementOnPosition(node *&currentNode, int st, int dr, int value)
    {
        node* copiedNode = copyNode(currentNode);
        if (st == dr)
        {
            copiedNode -> sum += 1;
            return copiedNode;
        }
  
        int mij = (st + dr) >> 1;
  
        if (value <= mij)
        {
            copiedNode -> leftSon = incrementOnPosition(copiedNode -> leftSon, st, mij, value);
        }
        else
        {
            copiedNode -> rightSon = incrementOnPosition(copiedNode -> rightSon, mij + 1, dr, value);
        }
        copiedNode -> sum = 0;
        if (copiedNode -> leftSon != NULL)
        {
            copiedNode -> sum += copiedNode -> leftSon -> sum;
        }
        if (copiedNode -> rightSon != NULL)
        {
            copiedNode -> sum += copiedNode -> rightSon -> sum;
        }
        return copiedNode;
    }
  
    void updateOnLine (pair <int, int> &cell, int value)
    {
        roots[cell.first][cell.second] = incrementOnPosition(roots [cell.first][cell.second - 1], 1, maxValue, value);
    }
  
    int getValue (pair <node *, node *> &currentInterval)
    {
        auto _right = currentInterval.second ;
        auto _left = currentInterval.first ;
        int sol = 0;
        if (_right != NULL)
        {
            _right = _right -> leftSon;
            if (_right != NULL)
            {
                sol += _right->sum;
            }
        }
        if (_left != NULL)
        {
            _left = _left -> leftSon;
            if (_left != NULL)
            {
                sol -= _left -> sum;
            }
        }
        return sol;
    }
  
    enum directions
    {
        leftWay, rightWay
    };
  
    void moveForward (node *&currentNode, int where)
    {
        if (currentNode == NULL)
            return;
        if (where == leftWay)
        {
            currentNode = currentNode -> leftSon;
        }
        else
        {
            assert(where == rightWay);
            currentNode = currentNode -> rightSon;
        }
    }
  
    void moveForwardInterval (pair <node *, node *> &currentInterval, int where)
    {
        moveForward(currentInterval.first, where);
        moveForward(currentInterval.second, where);
    }
  
    int solveQuery (pair <int, int> upperLeft, pair <int, int> lowerRight, int kth)
    {
        int line1 = upperLeft.first;
        int line2 = lowerRight.first;
        int column1 = upperLeft.second;
        int column2 = lowerRight.second;
        assert(line1 <= line2);
        assert(column1 <= column2);
  
        vector <pair <node *, node *> > temp;
        for (int currentLine = line1 ; currentLine <= line2 ; ++ currentLine)
        {
            temp.push_back({roots[currentLine][column1 - 1], roots [currentLine][column2]});
        }
        int st = 1;
        int dr = maxValue;
        while (st != dr)
        {
            int mij = (st + dr) >> 1;
            int partialSum = 0;
            for (auto &x : temp)
            {
                partialSum += getValue(x);
            }
            if (partialSum >= kth)
            {
                for (auto &x : temp)
                {
                    moveForwardInterval(x, leftWay);
                }
                dr = mij;
            }
            else
            {
                kth -= partialSum;
                for (auto &x : temp)
                {
                    moveForwardInterval(x, rightWay);
                }
                st = mij + 1;
            }
        }
  
        return st;
    }
  
};
  
int main() {
    ios :: sync_with_stdio(false);
    fin.tie(0);
    auto isBetween = [](const int &A, const int &B, const int &C) -> bool
    {
        return A <= B and B <= C;
    };
  
    int n, m;
    assert(fin >> n >> m);
    assert(isBetween(1, n, MAX));
    assert(isBetween(1, m, MAX));
    vector < vector <int> > mat (n + 1, vector <int> (m + 1));
    vector < pair <int, pair <int, int> > > elements (n * m);
    vector <int> inverse (n * m + 1);
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
        {
            assert(fin >> mat [i][j]);
            assert(isBetween(1, mat[i][j], VALMAX));
            elements[(i - 1) * m + j - 1] = {mat [i][j], {i, j}};
        }
    }
    sort (elements.begin(), elements.end());
    int e = 0;
    int lastElem = -1;
    for (auto &x: elements)
    {
        if (lastElem != x.first)
        {
            ++ e;
            inverse [e] = x.first;
            lastElem = x.first;
        }
        mat [x.second.first][x.second.second] = e;
    }
    PersistentSegmentTree *T = new PersistentSegmentTree(n, m, e);
    for (int i = 1 ; i <= n ; ++ i)
    {
        for (int j = 1 ; j <= m ; ++ j)
        {
            T -> Update({i, j}, mat [i][j]);
        }
    }
    int queries;
    assert(fin >> queries);
    assert (isBetween(1, queries, QMAX));
    while (queries --)
    {
        int x1, y1;
        int x2, y2;
        assert(fin >> x1 >> y1);
        assert(fin >> x2 >> y2);
        assert (isBetween(1, x1, n));
        assert (isBetween(1, x2, n));
        assert (isBetween(1, y1, m));
        assert (isBetween(1, y2, m));
        assert (x1 <= x2);
        assert (y1 <= y2);
        int kth;
        assert(fin >> kth);
        assert (isBetween(1, kth, (x2 - x1 + 1) * (y2 - y1 + 1)));
        fout << inverse[T -> Query({x1, y1}, {x2, y2}, kth)] << '\n';
    }
    return 0;
}
