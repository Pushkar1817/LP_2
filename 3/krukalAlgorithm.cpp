#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    vector<vector<pair<int, int>>> adjList;
    vector<vector<int>> edges;
    int n = 0;

    Graph(int n) {
        this->n = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
        edges.push_back({w, u, v}); // Store weight first for sorting
    }

    bool dfs(int node, int parent, vector<bool>& visited, const vector<vector<pair<int, int>>>& tree) {
        visited[node] = true;
        for (const auto& neighbor : tree[node]) {
            int nei = neighbor.first;
            if (!visited[nei]) {
                if (dfs(nei, node, visited, tree))
                    return true;
            } else if (nei != parent) {
                return true; // Cycle detected
            }
        }
        return false;
    }

    bool isCycle(const vector<vector<pair<int, int>>>& tree) {
        vector<bool> visited(n, false);
        for (int i = 0; i < n; ++i) {
            if (!visited[i]) {
                if (dfs(i, -1, visited, tree))
                    return true;
            }
        }
        return false;
    }

    void kruskalAlgo() {
        sort(edges.begin(), edges.end()); // Sort edges by weight
        vector<vector<pair<int, int>>> tree(n); // MST graph structure

        int mst_weight = 0;
        int edge_count = 0;

        for (auto edge : edges) {
            int w = edge[0];
            int u = edge[1];
            int v = edge[2];

            // Temporarily add edge
            tree[u].push_back({v, w});
            tree[v].push_back({u, w});

            if (isCycle(tree)) {
                // Undo the addition if it forms a cycle
                tree[u].pop_back();
                tree[v].pop_back();
            } else {
                mst_weight += w;
                edge_count++;
                cout << u << " - " << v << " : " << w << "\n";

                if (edge_count == n - 1) break; // Stop early when MST is complete
            }
        }

        cout << "Total weight of MST: " << mst_weight << "\n";
    }
};

int main() {
    Graph g(7); // Nodes: 0 to 6

    g.addEdge(0, 1, 7);
    g.addEdge(0, 3, 5);
    g.addEdge(1, 2, 8);
    g.addEdge(1, 3, 9);
    g.addEdge(1, 4, 7);
    g.addEdge(2, 4, 5);
    g.addEdge(3, 4, 15);
    g.addEdge(3, 5, 6);
    g.addEdge(4, 5, 8);
    g.addEdge(4, 6, 9);
    g.addEdge(5, 6, 11);

    g.kruskalAlgo();
    return 0;
}
