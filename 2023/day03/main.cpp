#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

void parseNumbers(string line, int l, vector<tuple<int, int, int, int>> * parts) {
    int offset = 0;
    smatch sm;
    string::const_iterator searchStart(line.cbegin());
    
    while(regex_search(searchStart, line.cend(), sm, regex("([[:digit:]]+)"))) {
        int position = offset + sm.position(1);
        int end = position + sm[1].length() - 1;

        parts->push_back({ l, position, end, stoi(sm[1])});

        offset = end + 1;
        searchStart = sm.suffix().first;
    }
}

void parseSymbols(string line, int l, vector<pair<int, int>> * symbols) {
    int offset = 0;
    smatch sm;
    string::const_iterator searchStart(line.cbegin());
    
    while(regex_search(searchStart, line.cend(), sm, regex("([^.[:digit:]])"))) {
        int position = offset + sm.position(1);

        symbols->push_back({ l, position });

        offset = position + 1;
        searchStart = sm.suffix().first;
    }
}

vector<pair<int, int>> generateCoords(tuple<int, int, int, int> part) {
    int y = get<0>(part);
    int x1 = get<1>(part);
    int x2 = get<2>(part);

    vector<pair<int, int>> coords = {{ x1 -1, y }, { x2 + 1, y }};
    for (int i = x1 - 1; i < x2 + 2; i++) {
        coords.push_back({ i, y - 1 });
        coords.push_back({ i, y + 1 });
    }

    sort(coords.begin(), coords.end());

    return coords;
}

bool checkCoord(vector<pair<int, int>> symbols, pair<int, int> coord) {
    for (auto symbol: symbols) {
        if (get<0>(coord) == get<1>(symbol) && get<1>(coord) == get<0>(symbol)) return true;
    }

    return false;
}

int calculatePartsSum(string fileName) {
    string line;
    ifstream File(fileName);
    int l = 0;
    int sum = 0;

    vector<tuple<int, int, int, int>> parts = {};
    vector<tuple<int, int, int, int>> * p_parts = &parts;

    vector<pair<int, int>> symbols = {};
    vector<pair<int, int>> * p_symbols = &symbols;

    while (getline(File, line)) {
        parseNumbers(line, l, p_parts);
        parseSymbols(line, l, p_symbols);

        l++;
    }

    File.close();

    for (auto &part: parts) {
        for (auto &coord: generateCoords(part)) {
            if (checkCoord(symbols, coord)) {
                sum += get<3>(part);
                break;
            }
        }
    }

    return sum;
}

int calculateGearRatio(string fileName) {
    string line;
    ifstream File(fileName);
    int l = 0;
    int sum = 0;

    vector<tuple<int, int, int, int>> parts = {};
    vector<tuple<int, int, int, int>> * p_parts = &parts;

    vector<pair<int, int>> symbols = {};
    vector<pair<int, int>> * p_symbols = &symbols;

    while (getline(File, line)) {
        parseNumbers(line, l, p_parts);
        parseSymbols(line, l, p_symbols);

        l++;
    }

    for (size_t i = 0; i < parts.size(); i++) {
        for (size_t j = i + 1; j < parts.size(); j++) {
            if (abs(get<0>(parts[i]) - get<0>(parts[j])) > 2) continue;

            auto firstCoords = generateCoords(parts[i]);
            auto secondCoords = generateCoords(parts[j]);
            vector<pair<int, int>> intersection(firstCoords.size() + secondCoords.size());

            auto it = set_intersection(firstCoords.begin(), firstCoords.end(), secondCoords.begin(), secondCoords.end(), intersection.begin());
            intersection.resize(it - intersection.begin());   

            if (intersection.size() == 0) continue;

            for (auto &coord: intersection) {
                if (checkCoord(symbols, coord)) {
                    sum += get<3>(parts[i]) * get<3>(parts[j]);
                    break;
                }   
            }
        }
    }

    return sum;
}

int main() {
    cout << "Advent of Code 2023 - Day 2" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculatePartsSum("example.txt") << endl;
    cout << "Result for input: " << calculatePartsSum("input.txt") << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calculateGearRatio("example.txt") << endl;
    cout << "Result for input: " << calculateGearRatio("input.txt") << endl;
}