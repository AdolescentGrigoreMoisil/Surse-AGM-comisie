/*Patrick Catalin Alexandru Sava
The University of Manchester
Max Flow of Minimal Cost
Expected: Accepted*/
 
#include <bits/stdc++.h>
 
using namespace std;
 
const int LabelMax = 1014;
 
int currentFlow [LabelMax][LabelMax];
int fixedCapacity [LabelMax][LabelMax];
 
int bellmanFord (vector < vector < pair <int, int> > > &graph, int numberOfNodes, vector <int> &previous)
{
    // bellman ford ahead
    const int infinite = 1 << 29;
    vector <int> dist (numberOfNodes + 1, infinite);
    vector <bool> isInQueue (static_cast<unsigned int>(numberOfNodes + 1), false);
    queue <int> heap;
    const int source = 0;
    heap.push(source);
    dist[source] = 0;
    isInQueue[source] = true;
 
    while (!heap.empty())
    {
        int nod = heap.front();
        isInQueue [nod] = false;
        heap.pop();
 
        for (auto &edge : graph[nod])
        {
            int where = edge.first;
            int cost = edge.second;
            if (dist [where] > dist [nod] + cost and currentFlow [nod][where] < fixedCapacity [nod][where]) {
                dist[where] = dist[nod] + cost;
                previous[where] = nod;
                if (!isInQueue[where])
                {
                    isInQueue[where] = true;
                    heap.push(where);
                }
            }
        }
    }
    // return the minimal cost to the destination
    return dist [numberOfNodes];
}
 
int flow (vector < pair <pair <int, int>, pair <int, int> > > &edges, int numberOfNodes)
{
    vector < vector <pair <int, int> > > graph (static_cast<unsigned int>(numberOfNodes + 1));
    for (auto &currentEdge : edges)
    {
        int from = currentEdge.first.first;
        int to = currentEdge.first.second;
        int capacity = currentEdge.second.first;
        int cost = currentEdge.second.second;
 
        currentFlow [from][to] = 0;
        fixedCapacity [from][to] = capacity;
        graph [from].emplace_back(to, cost);
    }
    const int forbidden = -1;
    vector <int> previous (static_cast<unsigned int>(numberOfNodes + 1), forbidden);
    const int infinite = 1 << 29;
    int answer = 0;
    // solve the maximum flow of minimum cost here
    while (true)
    {
        int bestDistance = bellmanFord(graph, numberOfNodes, previous);
        if (bestDistance >= infinite)
        {
            break;
        }
 
        int partialFlow = infinite;
 
        for (int currentNode = numberOfNodes ; previous [currentNode] != forbidden ; currentNode = previous[currentNode])
        {
            int from = previous [currentNode];
            int to = currentNode;
 
            partialFlow = min (partialFlow, fixedCapacity [from][to] - currentFlow [from][to]);
        }
 
        for (int currentNode = numberOfNodes ; previous [currentNode] != forbidden ; currentNode = previous[currentNode])
        {
            int from = previous [currentNode];
            int to = currentNode;
 
            currentFlow [from][to] += partialFlow;
            currentFlow [to][from] -= partialFlow;
        }
 
        answer += partialFlow * bestDistance;
    }
 
    graph.clear();
    for (auto &currentEdge : edges)
    {
        int from = currentEdge.first.first;
        int to = currentEdge.first.second;
 
        currentFlow [from][to] = 0;
        fixedCapacity [from][to] = 0;
    }
 
    return answer;
}
 
bool inserted [LabelMax][LabelMax];
 
