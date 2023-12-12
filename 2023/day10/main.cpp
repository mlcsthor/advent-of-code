#include <iostream>
#include <fstream>
#include <map>
using namespace std;

struct Pipe {
    pair<int, int> first;
    pair<int, int> second;

    Pipe(const int &x1, const int &y1, const int &x2, const int &y2) {
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
            
            Pipe p(n1.first, n1.second, n2.first, n2.second);
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
            pc = (*it).first;
            break;
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

int main() {
    cout << "Advent of Code 2023 - Day 10" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << getFarthestTile("example.txt") << endl;
    cout << "Result for input: " << getFarthestTile("input.txt") << endl << endl;
}