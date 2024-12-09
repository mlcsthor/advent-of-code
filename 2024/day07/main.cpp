#include <fstream>
#include <string>
#include <iostream>
#include <sstream>
#include <chrono>

using namespace std;
using namespace std::chrono;
using Data = vector<pair<uint64_t, vector<uint64_t>>>;

Data readFile(string fileName)
{
    string line;
    fstream File(fileName);
    Data operations;

    while (getline(File, line))
    {
        string t;
        stringstream ss(line);

        getline(ss, t, ':');
        uint64_t target = stol(t);

        string nb;
        vector<uint64_t> numbers;
        while (getline(ss, nb, ' '))
            if (nb != "")
                numbers.push_back(stol(nb));

        operations.push_back({target, numbers});
    }

    return operations;
}

bool check(uint64_t target, vector<uint64_t> prev, vector<uint64_t> next, bool concat)
{
    auto curr = next[0];
    next.erase(next.begin());

    vector<uint64_t> results;
    for (auto p : prev)
    {
        if (p % curr == 0)
            results.push_back(p / curr);

        results.push_back(p - curr);

        auto diff = p - curr;
        if (diff == 0)
            continue;

        results.push_back(p - curr);

        if (!concat)
            continue;

        auto t = int(pow(10, (floor(log10(curr)) + 1)));
        if (diff % t == 0)
            results.push_back(diff / t);
    }

    if (next.empty())
        return find(results.begin(), results.end(), target) != results.end();

    return check(target, results, next, concat);
}

long execute(Data data, bool concat)
{
    long sum = 0;
    for (auto o : data)
    {
        auto target = o.second[0];
        o.second.erase(o.second.begin());
        reverse(o.second.begin(), o.second.end());

        if (check(target, {o.first}, o.second, concat))
            sum += o.first;
    }

    return sum;
}

int main()
{
    cout << "Advent of Code 2024 - Day 7" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << execute(example, false) << endl;
    cout << "Result for input: " << execute(input, false) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << execute(example, true) << endl;
    cout << "Result for input: " << execute(input, true) << endl
         << endl;
}