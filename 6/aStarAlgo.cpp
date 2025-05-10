#include <bits/stdc++.h>
using namespace std;

struct Node {
    vector<vector<int>> mat;
    int x, y, cost, level;
    string path;

    bool operator>(const Node& other) const {
        return (cost + level) > (other.cost + other.level);
    }
};

int row[] = {1, 0, -1, 0};
int col[] = {0, -1, 0, 1};
string dir[] = {"Down", "Left", "Up", "Right"};

int manhattan(const vector<vector<int>> &curr, const vector<vector<int>> &goal) {
    int dist = 0;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++) {
            // if (curr[i][j] == 0) continue;
            // for(int x = 0; x < 3; x++)
            //     for(int y = 0; y < 3; y++)
            //         if (goal[x][y] == curr[i][j])
            //             dist += abs(i - x) + abs(j - y);
            if(curr[i][j]!=goal[i][j])
                dist++;
        }
    return dist;
}

bool isSafe(int x, int y) {
    return x >= 0 && x < 3 && y >= 0 && y < 3;
}

void printMatrix(const vector<vector<int>>& mat) {
    for(auto& row : mat) {
        for(auto& val : row)
            cout << val << " ";
        cout << "\n";
    }
}

void aStar(vector<vector<int>>& ini, const vector<vector<int>> & fin) {
    int sx, sy;
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if (ini[i][j] == 0) {
                sx = i;
                sy = j;
            }

    priority_queue<Node, vector<Node>, greater<Node>> pq;
    set<vector<vector<int>>> visited;

    Node start = {ini, sx, sy, manhattan(ini, fin), 0, ""};
    pq.push(start);

    while(!pq.empty()) {
        Node current = pq.top(); 
        pq.pop();

        cout << "Level: " << current.level << ", Heuristic (h): " << current.cost << ", f(n) = g + h = " << current.level + current.cost << "\n";
        printMatrix(current.mat);
        cout << "-------------------\n";

        if (current.mat == fin) {
            cout << " --- Solution found at level " << current.level << "\n";
            cout << " --- Path: " << current.path << "\n";
            return;
        }

        visited.insert(current.mat);

        for(int k = 0; k < 4; k++) {
            int nx = current.x + row[k];
            int ny = current.y + col[k];

            if (isSafe(nx, ny)) {
                vector<vector<int>> newMat = current.mat;
                swap(newMat[nx][ny], newMat[current.x][current.y]);

                if (visited.find(newMat) == visited.end()) {
                    Node neighbor = {
                        newMat,
                        nx,
                        ny,
                        manhattan(newMat, fin),
                        current.level + 1,
                        current.path + dir[k] + " "
                    };
                    pq.push(neighbor);
                }
            }
        }
    }

    cout << " ----- No solution found ------\n";
}

int main() {
    vector<vector<int>> ini(3, vector<int>(3));
    cout << "Please Enter the Initial matrix (row-wise, use 0 for blank): ";
    for(int i = 0; i < 9; i++)
        cin >> ini[i/3][i%3];

    vector<vector<int>> fin(3, vector<int>(3));
    cout << "Please Enter the Final(Goal) matrix (row-wise, use 0 for blank): ";
    for(int i = 0; i < 9; i++)
        cin >> fin[i/3][i%3];

    aStar(ini, fin);

    return 0;
}
// 1 2 3 4 0 6 7 5 8  
// 1 2 3 4 5 6 7 8 0 

//8 6 7 2 5 4 3 0 1
//1 2 3 4 5 6 7 8 0
