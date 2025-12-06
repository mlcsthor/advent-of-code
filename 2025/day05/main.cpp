#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <tuple>
#include <utility>
#include <vector>

using namespace std;

using Range = pair<long, long>;

pair<vector<Range>, vector<long>> readFile(string fileName) {
    string line;
    ifstream File(fileName);

    vector<Range> ranges;
    vector<long> ids;
    bool pastBlankLine = false;

    while (getline(File, line)) {
        if (line == "")
            pastBlankLine = true;
        else if (pastBlankLine) {
            ids.push_back(stol(line));
        } else {
            int sepIdx = line.find_first_of('-');
            auto start = line.substr(0, sepIdx);
            auto end = line.substr(sepIdx + 1, line.length());

            ranges.push_back({stol(start), stol(end)});
        }
    }

    sort(ranges.begin(), ranges.end());

    return {ranges, ids};
}

int calcNbFresh(pair<vector<Range>, vector<long>> data) {
    auto [ranges, ids] = data;
    int count = 0;

    for (auto id : ids) {
        auto it = find_if(ranges.begin(), ranges.end(), [id](const Range& e) {
            return e.first <= id && e.second >= id;
        });

        if (it != ranges.end())
            count++;
    }

    return count;
}

long calcRangeSize(vector<Range> ranges) {
    long count = 0;

    auto range = ranges.begin();
    for (auto it = ranges.begin() + 1; it < ranges.end(); it++) {
        if ((*it).first <= (*range).second + 1)
            (*range).second = max((*range).second, (*it).second);
        else {
            count += ((*range).second - (*range).first + 1);
            range = it;
        }
    }

    count += ((*range).second - (*range).first + 1);

    return count;
}

int main() {
    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << calcNbFresh(example) << endl;
    cout << "Result for input: " << calcNbFresh(input) << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calcRangeSize(example.first) << endl;
    cout << "Result for input: " << calcRangeSize(input.first) << endl;
}
