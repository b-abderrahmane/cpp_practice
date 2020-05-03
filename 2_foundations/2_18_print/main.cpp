#include <iostream>
#include <vector>

using namespace std;

void display_grid(vector<vector<int>> grid) {

    for (vector<int> row : grid) {
        for (int cell : row) {
            cout << cell;
        }
        cout << "\n";
    }
}

int main() {
    vector<vector<int>> grid = {{0, 1, 0, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {0, 1, 0, 0, 0, 0},
                                {0, 0, 0, 0, 1, 0}};

    display_grid(grid);
}