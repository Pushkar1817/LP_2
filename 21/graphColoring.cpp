#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int n;
    vector<vector<int>> adjList;

    Graph(int n) {
        this->n = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v) {
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    bool isSafe(int node, vector<int>& color, int c) {
        for (int i = 0; i < adjList[node].size(); i++) {
            int neighbor = adjList[node][i];
            if (color[neighbor] == c)
                return false;
        }
        return true;
    }

    bool solve(int node, int m, vector<int>& color) {
        if (node == n)
            return true;
        for (int c = 1; c <= m; c++) {
            if (isSafe(node, color, c)) {
                color[node] = c;
                if (solve(node + 1, m, color))
                    return true;
                color[node] = 0;
            }
        }
        return false;
    }

    void graphColoring(int m) {
        vector<int> color(n, 0);
        if (!solve(0, m, color)) {
            cout << "Solution does not exist\n";
            return;
        }

        for (int i = 0; i < n; i++)
            cout << "Vertex " << i << " --->  Color " << color[i] << "\n";
    }
};

int main() {
    Graph g(6);

    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 2);
    g.addEdge(1, 4);
    g.addEdge(1, 5);
    g.addEdge(1, 3);
    g.addEdge(2, 3);

    int m = 3;

    g.graphColoring(m);

    return 0;
}
