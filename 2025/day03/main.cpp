#include <algorithm>
#include <cmath>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<vector<int>> readFile(string fileName) {
    string line;
    ifstream File(fileName);
    vector<vector<int>> batteryList;

    while (getline(File, line)) {
        vector<int> batteries;

        for (auto c : line) {
            batteries.push_back(c - '0');
        }

        batteryList.push_back(batteries);
    }

    return batteryList;
}

long sumJoltage(vector<vector<int>> batteryList, int size) {
    long joltage = 0;

    for (auto batteries : batteryList) {
        long currentJoltage = 0;

        auto start = batteries.begin();
        auto end = batteries.end() - (size - 1);

        for (int i = 1; i <= size; i++) {
            auto max = max_element(start, end);
            currentJoltage += *max * pow(10, size - i);

            start = max + 1;
            end += 1;
        }

        joltage += currentJoltage;
    }

    return joltage;
}

int main() {
    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << sumJoltage(example, 2) << endl;
    cout << "Result for input: " << sumJoltage(input, 2) << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << sumJoltage(example, 12) << endl;
    cout << "Result for input: " << sumJoltage(input, 12) << endl;
}
