#include <fstream>
#include <iostream>
#include <string>
#include <set>
#include <map>

using namespace std;
using Coords = pair<int, int>;
using Data = tuple<Coords, Coords, vector<Coords>>;

Data readFile(string fileName)
{
    string line;
    fstream File(fileName);
    vector<Coords> obstacles;
    Coords start, max;

    int i = 0;
    while (getline(File, line))
    {
        max.second = line.size();

        for (int j = 0; j < line.size(); j++)
            if (line[j] == '#')
                obstacles.push_back({i, j});
            else if (line[j] == '^')
                start = {i, j};

        i++;
    }

    max.first = i;
    return {start, max, obstacles};
}

bool isLoop(Coords start, Coords max, vector<Coords> obstacles)
{
    set<pair<int, Coords>> turns;
    Coords currPos = start;

    vector<int> dirX = {-1, 0, 1, 0};
    vector<int> dirY = {0, 1, 0, -1};
    int dir = 0;

    while (true)
    {
        Coords nextPos = {
            currPos.first + dirX[dir],
            currPos.second + dirY[dir],
        };

        if (find(obstacles.begin(), obstacles.end(), nextPos) != obstacles.end())
        {
            dir = (dir + 1) % 4;
            pair<int, Coords> turn = {dir, currPos};

            if (turns.contains(turn))
                return true;

            turns.insert(turn);
            continue;
        }
        // Guard has reached top or left edge
        else if (currPos.first == 0 || currPos.second == 0)
            return false;
        // Guard has reached bottom or right edge
        else if (nextPos.first == max.first || nextPos.second == max.second - 1)
            return false;

        currPos = nextPos;
    }
}

pair<int, int> countDistinctPositions(Data data)
{
    auto [start, max, obstacles] = data;
    set<Coords> visited = {start};
    Coords currPos = start;

    vector<int> dirX = {-1, 0, 1, 0};
    vector<int> dirY = {0, 1, 0, -1};
    int dir = 0;

    while (true)
    {
        Coords nextPos = {
            currPos.first + dirX[dir],
            currPos.second + dirY[dir],
        };

        if (find(obstacles.begin(), obstacles.end(), nextPos) != obstacles.end())
        {
            dir = (dir + 1) % 4;
            continue;
        }
        // Guard has reached top or left edge
        else if (currPos != start && (currPos.first == 0 || currPos.second == 0))
            break;
        // Guard has reached bottom or right edge
        else if (currPos != start && (currPos.first == max.first - 1 || currPos.second == max.second - 1))
            break;

        currPos = nextPos;
        visited.insert(currPos);
    }

    int positions = visited.size();
    visited.erase(find(visited.begin(), visited.end(), start));

    int obstructions = 0;
    for (auto v : visited)
    {
        obstacles.push_back(v);

        if (isLoop(start, max, obstacles))
            obstructions++;

        obstacles.erase(find(obstacles.begin(), obstacles.end(), v));
    }

    return {positions, obstructions};
}

int main()
{
    cout << "Advent of Code 2024 - Day 6" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    auto [ex1, ex2] = countDistinctPositions(example);
    auto [in1, in2] = countDistinctPositions(input);

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << ex1 << endl;
    cout << "Result for input: " << in1 << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << ex2 << endl;
    cout << "Result for input: " << in2 << endl
         << endl;
}