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
    case State::kPath:
        return "🚗 ";
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

void add_to_open(vector<vector<State>> &grid, vector<vector<int>> &open_nodes, int x, int y, int g, int h) {
    open_nodes.push_back(vector<int>{x, y, g, h});
    grid[x][y] = State::kClosed;
}

bool compare_nodes(vector<int> a, vector<int> b) { return a[2] + a[3] > b[2] + b[3]; }

void cell_sort(vector<vector<int>> *v) { sort(v->begin(), v->end(), compare_nodes); }

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

void expand_neighbors(vector<int> current_node, vector<vector<State>> &grid, vector<vector<int>> &open_nodes,
                      int goal[2]) {
    int node_coor[2] = {current_node[0], current_node[1]};
    int g = current_node[2];
    int h = current_node[3];

    const int delta[4][2]{{-1, 0}, {0, -1}, {1, 0}, {0, 1}};
    vector<int> neighbor = {};
    int next_y, next_x;
    for (int i = 0; i < 4; i++) {
        int next_x = node_coor[0] + delta[i][0];
        int next_y = node_coor[1] + delta[i][1];
        int new_coor[2] = {next_x, next_y};
        if (CheckValidCell(next_x, next_y, grid)) {
            int heur = manhattan_heuristic(new_coor, goal);
            add_to_open(grid, open_nodes, next_x, next_y, g + 1, heur);
        }
    }
}

vector<vector<State>> search(vector<vector<State>> grid, int start[2], int goal[2]) {

    vector<vector<int>> open_nodes{};
    add_to_open(grid, open_nodes, start[0], start[1], 0, manhattan_heuristic(start, goal));

    while (open_nodes.size() > 0) {
        cell_sort(&open_nodes);
        auto current = open_nodes.back();
        open_nodes.pop_back();
        int x = current[0];
        int y = current[1];
        grid[x][y] = State::kPath;
        if (x == goal[0] && y == goal[1]) {
            return grid;
        }
        expand_neighbors(current, grid, open_nodes, goal);
    }

    cout << "No path found!"
         << "\n";
    return std::vector<vector<State>>{};
}

int main() {
    vector<vector<State>> grid;

    grid = read_board_file("1.board");
    int start[2] = {0, 0};
    int goal[2] = {0, 5};
    grid = search(grid, start, goal);
    display_grid(grid);
}