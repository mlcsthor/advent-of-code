#include <fstream>
#include <iostream>
#include <string>
#include <regex>
#include <set>

using namespace std;

struct Robot
{
    pair<int, int> pos;
    pair<int, int> velocity;
};

volatile sig_atomic_t stop;

vector<Robot> readFile(string fileName)
{
    string line;
    fstream File(fileName);

    vector<Robot> robots;
    regex r("p=([0-9]+),([0-9]+) v=([-0-9]+),([-0-9]+)");

    while (getline(File, line))
    {
        smatch sm;
        regex_match(line, sm, r);

        Robot robot;
        robot.pos = {stoi(sm[1]), stoi(sm[2])};
        robot.velocity = {stoi(sm[3]), stoi(sm[4])};
        robots.push_back(robot);
    }

    return robots;
}

int calcSafetyFactor(vector<Robot> robots, int seconds, int cols, int rows)
{
    int cRow = int(rows / 2);
    int cCol = int(cols / 2);
    int NO = 0, NE = 0, SO = 0, SE = 0;

    for (auto r : robots)
    {
        int x = (r.pos.first + seconds * r.velocity.first) % cols;
        if (x < 0)
            x += cols;

        int y = (r.pos.second + seconds * r.velocity.second) % rows;
        if (y < 0)
            y += rows;

        if (x < cCol)
        {
            if (y < cRow)
                NO++;
            else if (y > cRow)
                SO++;
        }
        else if (x > cCol)
        {
            if (y < cRow)
                NE++;
            else if (y > cRow)
                SE++;
        }
    }

    return NO * NE * SO * SE;
}

int findChristmasTree(vector<Robot> robots, int seconds, int cols, int rows)
{
    set<pair<int, int>> posSet;

    int i;
    for (i = 1; i < seconds; i++)
    {

        for (auto it = robots.begin(); it != robots.end(); it++)
        {
            int x = (it->pos.first + it->velocity.first) % cols;
            if (x < 0)
                x += cols;

            int y = (it->pos.second + it->velocity.second) % rows;
            if (y < 0)
                y += rows;

            it->pos = {x, y};
            posSet.insert({x, y});
        }

        if (robots.size() == posSet.size())
            break;

        posSet.clear();
    }

    return i;
}

int main()
{
    cout << "Advent of Code 2024 - Day 14" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << calcSafetyFactor(example, 100, 11, 7) << endl;
    cout << "Result for input: " << calcSafetyFactor(input, 100, 101, 103) << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for input: " << findChristmasTree(input, 10000, 101, 103) << endl
         << endl;
}