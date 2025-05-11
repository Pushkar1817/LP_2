#include<bits/stdc++.h>
using namespace std;

class SudokuSolver {
private:
    vector<vector<int>> puzzle;
    bool fixedCell[9][9];
    vector<vector<int>> nonFixedCols;

    void initializeFixedCells() {
        for (int i = 0; i < 9; ++i)
            for (int j = 0; j < 9; ++j)
                fixedCell[i][j] = (puzzle[i][j] != 0);
    }

    void collectNonFixedColumns() {
        nonFixedCols.resize(9);
        for (int i = 0; i < 9; ++i) {
            nonFixedCols[i].clear();
            for (int j = 0; j < 9; ++j) {
                if (!fixedCell[i][j])
                    nonFixedCols[i].push_back(j);
            }
        }
    }

    void randomInitialize() {
        for (int i = 0; i < 9; ++i) {
            vector<bool> present(10, false);
            for (int j = 0; j < 9; ++j)
                if (fixedCell[i][j]) present[puzzle[i][j]] = true;

            vector<int> avail;
            for (int num = 1; num <= 9; ++num)
                if (!present[num]) avail.push_back(num);

            random_shuffle(avail.begin(), avail.end());

            for (int k = 0; k < (int)nonFixedCols[i].size(); ++k)
                puzzle[i][nonFixedCols[i][k]] = avail[k];
        }
    }

    int computeConflicts() const {
        int conflicts = 0;

        // Column conflicts
        for (int col = 0; col < 9; ++col) {
            int count[10] = {0};
            for (int row = 0; row < 9; ++row) {
                int val = puzzle[row][col];
                if (val != 0) {
                    count[val]++;
                    if (count[val] > 1) conflicts++;
                }
            }
        }

        // Block conflicts
        for (int brow = 0; brow < 3; ++brow) {
            for (int bcol = 0; bcol < 3; ++bcol) {
                int count[10] = {0};
                for (int i = 0; i < 3; ++i) {
                    for (int j = 0; j < 3; ++j) {
                        int row = brow * 3 + i;
                        int col = bcol * 3 + j;
                        int val = puzzle[row][col];
                        if (val != 0) {
                            count[val]++;
                            if (count[val] > 1) conflicts++;
                        }
                    }
                }
            }
        }

        return conflicts;
    }

    bool hillClimb() {
        int currentConflicts = computeConflicts();
        while (true) {
            if (currentConflicts == 0) return true;

            int bestConflicts = currentConflicts;
            int bestRow = -1, bestCol1 = -1, bestCol2 = -1;

            for (int i = 0; i < 9; ++i) {
                int sz = nonFixedCols[i].size();
                for (int a = 0; a < sz; ++a) {
                    for (int b = a + 1; b < sz; ++b) {
                        int col1 = nonFixedCols[i][a];
                        int col2 = nonFixedCols[i][b];

                        swap(puzzle[i][col1], puzzle[i][col2]);
                        int newConflicts = computeConflicts();
                        if (newConflicts < bestConflicts) {
                            bestConflicts = newConflicts;
                            bestRow = i;
                            bestCol1 = col1;
                            bestCol2 = col2;
                        }
                        swap(puzzle[i][col1], puzzle[i][col2]); // revert
                    }
                }
            }

            if (bestConflicts < currentConflicts) {
                swap(puzzle[bestRow][bestCol1], puzzle[bestRow][bestCol2]);
                currentConflicts = bestConflicts;
            } else {
                return false; // local minimum
            }
        }
    }

public:
    SudokuSolver(const vector<vector<int>>& initial) : puzzle(initial) {
        srand(time(NULL));
        initializeFixedCells();
        collectNonFixedColumns();
    }

    void solve(int maxRestarts = 10000) {
        for (int attempt = 1; attempt <= maxRestarts; ++attempt) {
            randomInitialize();
            if (hillClimb()) {
                cout << "Solved in " << attempt << " attempts.\n";
                return;
            }
        }
        cout << "No solution found after " << maxRestarts << " random restarts. Puzzle might be unsolvable.\n";
    }

    void printSolution() const {
        for (const auto& row : puzzle) {
            for (int val : row) {
                cout << val << " ";
            }
            cout << endl;
        }
    }
};

int main() {
    vector<vector<int>> puzzle = {
        {5,3,0,0,7,0,0,0,0},
        {6,0,0,1,9,5,0,0,0},
        {0,9,8,0,0,0,0,6,0},
        {8,0,0,0,6,0,0,0,3},
        {4,0,0,8,0,3,0,0,1},
        {7,0,0,0,2,0,0,0,6},
        {0,6,0,0,0,0,2,8,0},
        {0,0,0,4,1,9,0,0,5},
        {0,0,0,0,8,0,0,7,9}
    };

    SudokuSolver solver(puzzle);
    solver.solve(5000);
    
    cout << "Solved Sudoku:\n";
    solver.printSolution();

    return 0;
}
