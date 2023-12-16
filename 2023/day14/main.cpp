#include <iostream>
#include <fstream>
#include <string>
using namespace std;

string moveRocks(string str) {
    auto cube = str.find('#');

    if (cube == string::npos) {
        string s = str;
        sort(s.begin(), s.end(), greater<char>());
        return s;
    }

    string s = str.substr(0, cube);
    sort(s.begin(), s.end(), greater<char>());

    return s + '#' + moveRocks(str.substr(cube + 1));
}

vector<string> tilt(vector<string> &lines, bool rev) {
    cout << endl;

    int width = lines.at(0).size();
    vector<string> tilted(width);

    for (int i = 0; i < width; i++) {
        for (auto l: lines) {
            tilted.at(i).push_back(l.at(i));
        }
    }

    if (rev) reverse(tilted.begin(), tilted.end());

    for (int i = 0; i < tilted.size(); i++) {
        tilted.at(i) = moveRocks(tilted.at(i));
    }

    return tilted;
}

int computeLoad(vector<string> &lines) {
    int sum = 0;
    for (int i = 0; i < lines.size(); i++) {
        string line = lines.at(i);

        for (int j = 0; j < line.size(); j++)
            if (line.at(j) == 'O')
                sum += (lines.size() - j);
    }

    return sum;
}

int calculateTotalLoad(string fileName) {
    string line;
    fstream File(fileName);

    vector<string> lines{};

    while (getline(File, line)) {
        lines.push_back(line);
    }

    File.close();

    auto tiltedNorth = tilt(lines, false);

    return computeLoad(tiltedNorth);
}

int calculateTotalLoadWithCycles(string fileName, int cycles) {
    string line;
    fstream File(fileName);

    vector<string> lines{};

    while (getline(File, line)) {
        lines.push_back(line);
    }

    File.close();

    for (int i = 0; i < cycles; i ++) {
        for (int j = 0; j < 4; j++) {
            auto newLines = tilt(lines, i == 2 || i == 3);
            lines.swap(newLines);
        }
    }

    return computeLoad(lines); 
}

int main() {
    cout << "Advent of Code 2023 - Day 14" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateTotalLoad("example.txt") << endl;
    cout << "Result for input: " << calculateTotalLoad("input.txt") << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calculateTotalLoadWithCycles("example.txt", 2) << endl;
    //cout << "Result for input: " << calculateTotalLoadWithCycles("input.txt", 1001) << endl;
}