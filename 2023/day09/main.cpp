#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

const regex R("(-?[[:digit:]]+)");

pair<int, int> extrapolateLine(string line) {
    auto begin = sregex_iterator(line.begin(), line.end(), R);
    auto end = sregex_iterator();

    vector<int> reports{};
    for (auto k = begin; k != end; ++k) {
        reports.push_back(stoi((*k).str()));
    }

    pair<int, int>extrapolate{reports.back(), reports.at(0)};
    int l = 0;

    while (!all_of(reports.begin(), reports.end(), [](int i) { return i == 0; })) {
        vector<int> diff{};

        for (int i = 0; i < reports.size() - 1; i++) {
            diff.push_back(reports[i + 1] - reports[i]);
        }

        extrapolate.first += diff.back();
        if (l%2 == 0) extrapolate.second -= diff.at(0);
        else extrapolate.second += diff.at(0);

        reports.swap(diff);
        l++;
    }

    return extrapolate;
}

pair<int, int> extrapolate(string fileName) {
    pair<int, int> results{0, 0};

    string line;
    ifstream File(fileName);

    while (getline(File, line)) {
        auto r = extrapolateLine(line);
        results.first += r.first;
        results.second += r.second;
    }

    File.close();

    return results;
}

int main() {
    cout << "Advent of Code 2023 - Day 9" << endl << endl;

    auto example = extrapolate("example.txt");
    auto input = extrapolate("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << example.first << endl;
    cout << "Result for input: " << input.first << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << example.second << endl;
    cout << "Result for input: " << input.second << endl;
}