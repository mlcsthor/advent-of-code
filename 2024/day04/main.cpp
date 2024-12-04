#include <fstream>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

vector<string> readFile(string fileName)
{
    string line;
    ifstream File(fileName);
    vector<string> content;

    while (getline(File, line))
        content.push_back(line);

    return content;
}

int search2D(vector<string> grid, int row, int col, string word)
{
    // Character is not first of word -> skip
    if (grid[row][col] != word[0])
        return 0;

    int rows = grid.size();
    int cols = grid[0].size();
    int len = word.size();

    // Directions in which word needs to be cherched
    vector<int> x = {-1, -1, -1, 0, 0, 1, 1, 1};
    vector<int> y = {-1, 0, 1, -1, 1, -1, 0, 1};

    int count = 0;
    for (int d = 0; d < x.size(); d++)
    {
        // Starting point
        int k, currX = row + x[d], currY = col + y[d];

        for (k = 1; k < len; k++)
        {
            // x is OOB
            if (currX > rows || currX < 0)
                break;

            // y is OOB
            if (currY > cols || currY < 0)
                break;

            if (grid[currX][currY] != word[k])
                break;

            // Move in current direction
            currX += x[d];
            currY += y[d];
        }

        if (k == len)
            count++;
    }

    return count;
}

bool searchX(vector<string> grid, int row, int col, string word)
{
    // Character is not center of word -> skip
    if (grid[row][col] != word[word.size() / 2])
        return false;

    int minOffset = 1, maxOffset = grid[0].size() - 2;

    // x is too close of an edge
    if (col < minOffset || col > maxOffset)
        return false;

    // y is too close of an edge
    if (row < minOffset || col > maxOffset)
        return false;

    string firstDiag, secondDiag;
    firstDiag += grid[row - 1][col - 1];
    firstDiag += grid[row + 1][col + 1];
    secondDiag += grid[row - 1][col + 1];
    secondDiag += grid[row + 1][col - 1];

    bool firstOk = (firstDiag == "SM" || firstDiag == "MS");
    bool secondOk = (secondDiag == "SM" || secondDiag == "MS");

    return (firstOk && secondOk);
}

int searchWord(vector<string> grid, string word)
{
    int rows = grid.size();
    int cols = grid[0].size();

    int count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            count += search2D(grid, i, j, word);

    return count;
}

int searchXWord(vector<string> grid, string word)
{
    int rows = grid.size();
    int cols = grid[0].size();

    int count = 0;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < cols; j++)
            if (searchX(grid, i, j, word))
                count++;

    return count;
}

int main()
{
    cout << "Advent of Code 2024 - Day 4" << endl
         << endl;

    auto example = readFile("example.txt");
    auto input = readFile("input.txt");

    cout
        << "Part 1" << endl;
    cout << "Result for example: " << searchWord(example, "XMAS") << endl;
    cout << "Result for input: " << searchWord(input, "XMAS") << endl
         << endl;

    cout
        << "Part 2" << endl;
    cout << "Result for example: " << searchXWord(example, "MAS") << endl;
    cout << "Result for input: " << searchXWord(input, "MAS") << endl
         << endl;
}