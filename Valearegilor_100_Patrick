/*Patrick Catalin Alexandru Sava
The University of Manchester
Problem: "Valea Regilor"
Expected: Accepted*/
 
#include <iostream>
#include <fstream>
#include <cassert>
#include <vector>
#include <algorithm>
 
using namespace std;
 
template <typename T>
bool isBetween (T inf, T number, T sup)
{
    return inf <= number and number <= sup;
}
 
bool checkInput (vector <int> &elements, int numberOfElements)
{
    vector <bool> visited (static_cast<unsigned int>(numberOfElements + 1), false);
    for (int currentIndex = 1; currentIndex <= numberOfElements; ++ currentIndex)
    {
        if (visited[elements[currentIndex]])
        {
            return false;
        }
        visited[elements[currentIndex]] = 1;
    }
    return true;
}
 
class SegmentTree
{
public:
    SegmentTree()
    {
 
    }
    SegmentTree(vector <int> &elements, int numberOfElements)
    {
        maxValue = numberOfElements;
        tree.resize(static_cast<unsigned int>(numberOfElements << 2 | 1), {INT32_MAX, 0});
        for (int currentIndex = 1; currentIndex <= numberOfElements; ++ currentIndex)
        {
            update (1, 1, maxValue, currentIndex, elements[currentIndex]);
        }
    }
 
    int askForMinimumPosition (int _left, int _right)
    {
        return query(1, 1, maxValue, _left, _right).second;
    }
 
private:
    int maxValue;
    vector < pair <int, int> > tree;
    void update (int node, int _left, int _right, int position, int value)
    {
        if (_left == _right)
        {
            tree [node] = {value, position};
            return;
        }
 
        int middle = (_left + _right) >> 1;
 
        if (position <= middle)
        {
            update(node * 2, _left, middle, position, value);
        }
        else
        {
            update(node * 2 + 1, middle + 1, _right, position, value);
        }
        tree [node] = min(tree[node * 2], tree[node * 2 + 1]);
    }
 
    pair <int, int> query (int node, int _left, int _right, int leftQuery, int rightQuery)
    {
        if (leftQuery <= _left and _right <= rightQuery)
        {
            return tree [node];
        }
        int middle = (_left + _right) >> 1;
        pair <int, int> ansLeft = {INT32_MAX, INT32_MAX};
        pair <int, int> ansRight = {INT32_MAX, INT32_MAX};
 
        if (leftQuery <= middle)
        {
            ansLeft = query(node * 2, _left, middle, leftQuery, rightQuery);
        }
        if (rightQuery > middle)
        {
            ansRight = query(node * 2 + 1, middle + 1, _right, leftQuery, rightQuery);
        }
        return min (ansLeft, ansRight);
    }
};
 
int buildCartesianTree (int _left, int _right, SegmentTree *&SegTree, vector < vector <int> > &graph, vector<int> &elements)
{
    // return the root
    if (_left > _right)
    {
        return -1;
    }
    int minimumPosition = SegTree -> askForMinimumPosition(_left, _right);
    if (minimumPosition - 1 >= _left)
    {
        graph [elements[minimumPosition]].push_back(elements[SegTree -> askForMinimumPosition(_left, minimumPosition - 1)]);
        buildCartesianTree(_left, minimumPosition - 1, SegTree, graph, elements);
    }
    if (minimumPosition + 1 <= _right)
    {
        graph [elements[minimumPosition]].push_back(elements[SegTree -> askForMinimumPosition(minimumPosition + 1, _right)]);
        buildCartesianTree(minimumPosition + 1, _right, SegTree, graph, elements);
    }
    return minimumPosition;
}
 
void depthFirstSearch (int node, vector < vector <int> > &graph, vector <int> &dp, vector <int> &inverse,
                       const bool truthValue)
{
    for (auto &neighbour : graph[node])
    {
        if ((inverse[neighbour] < inverse[node]) == truthValue)
        {
            dp[neighbour] = dp [node] + 1;
        }
        else
        {
            dp [neighbour] = dp [node];
        }
        depthFirstSearch(neighbour, graph, dp, inverse, truthValue);
    }
}
 
void buildPartialSumsAndLevels (int node, int father, int currentLevel, vector < vector <int> > &graph,
                                vector <int> &level, vector <int> &euler, vector <int> &firstAppearance)
{
    level [node] = currentLevel;
    euler.push_back(node);
    firstAppearance[node] = min(firstAppearance[node], (int)euler.size() - 1);
    for (auto &neighbour : graph[node])
    {
        buildPartialSumsAndLevels(neighbour, node, currentLevel + 1, graph,
                                  level, euler, firstAppearance);
        euler.push_back(node);
        firstAppearance[node] = min(firstAppearance[node], (int)euler.size() - 1);
    }
}
 
