#include <iostream>
#include <fstream>
#include <map>
#include <regex>
using namespace std;

int hashCharacter(int value, char c) {
    int ascii = c;
    int v = value;

    v += ascii;
    v *= 17;
    v %= 256;    

    return v;
}

int hashString(string str) {
    int value = 0;

    for (auto c: str) {
        value = hashCharacter(value, c);
    }

    return value;
}

int hashSequence(string fileName) {
    string line;
    fstream File(fileName);

    int sum = 0;
    while (getline(File, line, ',')) {
        sum += hashString(line);
    }

    return sum;
}

int calculateFocusingPower(string fileName) {
    string line;
    fstream File(fileName);

    map<int, vector<pair<string, int>>> boxes{};

    while (getline(File, line, ',')) {
        smatch sm;
        regex_search(line.cbegin(), line.cend(), sm, regex("([a-z]+)([-=])([1-9]?)"));
        
        string label = sm[1].str();
        int key = hashString(label);
        
        string op = sm[2].str();

        if (op == "=") {
            int focal = stoi(sm[3].str());

            if (!boxes.count(key)) {
                boxes.insert({ key, {} });
            }

            auto lenses = boxes.at(key);
            auto start = boxes.at(key).begin();
            auto end = boxes.at(key).end();

            auto it = find_if(start, end, [label] (const pair<string, int>& s) { return s.first == label; } );
            if (it == end)
                boxes.at(key).push_back(pair(label, focal));
            else
                it->second = focal;
        } else if (op == "-") {
            if (!boxes.count(key)) continue;

            auto start = boxes.at(key).begin();
            auto end = boxes.at(key).end();
            auto it = find_if(start, end, [label] (const pair<string, int>& s) { return s.first == label; } );

            if (it == end) continue;

            boxes.at(key).erase(it);

            if (boxes.at(key).size() == 0) boxes.erase(key); 
        }
    }

    int sum = 0;
    for (auto b: boxes) {
        int box = b.first + 1;

        for (int i = 0; i < b.second.size(); i++) {
            int slot = i + 1;
            int focal = b.second.at(i).second;

            sum += (box * slot * focal);
        }
    }

    return sum;
}

int main() {
    cout << "Advent of Code 2023 - Day 15" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << hashSequence("example.txt") << endl;
    cout << "Result for input: " << hashSequence("input.txt") << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calculateFocusingPower("example.txt") << endl;
    cout << "Result for input: " << calculateFocusingPower("input.txt") << endl << endl;
}