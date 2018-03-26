/*Patrick Catalin Alexandru Sava
The University of Manchester
O (N(logN)^3)
Expected : Accepted*/
  
// libraries
#include <fstream>
#include <vector>
#include <bitset>
#include <queue>
#include <algorithm>
#include <cassert>
  
using namespace std;
  
// constants
const int MaxNumberOfNodes = static_cast<const int>(1e5);
const int MaxNumberOfEdges = static_cast<const int>(666013);
const long long MaxValue = static_cast<const long long int>(1e12);
  
template <typename T>
bool isBetween (T inf, T num, T sup)
{
    return inf <= num and num <= sup;
}// isBetween with template
  
vector <long long> sieve (int limit)
{
    // eratosthenes's  sieve
    const auto MAX = static_cast<const int>(1e6 + 14);
    bitset <MAX> isNotPrime;
    isNotPrime.reset();
    vector <long long> factors;
    for (int currentNumber = 2; currentNumber <= limit; ++ currentNumber)
    {
        if (isNotPrime [currentNumber] == 0)
        {
            for (int hasToBeNotPrime = currentNumber + currentNumber; hasToBeNotPrime <= limit;
                 hasToBeNotPrime += currentNumber)
            {
                isNotPrime[hasToBeNotPrime] = 1;
            }
            factors.push_back(currentNumber);
        }
    }
    return factors;
}// sieve
  
long long dijkstra (int numberOfNodes, vector < vector <int> > &graph, vector <long long> &valueOfNode,
                    long long primeFactor, int source, int destination, vector <int> &correspondingPath)
{
    vector <long long> distances (static_cast<unsigned int>(numberOfNodes + 1), (1LL << 61));
    // compare function for heap
    auto cmp = [](const pair <int, long long> &currentPair, const pair <int, long long> &otherPair) -> bool {
        return currentPair.second > otherPair.second;
    };
    vector <long long> cost (numberOfNodes + 1, 0);
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode) {
        long long temp = valueOfNode[currentNode];
        if (temp == 0) {
            // pay attention to this tricky case
            cost [currentNode] = 1LL << 35;
            continue;
        }
        while (temp % primeFactor == 0) {
            // increase the cost whilst temp divides primeFactor
            cost [currentNode] += 1;
            temp /= primeFactor;
        }
    }
    // execute dijkstra's algorithm
    priority_queue <pair <int, long long>, vector < pair <int, long long> >, decltype(cmp)> heap(cmp);
    distances[source] = cost [source];
    heap.push({source, distances[source]});
    vector <int> previous (numberOfNodes + 1, -1);
    while (!heap.empty())
    {
        auto info = heap.top();
  
        auto node = info.first;
        auto bestCost = info.second;
        heap.pop();
  
        if (distances[node] != bestCost)
        {
            continue;
        }
  
        for (auto &neighbour : graph[node])
        {
            if (distances [neighbour] > distances [node] + cost [neighbour])
            {
                distances [neighbour] = distances [node] + cost [neighbour];
                heap.push({neighbour, distances[neighbour]});
                previous [neighbour] = node;
            }
        }
    }
    // build path
    int currentNode = destination;
    while (true)
    {
        correspondingPath.push_back(currentNode);
        if (previous[currentNode] == -1)
        {
            break;
        }
        currentNode = previous [currentNode];
    }
    reverse(correspondingPath.begin(), correspondingPath.end());
    return distances[destination];
}// dijkstra
  
int main() {
    // streams
    ifstream input ("pesaptecarari.in");
    ofstream output ("pesaptecarari.out");
    // assertions and reading
    assert(input.is_open());
    assert(output.is_open());
    int numberOfNodes, numberOfEdges;
    long long target;
    assert(input >> numberOfNodes >> numberOfEdges >> target);
    assert(isBetween(1, numberOfNodes, MaxNumberOfNodes));
    assert(isBetween(1, numberOfEdges, MaxNumberOfEdges));
    assert(isBetween(1LL, target, MaxValue));
    vector <long long> valueOfNode(static_cast<unsigned int>(numberOfNodes + 1));
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode)
    {
        // foar each node
        assert(input >> valueOfNode [currentNode]);
        assert(isBetween(0LL, valueOfNode[currentNode], MaxValue));
    }
    vector < vector <int> > graph (static_cast<unsigned int>(numberOfNodes + 1));
    for (int currentEdge = 1; currentEdge <= numberOfEdges; ++ currentEdge)
    {
        // read each edge
        int firstNode, secondNode;
        assert(input >> firstNode >> secondNode);
        assert(isBetween(1, firstNode, numberOfNodes));
        assert(isBetween(1, secondNode, numberOfNodes));
        graph [firstNode].push_back(secondNode);
    }
    auto factors = sieve(1000000);
    const int source = 1;
    const int destination = numberOfNodes;
    // factorize target
    vector < pair <long long, int> > factorsAndExponents;
    for (auto &currentFactor : factors)
    {
        if (currentFactor * currentFactor > target)
        {
            break;
        }
        int times = 0;
        while (target % currentFactor == 0)
        {
            target /= currentFactor;
            times += 1;
        }
  
        if (times)
        {
            factorsAndExponents.emplace_back(currentFactor, times);
        }
    }
    if (target != 1LL)
    {
        factorsAndExponents.emplace_back(target, 1);
    }
    // get the solution
    long long solution = 1LL << 61;
    vector <int> pathWhichProducesTheBestSolution;
    for (auto &factorAndExponent : factorsAndExponents)
    {
        auto factor = factorAndExponent.first;
        auto exponent = factorAndExponent.second;
        vector <int> correspondingPath;
        auto bestSumOfExponent = dijkstra(numberOfNodes, graph, valueOfNode, factor, source,
                                          destination, correspondingPath);
  
        if (bestSumOfExponent / exponent < solution)
        {
            solution = bestSumOfExponent / exponent;
            pathWhichProducesTheBestSolution = correspondingPath;
        }
    }
    // print the solution
    output << solution << '\n';
    for (auto &currentNode : pathWhichProducesTheBestSolution)
    {
        output << currentNode << ' ' ;
    }
    output << '\n';
    return 0;
}// main
