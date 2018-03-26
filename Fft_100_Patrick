/*Patrick Catalin Alexandru Sava
The University of Manchester
Palindromic Tree, Persistent Segment Tree
and Multiplication in logarithmic time to avoid overflow
Expected : Accepted;*/
 
// libraries
#include <iostream>
#include <utility>
#include <vector>
#include <fstream>
#include <cassert>
#include <algorithm>
 
using namespace std;
 
const int AlphabetSize = 26;
 
template <typename T>
bool isBetween (T inf, T num, T sup)
{
    return inf <= num and num <= sup;
}// isBetween with template
 
void makeModulo (long long &number, long long modulo)
{
    while (number >= modulo)
    {
        number -= modulo;
    }
}// makeModulo
 
long long multiplication (long long factor1, long long factor2, long long modulo)
{
    // the fastest way to multiplicate and avoid overflow
    // based on divide and conquer
    factor1 = factor1 % modulo;
    factor2 = factor2 % modulo;
    long long result = 0;
    while (factor2)
    {
        if (factor2 & 1LL)
        {
            result += factor1;
            if (result >= modulo)
            {
                result -= modulo;
            }
        }
        factor1 = factor1 + factor1;
        if (factor1 >= modulo)
        {
            factor1 -= modulo;
        }
        factor2 >>= 1LL;
    }
    assert(isBetween(0LL, result, modulo - 1));
    return result;
}// multiplication
 
class PalindromicTree
{
public:
    // constructors
    PalindromicTree() {}
    PalindromicTree(string sequence, long long base, long long modulo, vector <long long> &precomputedPowers)
    {
        rootOdd = new palNode();
        rootEven = new palNode();
 
        // for palindroms of odd size
        rootOdd->suffixLink = rootOdd;
        rootOdd->length = -1;
        rootOdd->frequency = 0;
 
        // for palindroms of even size
        rootEven->suffixLink = rootOdd;
        rootEven->length = 0;
        rootEven->frequency = 0;
 
        // pass the string
        numberOfLetters = sequence.size();
        this -> sequence = sequence;
        this -> precomputedPowers = std::move(precomputedPowers);
        this -> base = base;
        this -> modulo = modulo;
        bestSuffix = rootEven;
        // build the Palindromic tree
        initialize();
    }// Palindromic Tree constructor
 
    vector < pair <long long , pair <int, long long> > > solve ()
    {
        // return a vector of hashed nodes, with their corresponding
        // length and frequency
        vector < pair <long long , pair <int, long long> > > hashesAndLengths;
        propagation();
 
        depthFirstSearch(rootEven, 0, 0, hashesAndLengths);
        depthFirstSearch(rootOdd, 0, -1, hashesAndLengths);
 
        return hashesAndLengths;
    }// solve
private:
    // precomputed powers for polynomial hashes
    vector <long long> precomputedPowers;
    int numberOfLetters{};
    long long base, modulo;
    string sequence;
    // the model of a node from our data structure
    struct palNode
    {
        int length;
        palNode *suffixLink;
        palNode *neighbour [AlphabetSize];
        long long frequency;
 
        palNode()
        {
            length = 0;
            suffixLink = nullptr;
            for (auto &currentLetter : neighbour) {
                currentLetter = nullptr;
            }
            frequency = 0;
        }
    };
    // some special nodes ahead
    palNode *rootOdd{};
    palNode *rootEven{};
    palNode *bestSuffix;
    vector <palNode *> palNodes;
 
    void initialize ()
    {
        for (int currentIndex = 0; currentIndex < numberOfLetters; ++ currentIndex)
        {
            addLetter(currentIndex);
        }
    }// initialize the Pal Tree before query
 
