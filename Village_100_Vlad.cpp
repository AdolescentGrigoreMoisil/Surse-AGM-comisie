/*
 * Vlad-Andrei Munteanu
 * Problem: Village
 * Author: Tamio Nakajima-Vesa
 * Expected: Accepted
 */

#include <bits/stdc++.h>

using namespace std;

class MaxFlow {
public:
    MaxFlow (int source, int destination, int numberOfNodes) {
        this->source = source;
        this->destination = destination;
        this->numberOfNodes = numberOfNodes;
        flow.resize(static_cast<unsigned int>(numberOfNodes));
        capacities.resize(static_cast<unsigned int>(numberOfNodes));
        graph.resize(static_cast<unsigned int>(numberOfNodes));
        for (int i = 0; i < numberOfNodes; ++i) {
            flow[i].resize(static_cast<unsigned int>(numberOfNodes), 0);
            capacities[i].resize(static_cast<unsigned int>(numberOfNodes), 0);
        }
    }

    void AddEdge (int source, int destination, int capacity) {
        addEdge (source, destination, capacity);
    }

    int GetFlow (int source, int destination) {
        return flow[source][destination];
    }

    int GetMaxFlow () {
        return getMaxFlow(numberOfNodes, source, destination);
    }

private:
    //declarations - begin
    const int INF = 2000000000;
    int source, destination, numberOfNodes;
    vector <vector <int>> flow;
    vector <vector <int>> capacities;
    vector <vector <int>> graph;
    //declarations - end

    void addEdge (int source, int destination, int capacity) {
        capacities[source][destination] += capacity;
        graph[source].push_back(destination);
        graph[destination].push_back(source);
    }

    int getMaxFlow (int numberOfNodes, int source, int destination) {
        int maxFlow = 0;
        while (true) {
            vector <int> distances (static_cast<unsigned int>(numberOfNodes));
            bfs (distances, source, destination, numberOfNodes);
            int currentFlow = dfs (distances, source, destination, INF, numberOfNodes);
            if (!currentFlow) return maxFlow;
            maxFlow += currentFlow;
        }
    }

    void bfs (vector <int>& distances, int source, int destination, int numberOfNodes) {
        queue <int> q;
        for (int i = 0; i < numberOfNodes; ++i) {
            distances[i] = INF;
        }
        distances[source] = 0;
        q.push(source);
        while (!q.empty()) {
            int currentNode = q.front();
            q.pop();
            if (currentNode == destination) continue;
            for (auto next : graph[currentNode]) {
                if (capacities[currentNode][next] == flow[currentNode][next]) continue;
                if (distances[currentNode] + 1 >= distances[next]) continue;
                distances[next] = distances[currentNode] + 1;
                q.push(next);
            }
        }
    }

    int dfs (vector <int>& distances, int node, int destination, int maxFlow, int numberOfNodes) {
        int totalFlow = 0;
        if (maxFlow == 0) return 0;
        if (node == destination) return maxFlow;
        for (auto i : graph[node]) {
            if (distances[node] + 1 != distances[i]) continue;
            int currentFlow = dfs (distances, i, destination, min (maxFlow - totalFlow, capacities[node][i] - flow[node][i]), numberOfNodes);
            totalFlow += currentFlow;
            flow[node][i] += currentFlow;
            flow[i][node] -= currentFlow;
        }
        return totalFlow;
    }
};

int main() {
//    freopen ("input", "r", stdin);
    int tests;
    cin >> tests;
    while (tests--) {
        vector <int> x, y;
        vector <vector <int>> a, b, answer;
        int n, m;
        assert (cin >> n >> m);
        x.resize(static_cast<unsigned int>(n));
        y.resize(static_cast<unsigned int>(m));
        a.resize(static_cast<unsigned int>(n));
        b.resize(static_cast<unsigned int>(n));
        answer.resize(static_cast<unsigned int>(n));
        for (auto &line : a) {
            line.resize(static_cast<unsigned int>(m));
        }
        for (auto &line : b) {
            line.resize(static_cast<unsigned int>(m));
        }
        for (auto &line : answer) {
            line.resize(static_cast<unsigned int>(m));
        }
        for (int i = 0; i < n; ++i) {
            assert (cin >> x[i]);
            assert (-1000000000 <= x[i] and x[i] <= 1000000000);
        }
        for (int i = 0; i < m; ++i) {
            assert (cin >> y[i]);
            assert (-1000000000 <= y[i] and y[i] <= 1000000000);
        }
        int minVal = 100000000;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                assert (cin >> a[i][j]);
                assert (-10000000 <= a[i][j] and a[i][j] <= 10000000);
                minVal = min (a[i][j], minVal);
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] -= minVal;
                x[i] -= minVal;
                y[j] -= minVal;
            }
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                assert (cin >> b[i][j]);
                b[i][j] -= minVal;
                assert (a[i][j] <= b[i][j] and b[i][j] + minVal <= 10000000);
                b[i][j] -= a[i][j];
                x[i] -= a[i][j];
                y[j] -= a[i][j];
            }
        }
        bool validate2 = true;
        auto *myFlow = new MaxFlow (0, n + m + 1, n + m + 2);
        for (int i = 0; i < n; ++i) {
            if (x[i] < 0) {
                validate2 = false;
                continue;
            }
            myFlow->AddEdge(0, i + 1, x[i]);
        }
        for (int j = 0; j < m; ++j) {
            if (y[j] < 0) {
                validate2 = false;
                continue;
            }
            myFlow->AddEdge(n + j + 1, n + m + 1, y[j]);
        }
        if (!validate2) {
            assert (0);
            cout << -1 << '\n';
            continue;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                myFlow->AddEdge(i + 1, n + j + 1, b[i][j]);
            }
        }
        myFlow->GetMaxFlow();
        bool validate = true;
        for (int i = 0; i < n; ++i) {
            validate &= (x[i] == myFlow->GetFlow(0, i + 1));
        }
        for (int j = 0; j < m; ++j) {
            validate &= (y[j] == myFlow->GetFlow(n + j + 1, n + m + 1));
        }
        if (!validate) {
            assert (0);
            cout << -1 << '\n';
            continue;
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                answer[i][j] = myFlow->GetFlow(i + 1, n + j + 1) + a[i][j] + minVal;
                x[i] += a[i][j] + minVal;
                y[j] += a[i][j] + minVal;
                b[i][j] += a[i][j] + minVal;
                cout << myFlow->GetFlow(i + 1, n + j + 1) + a[i][j] + minVal << ' ';
            }
            cout << '\n';
        }
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                a[i][j] += minVal;
                assert(a[i][j] <= answer[i][j] and answer[i][j] <= b[i][j]);
                x[i] -= answer[i][j];
                y[j] -= answer[i][j];
            }
        }
        for (int i = 0; i < n; ++i) {
            assert (x[i] == 0);
        }
        for (int j = 0; j < m; ++j) {
            assert (y[j] == 0);
        }
    }
    return 0;
}