bool canDestroy(int numberOfBeatenEnemies, int myMinionsAttack, int myMinionsDefensive,
                vector < pair <int, int> > &enemies) {
    const int source = 0;
    const int destination = numberOfBeatenEnemies + enemies.size() + 1;
 
    //                    from to    capacity  cost
    vector < pair < pair <int, int>, pair <int, int> > > edges;
 
    // insert edges and remove duplicates
    auto insertEdges = [&](int from, int to, int capacity, int cost) -> void {
        if (inserted [from][to])
        {
            return;
        }
        inserted [from][to] = inserted [to][from] = true;
        edges.push_back({{from, to}, {capacity, cost}});
        edges.push_back({{to, from}, {0, -cost}});
    };
 
    // on the first column is the source
    // on the second there are the real enemies
    for (int indexOfEnemy = 0; indexOfEnemy < (int)enemies.size(); ++ indexOfEnemy)
    {
        const int currentNodeLabelForEnemy = indexOfEnemy + 1;
        const int capacity = 1;
        const int cost = 0;
 
        insertEdges(source, currentNodeLabelForEnemy, capacity, cost);
    }
 
 
    for (int indexOfEnemy = 0; indexOfEnemy < (int)enemies.size(); ++ indexOfEnemy)
    {
        const int correspondingNode = indexOfEnemy + 1;
        int lastCost = 0;
        int lastNode = 0;
        // on the third there are the fake enemies
        for (int minionsAttack = myMinionsAttack; minionsAttack < myMinionsAttack + numberOfBeatenEnemies; ++ minionsAttack)
        {
            const int currentNodeLabelForEnemy = (int)enemies.size() + minionsAttack - myMinionsAttack + 1;
            const int capacity = 1;
            const int computedCost = (enemies[indexOfEnemy].second / minionsAttack +
                                      (enemies[indexOfEnemy].second % minionsAttack != 0)) *
                                     enemies[indexOfEnemy].first;
            // CRUCIAL OPTIMISATION AHEAD
            if (computedCost == lastCost)
            {
                const int cost = 0;
                insertEdges(lastNode, currentNodeLabelForEnemy, capacity, cost);
            }
            else
            {
                lastCost = computedCost;
                lastNode = currentNodeLabelForEnemy;
                insertEdges(correspondingNode, currentNodeLabelForEnemy, capacity, computedCost);
            }
        }
    }
 
    for (int fakeMinion = (int)enemies.size() + 1; fakeMinion < destination; ++ fakeMinion)
    {
        const int capacity = 1;
        const int cost = 0;
        // connect the third column with the last one, on which is the destination node
        insertEdges(fakeMinion, destination, capacity, cost);
    }
    for (auto &edge : edges)
    {
        // clear the memo here
        inserted[edge.first.first][edge.first.second] = false;
    }
    // if the total damage is strictly less than the minion's defensive power + the binary searched answer - 1
    return flow(edges, destination) < myMinionsDefensive + numberOfBeatenEnemies - 1;
}
 
int main() {
    // streams
    ifstream input ("hsattack.in");
    ofstream output ("hsattack.out");
 
    // assertions
    assert(input.is_open());
    assert(output.is_open());
 
    // assertions and constants
    auto isBetween = [](const int inf, const int currentNumber, const int sup) -> bool {
        return inf <= currentNumber and currentNumber <= sup;
    };
    const int MaxNumberOfTests = 20;
    const int MaxNumberOfMinions = 500;
    const int MaxTotalNumberOfMinions = 4000;
    const auto MaxPowerAndMaxDamage = static_cast<const int>(1e4);
    int numberOfTests;
    assert(input >> numberOfTests);
    assert(isBetween(1, numberOfTests, MaxNumberOfTests));
    int totalNumberOfMinions = 0;
    for (int currentTest = 1; currentTest <= numberOfTests; ++ currentTest)
    {
        // for each test read and assert
        int myMinionsAttack, myMinionsDefensive;
        assert(input >> myMinionsAttack >> myMinionsDefensive);
        assert(isBetween(1, myMinionsAttack, MaxPowerAndMaxDamage));
        assert(isBetween(1, myMinionsDefensive, MaxPowerAndMaxDamage));
        totalNumberOfMinions += 1;
 
        int numberOfComputersMinions;
        assert(input >> numberOfComputersMinions);
        assert(isBetween(1, numberOfComputersMinions, MaxNumberOfMinions));
        totalNumberOfMinions += numberOfComputersMinions;
 
        vector < pair <int, int> > enemies;
        for (int currentMinionOfComputer = 1; currentMinionOfComputer <= numberOfComputersMinions; ++ currentMinionOfComputer)
        {
            // read the properties of each minion
            int attack, defensive;
            assert(input >> attack >> defensive);
            assert(isBetween(1, attack, MaxPowerAndMaxDamage));
            assert(isBetween(1, defensive, MaxPowerAndMaxDamage));
            enemies.emplace_back(attack, defensive);
        }
 
        // suppose now that we know how many minions I will destroy
        // it is correct to binary search the number
        int _left = 0;
        int _right = numberOfComputersMinions;
        int solution = 0;
 
        while (_left <= _right)
        {
            int numberOfBeatenEnemies = (_left + _right) >> 1;
 
            if (canDestroy(numberOfBeatenEnemies, myMinionsAttack, myMinionsDefensive, enemies))
            {
                // good? go in right
                solution = numberOfBeatenEnemies;
                _left = numberOfBeatenEnemies + 1;
            }
            else
            {
                // otherwise go in left
                _right = numberOfBeatenEnemies - 1;
            }
        }
 
        output << solution << '\n';
    }
    assert(isBetween(1, totalNumberOfMinions, MaxTotalNumberOfMinions));
    return 0;
}