    void addLetter(int position)
    {
        palNode *node = bestSuffix;
        assert(isBetween(0, position, numberOfLetters - 1));
        int letter = sequence [position] - 'a';
        // find the longest matching suffix link
        while (true)
        {
            assert(node != nullptr);
            int currentLength = node -> length;
            if (position - currentLength - 1 >= 0 and sequence [position - currentLength - 1] == sequence [position])
            {
                break;
            }
            node = node -> suffixLink;
        }
        assert(node != nullptr);
        // if the node already exists, just increase the frequency
        if (node -> neighbour [letter] != nullptr)
        {
            node -> neighbour [letter] -> frequency += 1LL;
            bestSuffix = node -> neighbour [letter];
            return;
        }
        // otherwise create an another node
        bestSuffix = new palNode();
        bestSuffix->length = node -> length + 2;
        bestSuffix -> frequency += 1LL;
        palNodes.push_back(bestSuffix);
        node -> neighbour [letter] = bestSuffix;
        // pay attention to this particular case,
        // set the suffix link properly
        if (bestSuffix -> length == 1)
        {
            bestSuffix -> suffixLink = rootEven;
            return;
        }
        // find the suffix link otherwise
        while (true)
        {
            assert(node != nullptr);
            node = node -> suffixLink;
            int currentLength = node -> length;
 
            if (position - currentLength - 1 >= 0 and sequence [position - currentLength - 1] == sequence [position])
            {
 
                assert(node -> neighbour [letter] != nullptr);
                bestSuffix -> suffixLink = node -> neighbour [letter];
                break;
            }
        }
    }// addLetter
    void propagation ()
    {
        // propagate the frequencies
        while (!palNodes.empty())
        {
            auto currentNode = palNodes.back();
            palNodes.pop_back();
            currentNode -> suffixLink -> frequency += currentNode -> frequency;
        }
    }// propagation
 
    void depthFirstSearch(palNode *&currentNode, long long hash, int length,
                          vector<pair<long long, pair<int, long long> > > &solution)
    {
        // make a depthFirstSearch to get all the hashes
        if (currentNode == nullptr)
        {
            return;
        }
        assert(currentNode != nullptr);
        if (currentNode -> length != 0 and currentNode -> length != -1)
        {
            // if it is not a special node, get it
            makeModulo(hash, modulo);
            solution.push_back({hash, {length, currentNode -> frequency}});
        }
        for (int currentLetter = 0; currentLetter < AlphabetSize; ++ currentLetter)
        {
            if (currentNode->length == -1)
            {
                // pay attention to this tricky case
                depthFirstSearch(currentNode->neighbour[currentLetter], currentLetter + 'a', length + 2, solution);
            }
            else
            {
                // compute the corresponding hash after appending the $currentletter to back and front
                long long partialHash = hash + multiplication(precomputedPowers [length], currentLetter + 'a', modulo);
                makeModulo(partialHash, modulo);
                partialHash = multiplication(partialHash, base, modulo);
                partialHash += currentLetter + 'a';
                makeModulo(partialHash, modulo);
                depthFirstSearch(currentNode->neighbour[currentLetter], partialHash, length + 2, solution);
            }
        }
    }// depthFirstSearch
};
 
void normalize (vector < pair <long long, pair <int, long long> > > &hashesFromPalTree,
                vector < pair < pair <long long, long long>, pair < pair <int, int>, int > > > &queries)
{
    // normalize the hashes and queries
    vector <long long> mergedValues;
    // insert all the values into the array
    for (auto &info : hashesFromPalTree)
    {
        mergedValues.push_back(info.first);
    }
    for (auto &info : queries)
    {
        mergedValues.push_back(info.first.first);
        mergedValues.push_back(info.first.second);
    }
    // sort it
    sort (mergedValues.begin(), mergedValues.end());
    int lastLabel = 0;
    long long lastValue = -(1LL << 61);
    int currentPointer = 0;
    // normalize it
    vector <int> indices (mergedValues.size() + 1);
    for (auto &currentElement : mergedValues)
    {
        if (currentElement != lastValue)
        {
            lastLabel += 1;
            lastValue = currentElement;
        }
        assert(currentPointer < mergedValues.size());
        indices [currentPointer] = lastLabel;
        currentPointer += 1;
    }
    // apply "two pointers" to get the right result
    sort (hashesFromPalTree.begin(), hashesFromPalTree.end());
    currentPointer = 0;
    for (auto &info : hashesFromPalTree)
    {
        auto currentHash = info.first;
        while (currentPointer < mergedValues.size() and mergedValues [currentPointer] != currentHash)
        {
            currentPointer += 1;
        }
        assert(currentPointer < mergedValues.size());
        info.first = indices[currentPointer];
    }
    sort (queries.begin(), queries.end());
    currentPointer = 0;
    for (auto &info : queries)
    {
        auto currentModulo = info.first.first;
        while (currentPointer < mergedValues.size() and mergedValues [currentPointer] != currentModulo)
        {
            currentPointer += 1;
        }
        assert(currentPointer < mergedValues.size());
        info.first.first = indices[currentPointer];
        swap (info.first.first, info.first.second);
    }
    sort (queries.begin(), queries.end());
    currentPointer = 0;
    for (auto &info : queries)
    {
        auto currentModulo = info.first.first;
        while (currentPointer < mergedValues.size() and mergedValues [currentPointer] != currentModulo)
        {
            currentPointer += 1;
        }
        assert(currentPointer < mergedValues.size());
        info.first.first = indices[currentPointer];
        swap (info.first.first, info.first.second);
    }
}// normalize
 
