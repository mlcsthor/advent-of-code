#include <fstream>
#include <iostream>
#include <string>
#include <map>
#include <set>
#include <sstream>

using namespace std;
using Frequencies = map<char, vector<pair<int, int>>>;
using Data = pair<Frequencies, pair<int, int>>;

Data readFile(string fileName)
{
    string line;
    fstream File(fileName);
    Frequencies frequencies;

    int i = 0;
    while (getline(File, line))
    {
        for (int j = 0; j < line.length(); j++)
        {
            if (line[j] == '.')
                continue;

            if (!frequencies.contains(line[j]))
                frequencies.insert({line[j], {}});

            frequencies.at(line[j]).push_back({i, j});
        }

        i++;
    }

    return {frequencies, {i, line.length()}};
}

bool isInBound(pair<int, int> c, pair<int, int> max)
{
    if (c.first < 0 || c.second < 0)
        return false;

    if (c.first >= max.first || c.second >= max.second)
        return false;

    return true;
}

int countLocations(Data data)
{
    auto [frequencies, max] = data;

    set<pair<int, int>> locations;
    for (auto [_, coords] : frequencies)
    {
        for (auto i1 = coords.begin(); i1 != coords.end() - 1; i1++)
        {
            for (auto i2 = i1 + 1; i2 != coords.end(); i2++)
            {
                int dx = i2->first - i1->first;
                int dy = i2->second - i1->second;

                pair<int, int> an1 = {i1->first - dx, i1->second - dy};
                pair<int, int> an2 = {i2->first + dx, i2->second + dy};

                if (isInBound(an1, max))
                    locations.insert(an1);

                if (isInBound(an2, max))
                    locations.insert(an2);
            }
        }
    }

    return locations.size();
}

int countResonantLocations(Data data)
{
    auto [frequencies, max] = data;

    set<pair<int, int>> locations;
    for (auto [_, coords] : frequencies)
    {
        for (auto i1 = coords.begin(); i1 != coords.end() - 1; i1++)
        {
            for (auto i2 = i1 + 1; i2 != coords.end(); i2++)
            {
                int dx = i2->first - i1->first;
                int dy = i2->second - i1->second;

                pair<int, int> an1 = {i1->first, i1->second};
                pair<int, int> an2 = {i2->first, i2->second};

                int f1 = 0;
                while (isInBound(an1, max))
                {
                    locations.insert(an1);
                    f1++;
                    an1.first = i1->first - dx * f1;
                    an1.second = i1->second - dy * f1;
                }

                int f2 = 0;
                while (isInBound(an2, max))
                {
                    locations.insert(an2);
                    f2++;
                    an2.first = i2->first + dx * f2;
                    an2.second = i2->second + dy * f2;
                }
            }
        }
    }

    return locations.size();
}

int main()
{
    cout << "Advent of Code 2024 - Day 8" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << countLocations(example) << endl;
    cout << "Result for input: " << countLocations(input) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << countResonantLocations(example) << endl;
    cout << "Result for input: " << countResonantLocations(input) << endl
         << endl;
}