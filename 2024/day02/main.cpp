#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

int maxOffset = 3;

bool descComp(int a, int b)
{
    return a > b;
}

bool isSafe(vector<int> report)
{
    if (is_sorted(report.begin(), report.end(), descComp))
        reverse(report.begin(), report.end());

    if (!is_sorted(report.begin(), report.end()))
        return false;

    vector<int>::iterator it;
    for (it = report.begin(); it != report.end() - 1; it++)
    {
        int offset = *(it + 1) - *it;
        if (offset <= 0 || offset > maxOffset)
            return false;
    }

    return true;
}

bool isDampenerSafe(vector<int> report)
{
    vector<vector<int>> combinations(size(report));
    for (int i = 0; i < size(report); i++)
    {
        for (int j = 0; j < size(report); j++)
        {
            if (i == j)
                continue;

            combinations[j].push_back(report[i]);
        }
    }

    for (auto r : combinations)
        if (isSafe(r))
            return true;

    return false;
}

vector<vector<int>> readFile(string fileName)
{
    string line;
    ifstream File(fileName);
    vector<vector<int>> reports;

    while (getline(File, line))
    {
        vector<int> report = {};
        stringstream ss(line);
        string t;
        char del = ' ';

        while (getline(ss, t, del))
            report.push_back(stoi(t));

        reports.push_back(report);
    }

    return reports;
}

int countSafeReports(vector<vector<int>> reports, bool dampener)
{
    int count = 0;
    for (auto report : reports)
        if (isSafe(report))
            count++;
        else if (dampener && isDampenerSafe(report))
            count++;

    return count;
}

int main()
{
    cout << "Advent of Code 2024 - Day 1" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << countSafeReports(example, false) << endl;
    cout << "Result for input: " << countSafeReports(input, false) << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << countSafeReports(example, true) << endl;
    cout << "Result for example: " << countSafeReports(input, true) << endl;
}