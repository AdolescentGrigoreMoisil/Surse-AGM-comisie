#include <bits/stdc++.h>

using namespace std;


void buildComponents (int node, vector <bool> &visited, vector <int> &currentComponent, vector <vector <pair <int, int>>> &initialGraph, vector <int> &where, int componentNumber) {
    currentComponent.push_back(node);
    where[node] = componentNumber;
    visited[node] = true;
    for (auto x : initialGraph[node]) {
        if (x.second) continue;
        if (visited[x.first]) continue;
        buildComponents(x.first, visited, currentComponent, initialGraph, where, componentNumber);
    }
}

void buildNewGraph (vector <vector <int>> &newGraph, vector <vector <int>> &components, int numberOfNodes, vector <int> &where, vector <vector <pair <int, int>>> &initialGraph, vector <int> &colors, vector <int> &inWhich) {
    newGraph.resize(components.size() + 1);
    colors.resize(components.size() + 1);
    inWhich.resize(components.size() + 1);
    for (int i = 1; i <= numberOfNodes; ++i) {
        for (auto x : initialGraph[i]) {
            if (where[i] != where[x.first]) {
                newGraph[where[i]].push_back(where[x.first]);
                newGraph[where[x.first]].push_back(where[i]);
            }
        }
    }
}

void buildConnectedComponents (int node, int number, vector <vector <int>> &graph, vector <int> &inWhich) {
    inWhich[node] = number;
    for (auto x : graph[node]) {
        if (inWhich[x]) continue;
        buildConnectedComponents(x, number, graph, inWhich);
    }
}

void buildColors (int node, int currentColor, vector < vector <int>> &graph, vector <int> &colors) {
    colors[node] = currentColor;
    if (currentColor == 3) {
        for (auto x : graph[node]) {
            if (colors[x] == 3) continue;
            buildColors(x, currentColor, graph, colors);
        }
    }
    else {
        int nextColor = 3 - currentColor;
        for (auto x : graph[node]) {
            if (colors[x]) {
                if (colors[x] != nextColor) {
                    buildColors(x, 3, graph, colors);
                }
            }
            else {
                buildColors(x, nextColor, graph, colors);
            }
        }
    }
}

int typeBigNodes (int x, int y, vector <int> &inWhich, vector <int> &colors) {
    if (inWhich[x] != inWhich[y]) return 0;
    if (colors[x] == 3) return 3;
    if (colors[x] == colors[y]) return 1;
    return 2;
}

int typeNormalNodes (int x, int y, vector <int> &where, vector <int> &inWhich, vector <int> &colors) {
    return typeBigNodes(where[x], where[y], inWhich, colors);
}

set <pair <int, int>> edges;

int main() {
//    freopen ("input", "r", stdin);
//    freopen ("output", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    cout.tie(nullptr);
    vector <vector <pair <int, int>>> initialGraph;
    vector <vector <int>> compressedGraph;
    vector <vector <int>> components;
    vector <int> where;
    vector <bool> visited;
    vector <int> inWhich;
    vector <int> colors;
    int numberOfNodes, numberOfEdges, numberOfQueries;
    assert (cin >> numberOfNodes >> numberOfEdges >> numberOfQueries);
    assert (1 <= numberOfNodes and numberOfNodes <= 100000);
    assert (1 <= numberOfEdges and numberOfEdges <= 200000);
    assert (1 <= numberOfQueries and numberOfQueries <= 100000);
    where.resize(static_cast<unsigned int>(numberOfNodes + 1));
    initialGraph.resize(static_cast<unsigned int>(numberOfNodes + 1));
    visited.resize(static_cast<unsigned int>(numberOfNodes + 1), false);
    for (int i = 0; i < numberOfEdges; ++i) {
        int nodeLeft, nodeRight, length;
        assert (cin >> nodeLeft >> nodeRight >> length);
        assert (1 <= nodeLeft and nodeLeft <= numberOfNodes);
        assert (1 <= nodeRight and nodeRight <= numberOfNodes);
        assert (nodeLeft != nodeRight);
        assert (1 <= length and length <= 1000000000);
        assert (edges.find({nodeLeft, nodeRight}) == edges.end());
        edges.insert({nodeLeft, nodeRight});
        edges.insert({nodeRight, nodeLeft});
        length %= 2;
        initialGraph[nodeRight].emplace_back(nodeLeft, length);
        initialGraph[nodeLeft].emplace_back(nodeRight, length);
    }
    for (int i = 1; i <= numberOfNodes; ++i) {
        if (visited[i]) continue;
        vector <int> current;
        buildComponents(i, visited, current, initialGraph, where, components.size() + 1);
        components.push_back(current);
    }
    buildNewGraph(compressedGraph, components, numberOfNodes, where, initialGraph, colors, inWhich);
    int numberOfConnectedComponents = 0;
    for (int i = 1; i < compressedGraph.size(); ++i) {
        if (inWhich[i]) continue;
        numberOfConnectedComponents += 1;
        buildConnectedComponents(i, numberOfConnectedComponents, compressedGraph, inWhich);
    }
    for (int i = 1; i < compressedGraph.size(); ++i) {
        if (colors[i]) continue;
        buildColors(i, 1, compressedGraph, colors);
    }
    for (int i = 1; i <= numberOfQueries; ++i) {
        int x, y, query;
        assert (cin >> x >> y >> query);
        assert (1 <= x and x <= numberOfNodes);
        assert (1 <= y and y <= numberOfNodes);
        assert (0 <= query and query <= 1);
        int type = typeNormalNodes(x, y, where, inWhich, colors);
        cout << ((type & (1 << query)) != 0) << '\n';
    }
    return 0;
}
