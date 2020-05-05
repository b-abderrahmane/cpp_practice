#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
#include <vector>

using namespace std;

enum class State { kClear, kObstacle };

string cell_string(State cell) {
    switch (cell) {
    case State::kObstacle:
        return "⛰️ ";
    default:
        return "0 ";
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

int main() {
    vector<vector<State>> grid;
    grid = read_board_file("1.board");
    display_grid(grid);
}