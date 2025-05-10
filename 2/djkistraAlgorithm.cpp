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

    int Djkistra(int st,int dest){
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

        return dist[dest];
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

    int start = 0;
    int dest = 5;
    cout<<"\nUsing Djkistra's Algorithm:\n";
    int dist = g.Djkistra(start,dest);
    cout<<"Shortest Path from "<<start<<" to "<<dest<<" is : "<<dist;
    return 0;
}
