#include <algorithm>
#include <cctype>
#include <cstring>
#include <fstream>
#include <iostream>
#include <numeric>
#include <regex>
#include <string>
#include <utility>
#include <vector>

using namespace std;

using Problem = pair<string, vector<long>>;

vector<Problem> readFile(string fileName) {
    string line;
    ifstream File(fileName);
    vector<Problem> problems;

    auto rNb = regex(R"(([0-9]+))");
    smatch m;
    bool firstLine = true;

    while (getline(File, line) && regex_search(line, m, rNb)) {
        sregex_token_iterator it{line.begin(), line.end(), rNb, 1};
        sregex_token_iterator end;

        int i = 0;
        while (it != end) {
            if (firstLine)
                problems.push_back({"", {}});

            problems[i++].second.push_back((stol(*it++)));
        }

        if (firstLine)
            firstLine = false;
    }

    auto rOp = regex(R"((\+|\*))");
    sregex_token_iterator it{line.begin(), line.end(), rOp, 1};
    sregex_token_iterator end;

    int i = 0;
    while (it != end)
        problems[i++].first = *it++;

    return problems;
}

vector<Problem> readFilePart2(string fileName) {
    string line;
    ifstream File(fileName);

    vector<string> columns;
    bool firstLine = true;

    while (getline(File, line)) {
        for (int i = 0; i < line.size(); i++) {
            if (i >= columns.size())
                columns.push_back("");

            columns[i] += line[i];
        }
    }

    vector<Problem> problems = {{"", {}}};
    int i = 0;

    for (auto c : columns) {
        c.erase(remove_if(c.begin(), c.end(), ::isspace), c.end());

        if (c == "") {
            problems.push_back({"", {}});
            i++;
            continue;
        }

        if (c.back() == '*' || c.back() == '+') {
            problems[i].first = c.back();
            c.pop_back();
        }

        problems[i].second.push_back(stol(c));
    }

    return problems;
}

long sumProblems(vector<Problem> problems) {
    long r = 0;

    for (auto [op, nb] : problems) {
        r += accumulate(nb.begin() + 1, nb.end(), *nb.begin(),
                        [op](long acc, long v) {
                            if (op == "+") {
                                return acc + v;
                            } else {
                                return acc * v;
                            }
                        });
    }

    return r;
}

int main() {
    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << sumProblems(example) << endl;
    cout << "Result for input: " << sumProblems(input) << endl;

    auto example2 = readFilePart2("example.txt");
    auto input2 = readFilePart2("input.txt");

    cout << "Part 1" << endl;
    cout << "Result for example: " << sumProblems(example2) << endl;
    cout << "Result for input: " << sumProblems(input2) << endl;
}
