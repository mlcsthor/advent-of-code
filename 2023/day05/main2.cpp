#include <iostream>
#include <fstream>
#include <regex>
#include <thread>
using namespace std;

long int calculateLowestLocation(string fileName) {
    string line;
    ifstream File(fileName);

    getline(File, line);

    regex rd("([[:digit:]]+)");
    auto it = sregex_iterator(line.begin(), line.end(), rd);
    auto end = sregex_iterator();

    vector<long int> seeds = {};

    for (auto k = it; k != end; ++k) {
        seeds.push_back(stol((*k).str()));
    }

    vector<vector<tuple<long int, long int, long int>>> mappings{};
    int i = -1;
    while (getline(File, line)) {
        smatch sm;
        if (regex_search(line.cbegin(), line.cend(), sm, regex("([0-9]+) ([0-9]+) ([0-9]+)"))) {
            mappings.at(i).push_back(tuple(stol(sm[1].str()), stol(sm[2].str()), stol(sm[3].str())));
        } else if (line != "") {
            i++;
            mappings.push_back({});
        }
    }

    File.close();

    auto minLocation = numeric_limits<long int>::max();
    for (int i = 0; i < seeds.size() - 1; i += 2) {
        for (int j = 0; j < seeds[i + 1]; j++) {
            cout << "i: " << i << " / j: " << j << endl;
            long int seed = seeds[i] + j;

            for (auto mapping: mappings) {
                for (auto m: mapping) {
                    long int d = get<0>(m);
                    long int t = get<1>(m);
                    long int r = get<2>(m);

                    if (seed < t || seed > t + r) continue;

                    long int offset = seed - t;
                    seed = d + offset;
                    break;
                }
            }

            minLocation = min(minLocation, seed);
        }

        cout << "Minimum: " << minLocation << endl;
    };

    return 0;
}

int main() {
    cout << "Advent of Code 2023 - Day 5" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateLowestLocation("example.txt") << endl;
    cout << "Result for input: " << calculateLowestLocation("input.txt") << endl << endl;
}