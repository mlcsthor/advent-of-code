#include <fstream>
#include <iostream>
using namespace std;

long int findShortestPaths(string fileName, int size) {
    string line;
    fstream File(fileName);

    vector<string> universe{};
    vector<pair<int, int>> galaxies{};

    vector<int> emptyLines;
    vector<int> emptyColumns;

    int l = 0;
    while (getline(File, line)) {
        universe.push_back(line);

        for (int c = 0; c < line.size(); c++) {
            if (line.at(c) != '#') continue;

            galaxies.push_back(pair(l, c));
        }

        // Find empty lines
        if (line.find("#") == string::npos) {
            emptyLines.push_back(l);
        }

        l++;
    }

    File.close();

    // Find empty columns
    int width = universe.at(0).length();
    for (int i = 0; i < width; i++) {
        string s;

        for (int j = 0; j < universe.size(); j++) {
            s += universe.at(j).at(i);
        }

        if (s.find("#") == string::npos) {
            emptyColumns.push_back(i);
        }
    }

    long int sum = 0;
    for (int i = 0; i < galaxies.size() - 1; i++) {
        for (int j = i + 1; j < galaxies.size(); j++) {
            auto g1 = galaxies.at(i);
            auto g2 = galaxies.at(j);

            // Base distance
            int dy = abs(g1.first - g2.first);
            int dx = abs(g1.second - g2.second);
            int d = dy + dx;

            // Handle empty lines
            int minY = min(g1.first, g2.first);
            int maxY = max(g1.first, g2.first);

            for (int m = minY; m < maxY; m++)
                if (find(emptyLines.begin(), emptyLines.end(), m) != emptyLines.end()) d += (size - 1);

            // Handle empty columns
            int minX = min(g1.second, g2.second);
            int maxX = max(g1.second, g2.second);

            for (int n = minX; n < maxX; n++)
                if (find(emptyColumns.begin(), emptyColumns.end(), n) != emptyColumns.end()) d += (size - 1);

            sum += d;
        }
    }

    return sum;
}

int main() {
    cout << "Advent of Code 2023 - Day 11" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << findShortestPaths("example.txt", 2) << endl;
    cout << "Result for input: " << findShortestPaths("input.txt", 2) << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << findShortestPaths("example.txt", 10) << endl;
    cout << "Result for input: " << findShortestPaths("input.txt", 1000000) << endl << endl;
}