class PersistentSegmentTree
{
public:
    PersistentSegmentTree(){}
    PersistentSegmentTree(int numberOfRoots, int maxValue)
    {
        roots.resize(static_cast<unsigned int>(numberOfRoots + 1));
        roots [0] = nullptr;
        this -> maxValue = maxValue;
    } // PersistentSegmentTree constructor
    void updateRoot (int which, int currentPosition, long long currentValue)
    {
        update (roots [which], 1, maxValue, currentPosition, currentValue);
    }// updateRoot
    void fakeUpdate (int which)
    {
        assert(which - 1 >= 0);
        roots [which] = roots [which - 1];
    }// fakeUpdate
    long long rangeQuery (int positionOne, int positionTwo, int valueOne, int valueTwo)
    {
        assert(positionOne > 0);
        assert(positionOne <= positionTwo);
        assert(valueOne <= valueTwo);
 
        return rangeQuery(roots [positionOne - 1], roots [positionTwo], valueOne, valueTwo);
    }// rangeQuery
private:
    int maxValue;
    // the model of a node from our data structure
    struct node
    {
        node *left;
        node *right;
        long long value;
 
        node ()
        {
            left = nullptr;
            right = nullptr;
            value = 0LL;
        }
 
        node (node *_left, node *_right, long long _value)
        {
            this -> left = _left;
            this -> right = _right;
            this -> value = _value;
        }
    };
    vector <node *> roots;
    node* copyNode (node *&currentNode)
    {
        if (currentNode == nullptr)
        {
            return new node (nullptr, nullptr, 0);
        }
        return new node (currentNode -> left, currentNode -> right, currentNode -> value);
    }// copyNode
    long long getValue (node *&currentNode)
    {
        // a wrapper to avoid null refference exception
        if (currentNode == nullptr)
        {
            return 0;
        }
        return currentNode -> value;
    }// getValue
    void update (node *&currentNode, int _left, int _right, int position, long long updatingValue)
    {
        // increase the value of a certain leaf
        currentNode = copyNode (currentNode);
        if (_left == _right)
        {
            currentNode -> value += updatingValue;
            return;
        }
        int middle = (_left + _right) >> 1;
        if (position <= middle)
        {
            update (currentNode -> left, _left, middle, position, updatingValue);
        }
        else
        {
            update (currentNode -> right, middle + 1, _right, position, updatingValue);
        }
        currentNode -> value = getValue(currentNode -> left) + getValue(currentNode -> right);
    }// update
    long long query (node *&currentNode, int _left, int _right, int _queryLeft, int _queryRight)
    {
        // get the sum on a certain range
        if (currentNode == nullptr)
        {
            return 0;
        }
        if (_queryLeft <= _left and _right <= _queryRight)
        {
            return getValue(currentNode);
        }
        int middle = (_left + _right) >> 1;
        long long totalSum = 0;
        if (_queryLeft <= middle)
        {
            totalSum += query(currentNode -> left, _left, middle, _queryLeft, _queryRight);
        }
        if (_queryRight > middle)
        {
            totalSum += query(currentNode -> right, middle + 1, _right, _queryLeft, _queryRight);
        }
        return totalSum;
    }// query
    long long rangeQuery (node *&leftRoot, node *&rightRoot, int _left, int _right)
    {
        return query(rightRoot, 1, maxValue, _left, _right) -
               query(leftRoot, 1, maxValue, _left, _right);
    }// range
};
 
