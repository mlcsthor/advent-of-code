#include <iostream>
#include <fstream>
#include <map>
#include <chrono>
#include <regex>
using namespace std;

struct Pipe {
    char type;
    pair<int, int> first;
    pair<int, int> second;

    Pipe(const char &t, const int &x1, const int &y1, const int &x2, const int &y2) {
        type = t;
        first = pair(x1, y1);
        second = pair(x2, y2);
    }

    auto getNext(pair<int, int> from) {
        return (first == from) ? second : first;
    }
};

int getFarthestTile(string fileName) {
    string line;
    fstream File(fileName);

    map<pair<int, int>, Pipe> pipes{};
    pair<int, int> start(-5, -5);

    int l = 0;
    while (getline(File, line)) {
        for (int c = 0; c < line.length(); c++) {
            if (line.at(c) == '.') continue;

            pair<int, int> n1{}, n2{};
            switch(line.at(c)) {
                case 'F':
                    n1 = pair(l + 1, c);
                    n2 = pair(l, c + 1);
                    break;
                case '7':
                    n1 = pair(l + 1, c);
                    n2 = pair(l, c - 1);
                    break;
                case 'J':
                    n1 = pair(l - 1, c);
                    n2 = pair(l, c - 1);
                    break;
                case 'L':
                    n1 = pair(l - 1,  c);
                    n2 = pair(l, c + 1);
                    break;
                case '|':
                    n1 = pair(l - 1, c);
                    n2 = pair(l + 1, c);
                    break;
                case '-':
                    n1 = pair(l, c - 1);
                    n2 = pair(l, c + 1);
                    break;
                case 'S':
                    start = pair(l, c);
                    continue;
            }
            
            Pipe p(line.at(c), n1.first, n1.second, n2.first, n2.second);
            pipes.insert({ pair(l, c), p });
        }

        l++;
    }

    vector<pair<int, int>> sn{
        pair(start.first - 1, start.second), pair(start.first + 1, start.second),
        pair(start.first, start.second - 1), pair(start.first, start.second + 1),
        pair(start.first - 1, start.second - 1), pair(start.first - 1, start.second + 1),
        pair(start.first + 1, start.second - 1), pair(start.first + 1, start.second + 1),
    };

    pair<int, int> from = start;
    pair<int, int> pc;

    for (int i = 0; i < sn.size(); i++) {
        auto it = pipes.find(sn.at(i));

        if (it != pipes.end()) {
            auto pipe = (*it).second;
            if (pipe.first == start || pipe.second == start) {
                pc = (*it).first;
                break;
            }
        }
    }

    int length = 1;
    while (pc != start) {
        auto p = pipes.at(pc);
        auto n = p.getNext(from);

        from = pc;
        pc = n;
        length++;
    }

    length /= 2;

    return length;
}

int getEnclosedTile(string fileName) {
    string line;
    fstream File(fileName);

    map<pair<int, int>, Pipe> pipes{};
    pair<int, int> start(-5, -5);

    int l = 0;
    int w = 0;
    while (getline(File, line)) {
        w = line.length();
        for (int c = 0; c < w; c++) {
            if (line.at(c) == '.') continue;

            pair<int, int> n1{}, n2{};
            switch(line.at(c)) {
                case 'F':
                    n1 = pair(l + 1, c);
                    n2 = pair(l, c + 1);
                    break;
                case '7':
                    n1 = pair(l + 1, c);
                    n2 = pair(l, c - 1);
                    break;
                case 'J':
                    n1 = pair(l - 1, c);
                    n2 = pair(l, c - 1);
                    break;
                case 'L':
                    n1 = pair(l - 1,  c);
                    n2 = pair(l, c + 1);
                    break;
                case '|':
                    n1 = pair(l - 1, c);
                    n2 = pair(l + 1, c);
                    break;
                case '-':
                    n1 = pair(l, c - 1);
                    n2 = pair(l, c + 1);
                    break;
                case 'S':
                    start = pair(l, c);
                    continue;
            }
            
            Pipe p(line.at(c), n1.first, n1.second, n2.first, n2.second);
            pipes.insert({ pair(l, c), p });
        }

        l++;
    }

    vector<pair<int, int>> sn{
        pair(start.first - 1, start.second), pair(start.first + 1, start.second),
        pair(start.first, start.second - 1), pair(start.first, start.second + 1),
        pair(start.first - 1, start.second - 1), pair(start.first - 1, start.second + 1),
        pair(start.first + 1, start.second - 1), pair(start.first + 1, start.second + 1),
    };

    pair<int, int> from = start;
    pair<int, int> pc;

    char tiles[l][w];
    fill(tiles[0], tiles[0] + l * w, 'O');
    tiles[start.first][start.second] = 'S';

    for (int i = 0; i < sn.size(); i++) {
        auto it = pipes.find(sn.at(i));

        if (it != pipes.end()) {
            auto pipe = (*it).second;
            if (pipe.first == start || pipe.second == start) {
                pc = (*it).first;
                break;
            }
        }
    }

    int counter = 0;
    while (pc != start) {
        auto p = pipes.at(pc);
        auto n = p.getNext(from);

        tiles[pc.first][pc.second] = p.type;

        from = pc;
        pc = n;
        counter++;
    }

    int total = 0;

    for (int m = 0; m < l; m++) {
        int crossing = 0;
        int t_line = 0;
        string str;

        for (int n = 0; n < w; n++) {
            str += tiles[m][n];
        }

        str = regex_replace(str, regex("([FS][-]*[JS])"), "|");
        str = regex_replace(str, regex("([LS][-]*[7S])"), "|");
        str = regex_replace(str, regex("([FS][-]*[7S])"), "");
        str = regex_replace(str, regex("([LS][-]*[JS])"), "");

        for (auto ch: str) {
            if (ch == '|') crossing++;
            else if (ch == 'O' && crossing%2 == 1) t_line++;
        }

        if (crossing != 1) total += t_line;
    }

    return total;
}

int main() {
    cout << "Advent of Code 2023 - Day 10" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << getFarthestTile("example.txt") << endl;
    cout << "Result for input: " << getFarthestTile("input.txt") << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << getEnclosedTile("example4.txt") << endl;
    cout << "Result for input: " << getEnclosedTile("input.txt") << endl << endl;
}