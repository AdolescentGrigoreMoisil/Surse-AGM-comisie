/*
 * Vlad-Andrei Munteanu
 * Patrick Catalin Alexandru Sava
 * University: University of Manchester
 * Problem: Pe ape si mai tulburi
 * Author: Vlad-Andrei Munteanu
 * Contest: "Adolescent Grigore Moisil"
 * Expected: Accepted
 */
#include <bits/stdc++.h>
 
using namespace std;
 
//Declarations - begin
const int MAXN = static_cast<const int>(1e5);
const int MAXLevel = static_cast<const int>(1e8);
const int MAXEdges = static_cast<const int>(2e5);
const int MAXCost = static_cast<const int>(1e5);
const int MINCost = static_cast<const int>(-1e5);
const long long INF = 1LL << 55;
const long long MINF = -(1LL << 55);
const long long MaxPossibleValue = static_cast<const long long int>(2e10);
const long long MinPossibleValue = static_cast<const long long int>(-2e10);
vector <vector <pair<int, long long>>> graph;
vector <vector <pair<int, long long>>> reversedGraph;
vector <vector <int>> graphSCC;
vector <vector <long long>> dp (2);
vector <int> SCC[MAXN + 1];
vector <int> nodesA;
vector <int> nodesB;
vector <int> nodesC;
vector <int> currentSCC;
vector <int> sortedSCC;
int heightOfSCC[MAXN + 1];
int minLevelInDFS[MAXN + 1];
int buildFinalSCC[MAXN + 1];
int inverse [MAXN + 1];
bool visited[MAXN + 1];
//Declarations - end
 
void readIt (int& numberOfNodes, int& numberOfEdges) {
    int numberOfA, numberOfB, numberOfC;
    ifstream fin ("peapesimaitulburi.in");
    assert (fin >> numberOfNodes >> numberOfEdges);
    assert (1 <= numberOfNodes and numberOfNodes <= MAXN);
    assert (1 <= numberOfEdges and numberOfEdges <= MAXEdges);
    currentSCC.resize(static_cast<unsigned int>(numberOfNodes + 1));
    graph.resize(static_cast<unsigned int>(numberOfNodes + 1));
    reversedGraph.resize(static_cast<unsigned int>(numberOfNodes + 1));
    for (int currentEdge = 0; currentEdge < numberOfEdges; ++currentEdge) {
        int source, target, cost;
        assert (fin >> source >> target >> cost);
        assert (1 <= source and source <= numberOfNodes);
        assert (1 <= target and target <= numberOfNodes);
        assert (MINCost <= cost and cost <= MAXCost);
        graph[source].emplace_back(target, cost);
        reversedGraph[target].emplace_back(source, cost);
    }
    assert (fin >> numberOfA);
    assert (0 <= numberOfA and numberOfA <= MAXN);
    for (int currentNode = 0; currentNode < numberOfA; ++currentNode) {
        int currentNodeA;
        assert (fin >> currentNodeA);
        assert (1 <= currentNodeA and currentNodeA <= numberOfNodes);
        nodesA.push_back(currentNodeA);
    }
    assert (fin >> numberOfB);
    assert (0 <= numberOfB and numberOfB <= MAXN);
    for (int currentNode = 0; currentNode < numberOfB; ++currentNode) {
        int currentNodeB;
        assert (fin >> currentNodeB);
        assert (1 <= currentNodeB and currentNodeB <= numberOfNodes);
        nodesB.push_back(currentNodeB);
    }
    assert (fin >> numberOfC);
    assert (0 <= numberOfC and numberOfC <= MAXN);
    for (int currentNode = 0; currentNode < numberOfC; ++currentNode) {
        int currentNodeC;
        assert (fin >> currentNodeC);
        assert (1 <= currentNodeC and currentNodeC <= numberOfNodes);
        nodesC.push_back(currentNodeC);
    }
} //readIt
 
void prepareIt (int numberOfNodes) {
    dp[0].resize(static_cast<unsigned int>(numberOfNodes + 1));
    dp[1].resize(static_cast<unsigned int>(numberOfNodes + 1));
    for (int currentNode = 1; currentNode <= numberOfNodes; ++currentNode) {
        dp[0][currentNode] = dp[1][currentNode] = INF;
        currentSCC[currentNode] = currentNode;
        heightOfSCC[currentNode] = 1;
        minLevelInDFS[currentNode] = MAXLevel;
        visited[currentNode] = false;
    }
} //prepareIt
 
int getComponent (int currentElement) {
    int currentKing = currentElement;
    while (currentSCC[currentKing] != currentKing) {
        currentKing = currentSCC[currentKing];
    }
    while (currentElement != currentKing) {
        int copyOfElement = currentElement;
        currentElement = currentSCC[copyOfElement];
        currentSCC[copyOfElement] = currentKing;
    }
    return currentKing;
} //getComponent
 