int main()
{
    const char inputFile[] =  "valearegilor.in";
    const char outputFile[] = "valearegilor.out";
    const auto MaxNumberOfElements = static_cast<const int>(1e5);
    const auto MaxNumberOfQueries = static_cast<const int>(1e6);
 
    ifstream inputStream (inputFile);
    ofstream outputStream (outputFile);
 
    assert(inputStream.is_open());
    assert(outputStream.is_open());
 
    int numberOfElements;
    int numberOfQueries;
    assert(inputStream >> numberOfElements >> numberOfQueries);
    assert(isBetween(1, numberOfElements, MaxNumberOfElements));
    assert(isBetween(1, numberOfQueries, MaxNumberOfQueries));
 
    vector <int> elements (static_cast<unsigned int>(numberOfElements + 1));
    vector <int> inverse (static_cast<unsigned int>(numberOfElements + 1));
    for (int currentIndex = 1; currentIndex <= numberOfElements; ++ currentIndex)
    {
        assert(inputStream >> elements[currentIndex]);
        assert(isBetween(1, elements[currentIndex], numberOfElements));
        inverse[elements[currentIndex]] = currentIndex;
    }
    assert(checkInput(elements, numberOfElements));
    auto *SegTree = new SegmentTree (elements, numberOfElements);
    vector < vector <int> > graph (static_cast<unsigned int>(numberOfElements + 1));
    int root = buildCartesianTree(1, numberOfElements, SegTree, graph, elements);
    vector <int> dpLeft (static_cast<unsigned int>(numberOfElements + 1), 0);
    vector <int> dpRight(static_cast<unsigned int>(numberOfElements + 1), 0);
    dpLeft [elements[root]] = dpRight [elements[root]] = 1;
    depthFirstSearch (elements[root], graph, dpLeft, inverse, false);
    depthFirstSearch (elements[root], graph, dpRight, inverse, true);
    dpLeft [0] = dpRight [0] = 0;
    vector <int> level (static_cast<unsigned int>(numberOfElements + 1));
    vector <int> euler; euler.push_back(0);
    euler.reserve(static_cast<unsigned int>(numberOfElements << 2 | 1));
    vector <int> firstAppearance(numberOfElements << 2 | 1, INT32_MAX);
    buildPartialSumsAndLevels (elements[root], 0, 1, graph, level, euler, firstAppearance);
    auto eulerSize = (int)euler.size() - 1;
    vector < vector <int> > rmq (static_cast<unsigned int>(20), vector <int> (static_cast<unsigned int>(eulerSize + 20)));
    vector <int> logarithm (eulerSize + 10, 0);
    for (int number = 2; number <= eulerSize; ++ number)
    {
        logarithm[number] = logarithm[number >> 1] + 1;
    }
    for (int currentIndex = 1; currentIndex <= eulerSize; ++ currentIndex)
    {
        rmq[0][currentIndex] = currentIndex;
    }
    for (int step = 1; (1 << step) <= eulerSize; ++ step)
    {
        for (int currentIndex = 1; currentIndex + (1 << step) - 1 <= eulerSize; ++ currentIndex)
        {
            rmq [step][currentIndex] = rmq [step - 1][currentIndex];
            int whichPosition = currentIndex + (1 << (step - 1));
            if (whichPosition <= eulerSize)
            {
                if (level[euler[rmq[step - 1][whichPosition]]] < level[euler[rmq[step][currentIndex]]])
                {
                    rmq[step][currentIndex] = rmq[step - 1][whichPosition];
                }
            }
        }
    }
    auto getLowestCommonAncestor = [&](const int &firstNode, const int &secondNode) -> int {
        int firstPosition = firstAppearance[firstNode];
        int secondPosition = firstAppearance[secondNode];
 
        if (firstPosition > secondPosition)
        {
            int temp = firstPosition;
            firstPosition = secondPosition;
            secondPosition = temp;
        }
        int diff = secondPosition - firstPosition + 1;
        int currentLogarithm = logarithm[diff];
        int answer = rmq[currentLogarithm][firstPosition];
        int secondPart = diff - (1 << currentLogarithm);
 
        if (level[euler[answer]] > level[euler[rmq[currentLogarithm][firstPosition + secondPart]]])
        {
            answer = rmq[currentLogarithm][firstPosition + secondPart];
        }
 
        return euler[answer];
    };
 
    for (int currentQuery = 1; currentQuery <= numberOfQueries; ++ currentQuery)
    {
        int _left, _right;
        assert(inputStream >> _left >> _right);
        assert(isBetween(1, _left, numberOfElements));
        assert(isBetween(1, _right, numberOfElements));
        assert(_left <= _right);
        _left = elements[_left];
        _right = elements[_right];
 
        int currentLca = getLowestCommonAncestor(_left, _right);
        outputStream << dpRight[_left] + dpLeft[_right] - dpLeft[currentLca] - dpRight[currentLca] + 1 << '\n';
    }
    return 0;
}
