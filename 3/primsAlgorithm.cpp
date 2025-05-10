#include <bits/stdc++.h>
using namespace std;

class Graph {
    int nv;                          
    vector<pair<int, int>> *adjList;  

   public:
    Graph(int nv) {
        this->nv = nv;
        adjList = new vector<pair<int, int>>[nv];
    }

    void addEdge(int src, int des, int weight) {
        adjList[src].push_back({des, weight});
        adjList[des].push_back({src, weight});  
    }

    void primsMST(int start) {
        vector<int> parent(nv, -1);      
        vector<int> key(nv, INT_MAX);    
        vector<bool> mstSet(nv, false);  

        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq; 

        key[start] = 0;       
        pq.push({0, start});  

        while (!pq.empty()) {
            int u = pq.top().second;
            pq.pop();

            mstSet[u] = true;

            for (auto i : adjList[u]) {
                int v = i.first;
                int weight = i.second;

                if (mstSet[v] == false && weight < key[v]) {
                    parent[v] = u;
                    key[v] = weight;
                    pq.push({key[v], v});
                }
            }
        }

        for (int i = 1; i < nv; i++) {
            cout << parent[i] << " - " << i << " : " << key[i] << endl;
        }

        int totalWeight = 0;
        for (int i = 1; i < nv; i++) {
            totalWeight += key[i];
        }
        cout << "Total weight of MST: " << totalWeight << endl;
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


    g.primsMST(0);

    return 0;
}