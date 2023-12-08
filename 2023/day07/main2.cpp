#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
#include <numeric>
using namespace std;

const string Cards = "J23456789TQKA";
const int HandsLength = 5;

enum Type { High, OnePair, TwoPair, Three, Full, Four, Five };

struct Hand {
    array<int, 5> cards{};
    string draw;
    int bid{};
    Type type{};
    
    Type getType() {
        array<int, 13> count{};
        int joker = 0;

        for (auto card: cards)
            if (card == Cards.find('J')) ++joker;
            else count[card] += 1;

        sort(count.begin(), count.end(), greater());

        count[0] += joker;

        switch(count[0]) {
            case 1:
                return High;
            case 2:
                return count[1] == 2 ? TwoPair : OnePair;
            case 3:
                return count[1] == 2 ? Full : Three;
            case 4:
                return Four;
            case 5:
                return Five;
            default:
                throw;
        }
    }

    Hand(const string &draw, const int bid): draw(draw), bid(bid) {
        for (int i = 0; i < HandsLength; i++) {
            cards[i] = Cards.find(draw.at(i));
        }

        type = getType();
    }

    auto operator<=>(const Hand &other) const {
        return pair(type, cards) <=> pair(other.type, other.cards);
    }
};

int calculateTotalWinnings(string fileName) {
    string line;
    ifstream File(fileName);

    vector<Hand> hands = {};

    while(getline(File, line)) {
        smatch sm;
        if (regex_search(line.cbegin(), line.cend(), sm, regex("([AKQJT2-9]{5}) ([0-9]+)"))) {
            Hand hand(sm[1], stoi(sm[2]));
            hands.push_back(hand);  
        };
    }

    File.close();

    sort(hands.begin(), hands.end());

    int count = 0;
    return accumulate(hands.begin(), hands.end(), 0, [count](int a, Hand b) mutable { return a + (++count)*b.bid; });
}

int main() {
    cout << "Advent of Code 2023 - Day 7" << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calculateTotalWinnings("example.txt") << endl;
    cout << "Result for input: " << calculateTotalWinnings("input.txt") << endl << endl;
}