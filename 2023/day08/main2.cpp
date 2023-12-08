#include <fstream>
#include <iostream>
#include <regex>
#include <map>
#include <numeric>
using namespace std;

long int calculateSteps(string fileName) {
    string line;
    ifstream File(fileName);

    string moves = "";
    do {
        getline(File, line);
        moves += line;
    } while (line != "");

    map<string, pair<string, string>> nodes{};
    vector<string> starts{};

    while (getline(File, line)) {
        smatch sm;
        
        if (regex_search(line.cbegin(), line.cend(), sm, regex("([A-Z0-9]{3}) = \\(([A-Z0-9]{3}), ([A-Z0-9]{3})\\)"))) {
            string node = sm[1].str();
            pair<string, string> neighbour{sm[2].str(), sm[3].str()};
            nodes.insert({ node, neighbour });

            if (node.at(2) == 'A') starts.push_back(node);
        }
    }

    File.close(); 

    vector<int> lengths{};

    for (auto start: starts) {
        string node = start;
        int steps = 0;

        while (node.at(2) != 'Z') {
            auto move = moves.at(steps%moves.size());
            auto n = nodes.at(node);

            if (move == 'R')
                node = n.second;
            else
                node = n.first;

            steps++;
        }

        lengths.push_back(steps);
    }

    long int ans = lengths[0];
    for (int i = 1; i < lengths.size(); i++) {
        ans = lcm(lengths[i], ans);
    }

    return ans;
}

int main() {
    cout << "Advent of Code 2023 - Day 8" << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calculateSteps("example3.txt") << endl;
    cout << "Result for example: " << calculateSteps("input.txt") << endl;
}