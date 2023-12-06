#include <iostream>
#include <fstream>
#include <regex>
using namespace std;

void parseNumbers(string line, vector<int> * v) {
    regex r("([[:digit:]]+)");
    auto it = sregex_iterator(line.begin(), line.end(), r);
    auto end = sregex_iterator();

    for (auto k = it; k != end; ++k) {
        v->push_back(stoi((*k).str()));
    } 
}

int calculateWays(long int time, long int distance) {
    int n = 0;

    for (long int j = 0; j <= time/2; j++) {
        long int d = j * (time - j);
        if (d > distance) n++;
    }

    n *= 2;
    if (time%2 == 0) n--;

    return n;
}

int calculateProductForEachRace(string fileName) {
    string line;
    ifstream File(fileName);

    int product = 1;

    vector<int> time = {};
    vector<int> *p_time = &time;

    vector<int> distance = {};
    vector<int> *p_distance = &distance;

    getline(File, line);
    parseNumbers(line, p_time);

    getline(File, line);
    parseNumbers(line, p_distance);

    File.close();

    for (int i = 0; i < time.size(); i++) {
        product *= calculateWays(time.at(i), distance.at(i));
    }

    return product;
}

int calculateProductForMergedRace(string fileName) {
    string line;
    ifstream File(fileName);

    int product = 1;

    getline(File, line);
    long int time = stol(regex_replace(line, regex(R"([^\d])"), ""));

    getline(File, line);
    long int duration = stol(regex_replace(line, regex(R"([^\d])"), ""));
    
    return calculateWays(time, duration);
}

int main() {
    cout << "Advent of Code 2023 - Day 6" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateProductForEachRace("example.txt") << endl;
    cout << "Result for input: " << calculateProductForEachRace("input.txt") << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateProductForMergedRace("example.txt") << endl;
    cout << "Result for input: " << calculateProductForMergedRace("input.txt") << endl;
}