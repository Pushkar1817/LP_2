#include <bits/stdc++.h>
using namespace std;

class Graph {
public:
    int n;
    vector<vector<int>> adj;

    Graph(int nodes) {
        n = nodes;
        adj.resize(n);
    }

    void addEdge(int u, int v) {
        adj[u].push_back(v);
        adj[v].push_back(u);
    }

    void dfsRecursiveUtil(int node, vector<bool>& visited, int level) {
        visited[node] = true;
        cout << "Node: " << node << ", Level: " << level << "\n";
        for (int i = 0; i < adj[node].size(); ++i) {
            int nei = adj[node][i];
            if (!visited[nei])
                dfsRecursiveUtil(nei, visited, level + 1);
        }
    }

    void dfsRecursive(int start) {
        vector<bool> visited(n, false);
        dfsRecursiveUtil(start, visited, 0);
    }

    void bfsRecursiveUtil(queue<int>& q, vector<bool>& visited, vector<int>& level) {
        if (q.empty()) return;
        int node = q.front();
        q.pop();
        cout << "Node: " << node << ", Level: " << level[node] << "\n";
        for (int i = 0; i < adj[node].size(); ++i) {
            int nei = adj[node][i];
            if (!visited[nei]) {
                visited[nei] = true;
                level[nei] = level[node] + 1;
                q.push(nei);
            }
        }
        bfsRecursiveUtil(q, visited, level);
    }

    void bfsRecursive(int start) {
        vector<bool> visited(n, false);
        vector<int> level(n, 0);
        queue<int> q;
        q.push(start);
        visited[start] = true;
        bfsRecursiveUtil(q, visited, level);
    }

    void dfsIterative(int start) {
        vector<bool> visited(n, false);
        stack<pair<int, int> > stk;
        stk.push(make_pair(start, 0));
        while (!stk.empty()) {
            pair<int, int> p = stk.top();
            stk.pop();
            int node = p.first;
            int level = p.second;
            if (visited[node]) continue;
            visited[node] = true;
            cout << "Node: " << node << ", Level: " << level << "\n";
            for (int i = adj[node].size() - 1; i >= 0; --i) {
                int nei = adj[node][i];
                if (!visited[nei]) {
                    stk.push(make_pair(nei, level + 1));
                }
            }
        }
    }

    void bfsIterative(int start) {
        vector<bool> visited(n, false);
        queue<pair<int, int> > q;
        q.push(make_pair(start, 0));
        visited[start] = true;
        while (!q.empty()) {
            pair<int, int> p = q.front();
            q.pop();
            int node = p.first;
            int level = p.second;
            cout << "Node: " << node << ", Level: " << level << "\n";
            for (int i = 0; i < adj[node].size(); ++i) {
                int nei = adj[node][i];
                if (!visited[nei]) {
                    visited[nei] = true;
                    q.push(make_pair(nei, level + 1));
                }
            }
        }
    }
};

int main() {
    Graph g(7);
    g.addEdge(0, 1);
    g.addEdge(0, 2);
    g.addEdge(1, 3);
    g.addEdge(1, 4);
    g.addEdge(2, 5);
    g.addEdge(2, 6);

    cout << "DFS Recursive:\n";
    g.dfsRecursive(0);

    cout << "\nBFS Recursive:\n";
    g.bfsRecursive(0);

    cout << "\nDFS Iterative:\n";
    g.dfsIterative(0);

    cout << "\nBFS Iterative:\n";
    g.bfsIterative(0);

    return 0;
}
