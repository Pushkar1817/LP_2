#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Object {
    int width, height, id;
    bool placed;
    string symbol; 
};

struct State {
    vector<vector<string>> room;
    vector<Object> objects;
    int usedArea;

    int heuristic() const {
        return  - usedArea;
    }

    bool operator>(const State& other) const {
        return heuristic() > other.heuristic();
    }
};

bool canPlace(const vector<vector<string>>& room, const Object& obj, int x, int y) {
    int h = room.size(), w = room[0].size();
    if (x + obj.height > h || y + obj.width > w) return false;

    for (int i = x; i < x + obj.height; ++i)
        for (int j = y; j < y + obj.width; ++j)
            if (room[i][j] != ".") return false;

    return true;
}

void placeObject(vector<vector<string>>& room, const Object& obj, int x, int y) {
    for (int i = x; i < x + obj.height; ++i)
        for (int j = y; j < y + obj.width; ++j)
            room[i][j] = obj.symbol;
}

void arrangeObjects(int rows, int cols, vector<Object> objects) {
    priority_queue<State, vector<State>, greater<State>> pq;

    vector<vector<string>> emptyRoom(rows, vector<string>(cols, "."));
    State start = {emptyRoom, objects, 0};
    pq.push(start);

    while (!pq.empty()) {
        State current = pq.top(); pq.pop();

        bool allPlaced = true;
        for (const auto& obj : current.objects) {
            if (!obj.placed) {
                allPlaced = false;
                break;
            }
        }

        if (allPlaced) {
            cout << "\nFinal Room Arrangement:\n";
            for (const auto& row : current.room) {
                for (const string& c : row)
                    cout << c << '\t';
                cout << '\n';
            }
            return;
        }

        for (int idx = 0; idx < current.objects.size(); ++idx) {
            if (current.objects[idx].placed) continue;
            Object obj = current.objects[idx];

            for (int i = 0; i < rows; ++i) {
                for (int j = 0; j < cols; ++j) {
                    if (canPlace(current.room, obj, i, j)) {
                        State next = current;
                        placeObject(next.room, obj, i, j);
                        next.objects[idx].placed = true;
                        next.usedArea += obj.width * obj.height;
                        pq.push(next);
                        goto next_object;
                    }
                }
            }
        next_object:;
        }
    }

    cout << "Could not place all objects.\n";
}

int main() {
    int roomRows = 0, roomCols = 0;
    vector<Object> objects;
    int choice;
    int rectCount = 1, squareCount = 1;

    do {
        cout << "\n--- Object Arrangement Menu ---\n";
        cout << "1. Enter room dimensions\n";
        cout << "2. Enter rectangular objects\n";
        cout << "3. Enter square objects\n";
        cout << "4. Arrange objects using A*\n";
        cout << "5. Exit\n";
        cout << "Choice: ";
        cin >> choice;

        switch (choice) {
        case 1:
            cout << "Enter room rows and columns: ";
            cin >> roomRows >> roomCols;
            break;

        case 2: {
            int n;
            cout << "Enter number of rectangular objects (max 5): ";
            cin >> n;
            n = min(n, 5);
            for (int i = 0; i < n; ++i) {
                Object obj;
                obj.id = rectCount;
                obj.placed = false;
                cout << "Enter width and height for rectangle " << rectCount << ": ";
                cin >> obj.width >> obj.height;
                obj.symbol = "r" + to_string(rectCount++);
                objects.push_back(obj);
            }
            break;
        }

        case 3: {
            int n;
            cout << "Enter number of square objects (max 4): ";
            cin >> n;
            n = min(n, 4);
            for (int i = 0; i < n; ++i) {
                Object obj;
                obj.id = squareCount;
                obj.placed = false;
                cout << "Enter side length for square " << squareCount << ": ";
                cin >> obj.width;
                obj.height = obj.width;
                obj.symbol = "s" + to_string(squareCount++);
                objects.push_back(obj);
            }
            break;
        }

        case 4:
            if (roomRows > 0 && roomCols > 0 && !objects.empty()) {
                arrangeObjects(roomRows, roomCols, objects);
            } else {
                cout << "Room dimensions and objects must be entered first.\n";
            }
            break;

        case 5:
            cout << "Exiting...\n";
            break;

        default:
            cout << "Invalid choice.\n";
        }

    } while (choice != 5);

    return 0;
}