int main()
{
    // streams
    ifstream input ("fft.in");
    ofstream output ("fft.out");
 
    // assertions
    assert (input.is_open());
    assert (output.is_open());
 
    // constants
    const auto MaxLengthOfSequence = static_cast<const int>(2e5);
    const auto MaxBase = static_cast<const long long int>(1e18);
    const auto MaxModulo = static_cast<const long long int>(1e18);
    const auto MaxNumberOfQueries = static_cast<const int>(2e5);
 
    // read from file and assertions
    long long base, modulo;
    assert (input >> base >> modulo);
    assert (isBetween(1LL, base, MaxBase));
    assert (isBetween(1LL, modulo, MaxModulo));
    string sequence;
    assert (input >> sequence);
    assert (isBetween(1, (int)sequence.size(), MaxLengthOfSequence));
    for (auto &letter : sequence)
    {
        // validate the input
        assert (isBetween('a', letter, 'z'));
    }
    // precompute the powers
    vector <long long> precomputedPowers (sequence.size() + 4);
    precomputedPowers[0] = 1;
    for (int currentExponent = 1; currentExponent <= sequence.size() + 3; ++ currentExponent)
    {
        precomputedPowers[currentExponent] = multiplication(precomputedPowers[currentExponent - 1],
                                                            base, modulo);
    }
    // read from file and assert
    int numberOfQueries;
    assert (input >> numberOfQueries);
    assert (isBetween(1, numberOfQueries, MaxNumberOfQueries));
    vector < pair < pair <long long, long long>, pair < pair <int, int>, int > > > queries (
            static_cast<unsigned int>(numberOfQueries));
    for (int currentQuery = 0; currentQuery < numberOfQueries; ++ currentQuery)
    {
        // for each query
        // read from file and assert
        long long moduloOne, moduloTwo;
        int lengthOne, lengthTwo;
        assert (input >> moduloOne >> moduloTwo >> lengthOne >> lengthTwo);
        assert (isBetween(0LL, moduloOne, MaxModulo));
        assert (isBetween(0LL, moduloTwo, MaxModulo));
        assert (isBetween(1, lengthOne, (int)sequence.size()));
        assert (isBetween(1, lengthTwo, (int)sequence.size()));
 
        queries [currentQuery] = {{moduloOne, moduloTwo}, {{lengthOne, lengthTwo}, currentQuery}};
    }
    // declare an instance
    PalindromicTree *PalTree = new PalindromicTree (sequence, base, modulo, precomputedPowers);
    // get the hashes from Pal Tree
    auto hashesFromPalTree = PalTree -> solve();
    // normalize
    normalize (hashesFromPalTree, queries);
    // sort back the queries
    sort (queries.begin(), queries.end(),
          [](const pair < pair <long long, long long>, pair < pair <int, int>, int > > &currentElement,
             const pair < pair <long long, long long>, pair < pair <int, int>, int > > &otherElement) -> bool {
              return currentElement.second.second < otherElement.second.second;
          });
    sort (hashesFromPalTree.begin(), hashesFromPalTree.end(), [](const pair <long long, pair <int, long long > > &currentPair,
                                                                 const pair <long long, pair <int, long long> > &otherPair) -> bool {
        return currentPair.second.first < otherPair.second.first;
    });
    // declare an instance
    auto *Tree = new PersistentSegmentTree((int)sequence.size(), (int)sequence.size() + 2 * numberOfQueries + 3);
    int currentPointer = 0;
    for (int currentLength = 1; currentLength <= (int)sequence.size(); ++ currentLength)
    {
        // build the persistance for all possible lengths
        if(currentPointer < (int)hashesFromPalTree.size())
        {
            assert(isBetween(1, (int) hashesFromPalTree[currentPointer].first, (int) sequence.size() + 2 * numberOfQueries + 3));
        }
        Tree -> fakeUpdate(currentLength);
        while (currentPointer < (int)hashesFromPalTree.size() and hashesFromPalTree [currentPointer].second.first < currentLength)
        {
            currentPointer += 1;
        }
        while (currentPointer < (int)hashesFromPalTree.size() and hashesFromPalTree [currentPointer].second.first == currentLength)
        {
            Tree -> updateRoot(currentLength, (int)hashesFromPalTree[currentPointer].first, hashesFromPalTree[currentPointer].second.second);
            currentPointer += 1;
        }
    }
    for (int currentQuery = 0; currentQuery < numberOfQueries; ++ currentQuery)
    {
        // for each query
        int lengthOne = queries [currentQuery].second.first.first;
        int lengthTwo = queries [currentQuery].second.first.second;
 
        auto _left = static_cast<int>(queries[currentQuery].first.first);
        auto _right = static_cast<int>(queries[currentQuery].first.second);
 
        // solve
        output << Tree -> rangeQuery(lengthOne, lengthTwo, _left, _right) << '\n';
    }
    return 0;
}
