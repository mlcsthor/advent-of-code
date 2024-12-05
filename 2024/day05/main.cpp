#include <fstream>
#include <iostream>
#include <map>
#include <sstream>

using namespace std;
using Rules = map<int, vector<int>>;
using Data = pair<Rules, vector<vector<int>>>;

Data readFile(string fileName)
{
    map<int, vector<int>> rules;
    vector<vector<int>> pages;

    string line;
    ifstream File(fileName);
    bool rulesOver = false;

    while (getline(File, line))
    {
        if (line == "")
            rulesOver = true;
        else if (rulesOver)
        {
            vector<int> pageList;
            stringstream ss(line);
            string page;

            while (getline(ss, page, ','))
                pageList.push_back(stoi(page));

            pages.push_back(pageList);
        }
        else
        {
            int a = stoi(line.substr(0, line.find('|')));
            int b = stoi(line.substr(line.find('|') + 1, line.length()));

            if (rules.find(a) == rules.end())
                rules.insert({a, {}});

            rules.at(a).push_back(b);
        }
    }

    return {rules, pages};
}

bool comp(int lhs, int rhs, Rules rules, vector<int> pages)
{
    if (rules.find(rhs) == rules.end())
        return true;

    auto r = rules.at(rhs);
    if (find(r.begin(), r.end(), lhs) == r.end())
        return true;

    auto aIdx = find(pages.begin(), pages.end(), rhs);
    auto bIdx = find(pages.begin(), pages.end(), lhs);

    return bIdx < aIdx;
}

pair<int, int> sumMiddlePageNumbers(Data data)
{
    auto [rules, pages] = data;
    int sumCorrect = 0;
    int sumIncorrect = 0;

    for (auto p : pages)
    {
        bool sorted = is_sorted(p.begin(), p.end(), [&p, &rules](const auto &lhs, const auto &rhs)
                                { return comp(lhs, rhs, rules, p); });
        if (sorted)
            sumCorrect += p[p.size() / 2];
        else
        {
            sort(p.begin(), p.end(), [&p, &rules](const auto &lhs, const auto &rhs)
                 { return comp(lhs, rhs, rules, p); });
            sumIncorrect += p[p.size() / 2];
        }
    }

    return {sumCorrect, sumIncorrect};
}

int main()
{
    cout << "Advent of Code 2024 - Day 5" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    auto [examplePart1, examplePart2] = sumMiddlePageNumbers(example);
    auto [inputPart1, inputPart2] = sumMiddlePageNumbers(input);

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << examplePart1 << endl;
    cout << "Result for input: " << inputPart1 << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << examplePart2 << endl;
    cout << "Result for input: " << inputPart2 << endl;
}