#include <fstream>
#include <iostream>
#include <regex>
#include <map>
using namespace std;

int calculateSteps(string fileName) {
    string line;
    ifstream File(fileName);

    string moves = "";
    do {
        getline(File, line);
        moves += line;
    } while (line != "");

    map<string, pair<string, string>> nodes{};

    while (getline(File, line)) {
        smatch sm;
        
        if (regex_search(line.cbegin(), line.cend(), sm, regex("([A-Z]{3}) = \\(([A-Z]{3}), ([A-Z]{3})\\)"))) {
            pair<string, string> neighbour{sm[2], sm[3]};
            nodes.insert({ sm[1], neighbour });
        }
    }

    File.close();

    string node = "AAA";
    int steps = 0;
    while (node != "ZZZ") {
        auto move = moves.at(steps%moves.size());
        auto n = nodes.at(node);

        if (move == 'R')
            node = n.second;
        else
            node = n.first;

        steps++;
    }

    return steps;
}

int main() {
    cout << "Advent of Code 2023 - Day 8" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateSteps("example.txt") << endl;
    cout << "Result for example 2: " << calculateSteps("example2.txt") << endl;
    cout << "Result for input: " << calculateSteps("input.txt") << endl << endl;
}