void uniteComponents (int firstElement, int secondElement) {
    int firstComponent = getComponent(firstElement);
    int secondComponent = getComponent(secondElement);
    if (firstComponent == secondComponent) {
        return;
    }
    if (heightOfSCC[firstComponent] < heightOfSCC[secondComponent]) {
        swap (firstComponent, secondComponent);
    }
    if (heightOfSCC[firstComponent] == heightOfSCC[secondComponent]) {
        ++heightOfSCC[firstComponent];
    }
    currentSCC[secondComponent] = firstComponent;
    minLevelInDFS[firstComponent] = min (minLevelInDFS[firstComponent], minLevelInDFS[secondComponent]);
} //uniteComponents
 
void solveIt (int node, int currentLevel) {
    int componentOfNode = getComponent(node);
    minLevelInDFS[componentOfNode] = min (minLevelInDFS[componentOfNode], currentLevel);
    visited[node] = true;
    for (auto currentNeighbour : graph[node]) {
        if (!visited[currentNeighbour.first]) {
            solveIt(currentNeighbour.first, currentLevel + 1);
        }
        int componentOfNeighbour = getComponent(currentNeighbour.first);
        if (minLevelInDFS[componentOfNeighbour] < currentLevel) {
            uniteComponents(node, currentNeighbour.first);
        }
    }
    componentOfNode = getComponent(node);
    if (minLevelInDFS[componentOfNode] == currentLevel) {
        minLevelInDFS[componentOfNode] = MAXLevel;
    }
} //solveIt
 
vector <long long> dijkstra (vector <int>& SCC, vector <vector <pair <int, long long>>> &graph, vector <long long>& distances, vector <int> &where, int currentSCC) {
    auto numberOfNodesFromComponent = (int)distances.size();
    vector <long long> dist(static_cast<unsigned int>(numberOfNodesFromComponent + 1), 0LL);
    for (int ind = 0; ind < (int)SCC.size(); ++ ind) {
        dist [ind] = distances [ind];
        inverse [SCC[ind]] = ind;
    }
    auto cmp = [](pair <int, long long> &currentPair, pair <int, long long> &otherPair) -> bool {
        return currentPair.second > otherPair.second;
    };
    priority_queue <pair <int, long long>, vector <pair <int, long long> > , decltype(cmp)> heap(cmp);
    for (auto &currentNode : SCC) {
        heap.push({currentNode, dist[inverse[currentNode]]});
    }
    while (heap.size()) {
        auto info = heap.top();
        auto node = info.first;
        auto cost = info.second;
        heap.pop();
        if (dist[inverse[node]] != cost)
            continue;
 
        for (auto infoForNeighbour: graph[node]) {
            int neighbour = infoForNeighbour.first;
            long long costOfEdge = infoForNeighbour.second;
            if (where [neighbour] != currentSCC) {
                continue;
            }
            else {
                assert(0 <= costOfEdge);
                if (dist [inverse[neighbour]] > dist [inverse[node]] + costOfEdge) {
                    dist [inverse[neighbour]] = dist [inverse[node]] + costOfEdge;
                    heap.push({neighbour, dist [inverse[neighbour]]});
                }
            }
        }
    }
    return dist;
} //dijkstra
 
vector <long long> bellmanFord (vector <int>& SCC, vector <vector <pair <int, long long>>> &graph, vector <long long>& distances, vector <int> &where, int currentSCC) {
    auto numberOfNodesFromComponent = (int)distances.size();
    vector <long long> dist(numberOfNodesFromComponent + 1, 0);
    for (int ind = 0; ind < (int)SCC.size(); ++ ind) {
        dist [ind] = distances [ind];
        inverse [SCC[ind]] = ind;
    }
    queue <int> Queue;
    vector <bool> inQueue (static_cast<unsigned int>(numberOfNodesFromComponent + 1), true);
    vector <int> times (numberOfNodesFromComponent + 1, 0);
    for (auto &currentNode : SCC) {
        Queue.push(currentNode);
    }
    bool negativeCycle = false;
    while (!Queue.empty()) {
        auto node = Queue.front();
        inQueue [inverse[node]] = false;
        times [inverse [node]] += 1;
 
        if (times [inverse[node]] > numberOfNodesFromComponent + 1) {
            negativeCycle = true;
            break;
        }
        Queue.pop();
 
        for (auto infoForNeighbour: graph[node]) {
            int neighbour = infoForNeighbour.first;
            long long costOfEdge = infoForNeighbour.second;
            if (where [neighbour] != currentSCC) {
                continue;
            }
            else {
                if (dist [inverse[neighbour]] > dist [inverse[node]] + costOfEdge) {
                    dist [inverse[neighbour]] = dist [inverse[node]] + costOfEdge;
                    Queue.push(neighbour);
                }
            }
        }
    }
    if (negativeCycle) {
        for (auto &elem : dist) {
            elem = MINF;
        }
    }
    return dist;
} //bellmanFord
 
