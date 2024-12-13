#include <fstream>
#include <iostream>
#include <string>
#include <vector>
#include <map>

using namespace std;
map<long long, map<int, long>> cache;

vector<long long> readFile(string fileName)
{
    string line;
    fstream File(fileName);

    vector<long long> nbs;
    while (getline(File, line, ' '))
        nbs.push_back(stoll(line));

    return nbs;
}

int blink(long stone, int c)
{
    if (c == 0)
    {
        if (stone == 0)
            return 1;

        string sstr = to_string(stone);
        if (sstr.length() % 2 == 1)
            return 1;

        return 2;
    }

    if (!cache.contains(stone))
        cache.insert({stone, {}});

    if (cache.at(stone).contains(c - 1))
        return cache.at(stone).at(c - 1);

    string sstr = to_string(stone);
    if (stone == 0)
        cache.at(stone).insert({c - 1, blink(1, c - 1)});
    else if (sstr.length() % 2 == 1)
        cache.at(stone).insert({c - 1, blink(stone * 2024, c - 1)});
    else
    {
        long long half = stoll(sstr.substr(0, sstr.length() / 2));
        long long otherHalf = stoll(sstr.substr(sstr.length() / 2));
        cache.at(stone).insert({c - 1, blink(half, c - 1) + blink(otherHalf, c - 1)});
    }

    return cache.at(stone).at(c - 1);
}

int blinkStones(vector<long long> stones, int c)
{
    cache.clear();
    int count = 0;

    for (auto s : stones)
        count += blink(s, c - 1);

    return count;
}

int main()
{
    cout << "Advent of Code 2024 - Day 8" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << blinkStones(example, 25) << endl;
    cout << "Result for input: " << blinkStones(input, 25) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for input: " << blinkStones(input, 75) << endl
         << endl;
}