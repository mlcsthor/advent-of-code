#include <fstream>
#include <iostream>
#include <regex>
#include <string>
#include <tuple>
#include <vector>

using namespace std;

const auto r1 = regex(R"(^(\d+)\1$)");
const auto r2 = regex(R"(^(\d+)\1+$)");

vector<tuple<long, long>> readFile(string fileName) {
    string line;
    ifstream File(fileName);
    vector<tuple<long, long>> ranges;

    while (getline(File, line, ',')) {
        auto start = line.substr(0, line.find_first_of('-'));
        auto end = line.substr(line.find_last_of('-') + 1, line.length());

        ranges.push_back({stol(start), stol(end)});
    }

    return ranges;
}

long sumInvalidID(vector<tuple<long, long>> ranges, regex r) {
    long count = 0;

    for (auto [start, end] : ranges) {
        for (long i = start; i <= end; i++) {
            if (regex_match(to_string(i), r)) {
                count += i;
            }
        }
    }

    return count;
}

int main() {
    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << sumInvalidID(example, r1) << endl;
    cout << "Result for input: " << sumInvalidID(input, r1) << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << sumInvalidID(example, r2) << endl;
    cout << "Result for input: " << sumInvalidID(input, r2) << endl;
}
