#include <cstdlib>
#include <fstream>
#include <iostream>
#include <math.h>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

vector<tuple<char, int>> readFile(string fileName) {
    string line;
    ifstream File(fileName);
    vector<tuple<char, int>> moves;

    while (getline(File, line)) {
        auto dir = line[0];
        auto nbClick = stoi(line.substr(1, line.length()));

        moves.push_back({dir, nbClick});
    }

    return moves;
}

tuple<int, int> calculateClickOnZero(vector<tuple<char, int>> moves) {
    int pos = 50;
    int p1 = 0;
    int p2 = 0;

    for (auto m : moves) {
        auto [dir, nbClick] = m;
        int oldPos = pos;

        if (dir == 'L') {
            pos -= nbClick;

            p2 += (100 - pos) / 100;
            p2 -= oldPos == 0 ? 1 : 0;
        } else if (dir == 'R') {
            pos += nbClick;
            p2 += pos / 100;
        }

        pos = (pos % 100 + 100) % 100;

        if (pos == 0)
            p1++;
    }

    return {p1, p2};
}

int main() {
    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    auto [e1, e2] = calculateClickOnZero(example);
    auto [i1, i2] = calculateClickOnZero(input);

    cout << "Part 1" << endl;
    cout << "Result for example: " << e1 << endl;
    cout << "Result for input: " << i1 << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << e2 << endl;
    cout << "Result for example: " << i2 << endl;
}
