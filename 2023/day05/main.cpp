#include <iostream>
#include <fstream>
#include <regex>
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

    int l = 0;
    vector<long int> toCheck = {};
    vector<long int> newSeeds(seeds.begin(), seeds.end());
    while (getline(File, line)) {
        smatch sm;
        regex r("([[:digit:]]+) ([[:digit:]]+) ([[:digit:]]+)");

        if (regex_search(line.cbegin(), line.cend(), sm, r)) {
            long int dest = stol(sm[1]);
            long int target = stol(sm[2]);
            long int range = stol(sm[3]);
            vector<long int> s(toCheck.begin(), toCheck.end());
            
            for (auto seed: toCheck) {
                if (seed >= target && seed <= target + range) {
                   s.erase(remove(s.begin(), s.end(), seed));

                   int offset = seed - target;
                   newSeeds.push_back(dest + offset);
                }
            }

            toCheck.swap(s);
        } else if (line != "") {
            seeds.swap(newSeeds);
            newSeeds.clear();

            seeds.insert(seeds.end(), toCheck.begin(), toCheck.end());

            toCheck.clear();
            toCheck.insert(toCheck.end(), seeds.begin(), seeds.end());
        }
    }

    return *min_element(seeds.begin(), seeds.end());
}

int main() {
    cout << "Advent of Code 2023 - Day 5" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateLowestLocation("example.txt") << endl;
    cout << "Result for input: " << calculateLowestLocation("input.txt") << endl << endl;
}