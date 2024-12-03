#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

string readFile(string fileName)
{
    string content;
    string line;
    ifstream File(fileName);

    while (getline(File, line))
        content += line;

    return content;
}

int run(string content)
{
    string::const_iterator start = content.begin();
    string::const_iterator end = content.end();
    regex rx("mul[(]([0-9]{1,3}),([0-9]{1,3})[)]");
    smatch m;

    int sum = 0;

    while (regex_search(start, end, m, rx))
    {
        int first = stoi(m[1].str());
        int second = stoi(m[2].str());
        sum += first * second;

        start = m[0].second;
    }

    return sum;
}

int runWithInstructions(string content)
{
    string doInstr = "do";
    string doNotInstr = "don't";

    string::const_iterator start = content.begin();
    string::const_iterator end = content.end();
    regex rx("mul[(]([0-9]{1,3}),([0-9]{1,3})[)]|" + doNotInstr + "|" + doInstr);
    smatch m;

    bool enabled = true;
    int sum = 0;

    while (regex_search(start, end, m, rx))
    {
        if (m[0].str() == doNotInstr)
            enabled = false;
        else if (m[0].str() == doInstr)
            enabled = true;
        else if (enabled)
        {
            int first = stoi(m[1].str());
            int second = stoi(m[2].str());
            sum += first * second;
        }

        start = m[0].second;
    }

    return sum;
}

int main()
{
    cout << "Advent of Code 2024 - Day 3" << endl
         << endl;

    auto example = readFile("example.txt");
    auto example2 = readFile("example2.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << run(example) << endl;
    cout << "Result for input: " << run(input) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << runWithInstructions(example2) << endl;
    cout << "Result for input: " << runWithInstructions(input) << endl
         << endl;
}