vector <int> topologicalSorting (vector < vector <int>> &graph) {
    int numberOfNodes = (int)graph.size() - 1;
    vector <int> grade (numberOfNodes + 1, 0);
 
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode) {
        for (auto &neighbour : graph [currentNode]) {
            grade [neighbour] += 1;
        }
    }
    queue <int> Queue;
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode) {
        if (grade [currentNode] == 0) {
            Queue.push(currentNode);
        }
    }
    vector <int> solution;
    while (!Queue.empty()) {
        int node = Queue.front();
        Queue.pop();
        solution.push_back (node);
        for (auto &neighbour : graph [node]) {
            -- grade [neighbour];
 
            if (grade [neighbour] == 0) {
                Queue.push(neighbour);
            }
        }
    }
    return solution;
} //topologicalSorting
 
vector <vector<int>> buildSCCGraph (vector < vector < pair <int, long long> > > & graph, int numberOfSCC, vector <int> &where) {
    int numberOfNodes = (int)where.size() - 1; // indexed from 1
    vector < vector <int> > solution (static_cast<unsigned int>(numberOfSCC + 1));
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode) {
        for (auto &info : graph [currentNode]) {
            auto neigh = info.first;
            if (where [currentNode] != where [neigh]) {
                solution[where[currentNode]].push_back(where[neigh]);
            }
        }
    }
    return solution;
}
void solveOneSCC (vector <long long>& dp, int currentSCC, vector <int>& where, vector <vector <pair <int, long long>>>& graph) {
    vector <long long> currentDp (SCC[currentSCC].size());
    for (auto node : SCC[currentSCC]) {
        for (auto neigh : graph[node]) {
            if (where[neigh.first] == where[node]) {
                continue;
            }
            if (dp[node] > dp[neigh.first] + neigh.second) {
                dp[node] = dp[neigh.first] + neigh.second;
            }
        }
    }
    bool onlyINF = true;
    bool onlyMINF = true;
    for (auto node : SCC[currentSCC]) {
        if (dp[node] <= MaxPossibleValue) {
            onlyINF = false;
        }
        if (MinPossibleValue <= dp[node]) {
            onlyMINF = false;
        }
    }
    if (onlyINF) {
        for (auto node : SCC[currentSCC]) {
            dp[node] = INF;
        }
        return ;
    }
    if (onlyMINF) {
        for (auto node : SCC[currentSCC]) {
            dp[node] = MINF;
        }
        return ;
    }
    for (int currentNode = 0; currentNode < SCC[currentSCC].size(); ++currentNode) {
        currentDp[currentNode] = dp[SCC[currentSCC][currentNode]];
    }
    if (SCC[currentSCC].size() <= 50) {
        currentDp = bellmanFord(SCC[currentSCC], reversedGraph, currentDp, where, currentSCC);
    }
    else {
        currentDp = dijkstra(SCC[currentSCC], reversedGraph, currentDp, where, currentSCC);
    }
    for (int currentNode = 0; currentNode < SCC[currentSCC].size(); ++currentNode) {
        dp[SCC[currentSCC][currentNode]] = currentDp[currentNode];
    }
} //solveOneSCC
int main() {
    ofstream fout ("peapesimaitulburi.out");
    int numberOfNodes, numberOfEdges;
    readIt(numberOfNodes, numberOfEdges);
    prepareIt(numberOfNodes);
    for (int currentNode = 1; currentNode <= numberOfNodes; ++currentNode) {
        if (!visited[currentNode]) {
            solveIt(currentNode, 1);
        }
    }
    int howmanySCC = 0;
    for (int currentNode = 1; currentNode <= numberOfNodes; ++currentNode) {
        if (currentNode == currentSCC[currentNode]) {
            ++howmanySCC;
        }
    }
    int currentIndexSCC = 0;
    for (int currentNode = 1; currentNode <= numberOfNodes; ++currentNode) {
        int where = getComponent(currentNode);
        if (buildFinalSCC[where]) {
            SCC[buildFinalSCC[where]].push_back(currentNode);
        }
        else {
            ++currentIndexSCC;
            buildFinalSCC[where] = currentIndexSCC;
            SCC[buildFinalSCC[where]].push_back(currentNode);
        }
    }
    for (int i = 1; i <= howmanySCC; ++i) {
        for (auto x:SCC[i]) {
            currentSCC[x] = i;
        }
    }
    graphSCC = buildSCCGraph(graph, howmanySCC, currentSCC);
    sortedSCC = topologicalSorting(graphSCC);
    reverse (sortedSCC.begin(), sortedSCC.end());
    for (auto node : nodesC) {
        dp[0][node] = 0;
    }
    for (auto current : sortedSCC) {
        solveOneSCC(dp[0], current, currentSCC, graph);
    }
    for (auto node : nodesB) {
        dp[1][node] = dp[0][node];
    }
    for (auto current : sortedSCC) {
        solveOneSCC(dp[1], current, currentSCC, graph);
    }
    for (auto node : nodesA) {
        if (dp[1][node] < MinPossibleValue) {
            fout << "-INF\n";
            continue;
        }
        if (dp[1][node] > MaxPossibleValue) {
            fout << "INF\n";
            continue;
        }
        fout << dp[1][node] << '\n';
    }
    return 0;
} //main
