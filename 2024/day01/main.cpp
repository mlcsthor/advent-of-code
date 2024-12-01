#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;

tuple<vector<int>, vector<int>> readFile(string fileName)
{
    string line;
    ifstream File(fileName);
    vector<int> first, second;

    while (getline(File, line))
    {
        int f = stoi(line.substr(0, line.find_first_of(' ')));
        int s = stoi(line.substr(line.find_last_of(' ') + 1, line.length()));

        first.push_back(f);
        second.push_back(s);
    }

    return {first, second};
}

int calculateDistance(tuple<vector<int>, vector<int>> data)
{
    auto [first, second] = data;
    sort(first.begin(), first.end());
    sort(second.begin(), second.end());

    auto it1 = first.begin();
    auto it2 = second.begin();
    int sum = 0;
    for (; it1 != first.end() && it2 != second.end(); ++it1, ++it2)
    {
        sum += abs(*it1 - *it2);
    }

    return sum;
}

int calculateSimilarityScore(tuple<vector<int>, vector<int>> data)
{
    auto [first, second] = data;
    map<int, int> occurences;

    for (auto s : second)
    {
        if (occurences.find(s) == occurences.end())
        {
            occurences.insert({s, 0});
        }

        occurences.at(s)++;
    }

    int sum = 0;
    for (auto f : first)
    {
        if (occurences.find(f) != occurences.end())
        {
            sum += occurences.at(f) * f;
        }
    }

    return sum;
}

int main()
{
    cout << "Advent of Code 2024 - Day 1" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << calculateDistance(example) << endl;
    cout << "Result for input: " << calculateDistance(input) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << calculateSimilarityScore(example) << endl;
    cout << "Result for input: " << calculateSimilarityScore(input) << endl
         << endl;
}