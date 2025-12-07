#include <algorithm>
#include <fstream>
#include <iostream>
#include <set>
#include <string>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

using Coords = pair<int, int>;

tuple<Coords, vector<Coords>, Coords> readFile(string fileName) {
    string line;
    ifstream File(fileName);

    Coords start;
    vector<Coords> tachyons;
    Coords limits = {0, 0};

    int i = 0;
    while (getline(File, line)) {
        if (limits.second == 0)
            limits.second = line.length();

        for (int j = 0; j < line.length(); j++) {
            switch (line[j]) {
            case 'S':
                start = {i, j};
                break;

            case '^':
                tachyons.push_back({i, j});
                break;

            default:
                continue;
            }
        }

        i++;
    }

    limits.first = i;

    return {start, tachyons, limits};
}

void moveDownward(tuple<Coords, vector<Coords>, Coords> data,
                  set<Coords>* visited, set<Coords>* splits) {
    auto [start, tachyons, limits] = data;

    if (start.second < 0 || start.second > limits.second ||
        visited->contains(start))
        return;

    Coords c = {start.first, start.second};
    visited->insert(c);

    while (find(tachyons.begin(), tachyons.end(), c) == tachyons.end() &&
           c.first < limits.first) {
        c.first++;
    }

    if (c.first == limits.first) {
        return;
    } else {
        splits->insert(c);

        Coords left = {c.first, c.second - 1};
        Coords right = {c.first, c.second + 1};

        moveDownward({left, tachyons, limits}, visited, splits);
        moveDownward({right, tachyons, limits}, visited, splits);
        return;
    }
}

int countSplit(tuple<Coords, vector<Coords>, Coords> data) {
    set<Coords> visited, splits;
    moveDownward(data, &visited, &splits);

    return splits.size();
}

long countTimeline(tuple<Coords, vector<Coords>, Coords> data) {
    auto [start, tachyons, limits] = data;

    vector<long> beams;
    for (int i = 0; i <= limits.second; i++) {
        beams.push_back(i == start.second ? 1 : 0);
    }

    for (auto tachyon : tachyons) {
        if (beams[tachyon.second] != 0) {
            beams[tachyon.second - 1] += beams[tachyon.second];
            beams[tachyon.second + 1] += beams[tachyon.second];
            beams[tachyon.second] = 0;
        }
    }

    long count = 0;
    for (auto n : beams) {
        count += n;
    }

    return count;
}

int main() {
    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << countSplit(example) << endl;
    cout << "Result for input: " << countSplit(input) << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << countTimeline(example) << endl;
    cout << "Result for input: " << countTimeline(input) << endl;
}
