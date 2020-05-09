#include <algorithm>
#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class State { kClear, kObstacle, kClosed, kPath };

string cell_string(State cell) {
    switch (cell) {
    case State::kObstacle:
        return "⛰️ ";
    default:
        return "0  ";
    }
}

State stostate(string value) {
    if (value == "0") {
        return State::kClear;
    } else {
        return State::kObstacle;
    }
}

void display_grid(vector<vector<State>> grid) {
    for (vector<State> row : grid) {
        for (State cell : row) {
            cout << cell_string(cell);
        }
        cout << "\n";
    }
}

vector<State> parse_line(istringstream &line_stream) {
    vector<State> vector_line = {};
    string cell;
    while (getline(line_stream, cell, ',')) {
        vector_line.push_back(stostate(cell));
    }
    return vector_line;
}

vector<vector<State>> read_board_file(string filename) {
    vector<vector<State>> grid;
    ifstream infile(filename);
    if (!infile) {
        cout << "Cannot open input file.\n";
        exit(1);
    }

    string line;
    while (getline(infile, line)) {
        istringstream iss(line);
        grid.push_back(parse_line(iss));
    }
    return grid;
}

int manhattan_heuristic(int start[2], int destination[2]) {
    return abs(start[0] - destination[0]) + abs(start[1] - destination[1]);
}

void add_to_open(vector<vector<State>> &grid, vector<vector<int>> &open_nodes,
                 int x, int y, int g, int h) {
    vector<int> node = {x, y, g, h};
    open_nodes.push_back(node);
    grid[x][y] = State::kClosed;
}

bool compare_nodes(vector<int> a, vector<int> b) {
    if (a[2] + a[3] > b[2] + b[3]) {
        return true;
    }
    return false;
}

void cell_sort(vector<vector<int>> *v) {
    sort(v->begin(), v->end(), compare_nodes);
}

bool CheckValidCell(int x, int y, vector<vector<State>> &grid) {
    if (x >= 0 && y >= 0) {
        if (x < grid.size() && y < grid[0].size()) {
            if (grid[x][y] == State::kClear) {
                return true;
            }
        }
    }
    return false;
}

vector<vector<State>> search(vector<vector<State>> grid, int indices[2][2]) {
    vector<vector<State>> results;
    vector<vector<int>> open_nodes;
    add_to_open(grid, open_nodes, indices[0][0], indices[0][1], 0,
                manhattan_heuristic(indices[0], indices[1]));

    int i = 0;
    while (!open_nodes.empty()) {
        cell_sort(&open_nodes);

        int x = open_nodes[i][2];
        int y = open_nodes[i][3];
        grid[x][y] = State::kPath;
        if (x == indices[1][0] && y == indices[1][1]) {
            return grid;
        }
        return grid;
    }

    cout << "No path found!" << endl;
    return results;
}

int main() {
    vector<vector<State>> grid;

    grid = read_board_file("1.board");
    int indices[2][2] = {{0, 0}, {4, 5}};
    cout << manhattan_heuristic(indices[0], indices[1]) << endl;
    grid = search(grid, indices);
    display_grid(grid);
}