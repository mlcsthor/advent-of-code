#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <numeric>

using namespace std;
using Coords = pair<long, long>;
using Input = vector<Coords>;

Input parseInput(vector<string> lines)
{
    regex btnRegex("Button [AB]: X[+]([0-9]+), Y[+]([0-9]+)");
    regex priceRegex("Prize: X=([0-9]+), Y=([0-9]+)");

    smatch btnA;
    regex_match(lines[0], btnA, btnRegex);
    Coords coordsBtnA = {stol(btnA[1]), stol(btnA[2])};

    smatch btnB;
    regex_match(lines[1], btnB, btnRegex);
    Coords coordsBtnB = {stol(btnB[1]), stol(btnB[2])};

    smatch price;
    regex_match(lines[2], price, priceRegex);
    Coords coordsPrice = {stol(price[1]), stol(price[2])};

    return {coordsBtnA, coordsBtnB, coordsPrice};
}

vector<Input> readFile(string fileName)
{
    string line;
    fstream File(fileName);

    vector<string> lines;
    vector<Input> inputs;
    while (getline(File, line))
    {
        if (line == "")
        {
            inputs.push_back(parseInput(lines));
            lines.clear();
        }
        else
            lines.push_back(line);
    }

    inputs.push_back(parseInput(lines));

    return inputs;
}

long calc(vector<Input> inputs, long offset)
{
    long sum = 0;
    for (auto i : inputs)
    {
        auto a = i[0], b = i[1], p = i[2];
        p = {p.first + offset, p.second + offset};

        auto x = (b.second * p.first - b.first * p.second * 1.0) /
                 (b.second * a.first - a.second * b.first);
        auto y = (p.first - a.first * x) / b.first;

        if (x == floor(x) && y == floor(y))
            sum += (3 * x + y);
    }

    return sum;
}

int main()
{
    cout << "Advent of Code 2024 - Day 13" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << calc(example, 0) << endl;
    cout << "Result for input: " << calc(input, 0) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << calc(example, 10000000000000) << endl;
    cout << "Result for input: " << calc(input, 10000000000000) << endl
         << endl;
}