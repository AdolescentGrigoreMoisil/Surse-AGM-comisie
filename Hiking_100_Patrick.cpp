/// Patrick Catalin Alexandru Sava
#include <iostream>
#include <cassert>
#include <vector>

using namespace std;

void assertIsBetween (int inf, int number, int sup)
{
    assert(inf <= number and number <= sup);
}

void getComponent (int node, const vector < vector < pair <int, int > > > &graph,
                   vector <int> &componentNodeNumber, const int componentNumber)
{
    componentNodeNumber[node] = componentNumber;
    for (auto &info : graph[node])
    {
        auto neighbour = info.first;
        auto cost = info.second;

        if (cost or componentNodeNumber[neighbour]) continue;
        getComponent(neighbour, graph, componentNodeNumber, componentNumber);
    }
}

void buildColors (int node, int currentColor, const int currentComponent, const vector < vector <int> > &graph,
                  vector <int> &where, vector <int> &color)
{
    color[node] = currentColor;
    where[node] = currentComponent;
    if (color [node] == 3)
    {
        for (auto &neighbour : graph[node])
            if (color[neighbour] != 3)
                buildColors(neighbour, 3, currentComponent, graph, where, color);
    }
    else
    {
        for (auto &neighbour : graph[node])
            if (color[neighbour] == 0)
                buildColors(neighbour, 3 - currentColor, currentComponent, graph, where, color);
            else if (3 - currentColor != color[neighbour])
                buildColors(neighbour, 3, currentComponent, graph, where, color);
    }
}

int main() {
    const auto NMAX = static_cast<const int>(1e5);
    const auto MMAX = static_cast<const int>(2e5);
    const auto QMAX = static_cast<const int>(1e5);
    const auto LENMAX = static_cast<const int>(1e9);
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    int numberOfNodes, numberOfEdges, numberOfQueries;
    assert(cin >> numberOfNodes >> numberOfEdges >> numberOfQueries);
    assertIsBetween(1, numberOfNodes, NMAX);
    assertIsBetween(1, numberOfEdges, MMAX);
    assertIsBetween(1, numberOfQueries, QMAX);
    vector < vector < pair <int, int> > > graph (static_cast<unsigned int>(numberOfNodes + 1));
    while (numberOfEdges --)
    {
        int node1, node2, len;
        assert(cin >> node1 >> node2 >> len);
        assertIsBetween(1, len, LENMAX);
        graph[node1].emplace_back(node2, len % 2);
        graph[node2].emplace_back(node1, len % 2);
    }
    vector <int> componentNumber (numberOfNodes + 1, 0);
    int currentNumberOfComponents = 0;
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode)
    {
        if (componentNumber[currentNode] == 0)
        {
            ++ currentNumberOfComponents;
            getComponent(currentNode, graph, componentNumber, currentNumberOfComponents);
        }
    }
    vector < vector < int > > compressedGraph(static_cast<unsigned int>(currentNumberOfComponents + 1));
    for (int currentNode = 1; currentNode <= numberOfNodes; ++ currentNode)
    {
        for (auto &info : graph[currentNode])
        {
            auto neighbour = info.first;

            if (componentNumber[neighbour] != componentNumber[currentNode])
            {
                compressedGraph[componentNumber[neighbour]].push_back(componentNumber[currentNode]);
                compressedGraph[componentNumber[currentNode]].push_back(componentNumber[neighbour]);
            }
        }
    }
    vector <int> where (static_cast<unsigned int>(currentNumberOfComponents + 1), 0);
    vector <int> color (currentNumberOfComponents + 1, 0);
    int currentLabel = 0;
    for (int currentNode = 1; currentNode <= currentNumberOfComponents; ++ currentNode)
    {
        if (where [currentNode]) continue;
        buildColors(currentNode, 1, ++ currentLabel, compressedGraph, where, color);
    }
    while (numberOfQueries --)
    {
        int node1, node2, parity;
        assert(cin >> node1 >> node2 >> parity);
        assertIsBetween(1, node1, numberOfNodes);
        assertIsBetween(1, node2, numberOfNodes);
        assertIsBetween(0, parity, 1);

        node1 = componentNumber[node1];
        node2 = componentNumber[node2];

        if (where[node1] != where [node2])
        {
            cout << 0 << '\n';
        }
        else
        {
            if (color[node1] == 3)
            {
                assert(color[node2] == 3);
                cout << 1 << '\n';
            }
            else if (color [node1] == color [node2])
            {
                cout << (parity == 0) << '\n';
            }
            else
            {
                cout << (parity == 1) << '\n';
            }
        }
    }
    return 0;
}
