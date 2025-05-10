#include <bits/stdc++.h>
using namespace std;

class graph {
public:
    int ver = 0;
    vector<vector<pair<int, int>>> adjList;
    vector<vector<int>> edges;

    graph(int n) {
        this->ver = n;
        adjList.resize(n);
    }

    void addEdge(int u, int v, int w) {
        adjList[u].push_back({v, w});
        adjList[v].push_back({u, w});
        edges.push_back({u, v, w});
    }

    vector<int> bellmonFord(int st) {
        vector<int> dist(ver, INT_MAX);
        dist[st] = 0;

        for (int i = 0; i < ver - 1; i++) {
            for (auto& edge : edges) {
                int u = edge[0];
                int v = edge[1];
                int w = edge[2];

                if (dist[u] != INT_MAX && dist[u] + w < dist[v])
                    dist[v] = dist[u] + w;
                if (dist[v] != INT_MAX && dist[v] + w < dist[u])
                    dist[u] = dist[v] + w;
            }
        }

        return dist;
    }

    vector<int> Djkistra(int st){
        vector<int>dist(ver,INT_MAX);

        priority_queue<pair<int,int>,vector<pair<int,int>>,greater<>>pq;
        pq.push({0,st});

        while(!pq.empty()){
            int currDist = pq.top().first;
            int node = pq.top().second;
            pq.pop();

            if(dist[node] > currDist)
                dist[node] = currDist;
            else
                continue;

            for(int i = 0 ;i< adjList[node].size() ;i++){
                int neigh = adjList[node][i].first;
                int weight = adjList[node][i].second;

                pq.push({currDist+weight,neigh});
            }
        }

        return dist;
    }

    void printVec(int st, const vector<int>& dist) {
        cout << "Distance from " << st << " to all the nodes:\n";
        for (int i = 0; i < dist.size(); i++) {
            cout << st << " - " << i << " = ";
            if (dist[i] == INT_MAX)
                cout << "INF";
            else
                cout << dist[i];
            cout << endl;
        }
    }
};

int main() {
    graph g(6);
    
    g.addEdge(0, 1, 4);
    g.addEdge(0, 2, 2);
    g.addEdge(1, 2, 5);
    g.addEdge(1, 3, 10);
    g.addEdge(2, 4, 3);
    g.addEdge(4, 3, 4);
    g.addEdge(3, 5, 11);
    g.addEdge(4, 5, 2);
    g.addEdge(0, 4, 7);
    g.addEdge(2, 5, 9);

    cout<<"\nUsing Bellmon Ford's Algorithm:\n";
    int start = 0;
    vector<int> dist1 = g.bellmonFord(start);
    g.printVec(start, dist1);

    cout<<"\nUsing Djkistra's Algorithm:\n";
    vector<int> dist2 = g.Djkistra(start);
    g.printVec(start, dist2);

    return 0;
}
