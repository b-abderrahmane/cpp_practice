#include <fstream>
#include <iostream>
#include <iterator>
#include <sstream>
#include <string>
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

vector<int> parse_line(istringstream &line_stream) {
    vector<int> vector_line = {};
    string cell;
    while (getline(line_stream, cell, ',')) {
        vector_line.push_back(stoi(cell));
    }
    return vector_line;
}

vector<vector<int>> read_board_file(string filename) {
    vector<vector<int>> grid;
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
    vector<vector<int>> grid;
    grid = read_board_file("1.board");
    display_grid(grid);
}