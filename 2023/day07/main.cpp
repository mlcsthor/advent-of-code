#include <iostream>
#include <fstream>
#include <regex>
#include <algorithm>
using namespace std;

const string Cards = "AKQJT98765432";
const int HandsLength = 5;

class Hand {
    public:
        int bid;
        string cards;
        int primaryType;
        int secondaryType;

        Hand(string c, int b) {
            bid = b;
            cards = c;

            int maxCard = 0;
            int secondMaxCard = 0;
            for (char card: Cards) {
                int nbCard = count_if(cards.begin(), cards.end(), [card](char c){ return c == card; });

                if (nbCard > maxCard) {
                    secondMaxCard = max(maxCard, secondMaxCard);
                    maxCard = nbCard;
                } else {
                    secondMaxCard = max(nbCard, secondMaxCard);
                }
            }

            primaryType = maxCard;
            secondaryType = secondMaxCard;
        }

        bool operator< (const Hand &h) const {
            if (primaryType != h.primaryType)
                return primaryType < h.primaryType;

            if (secondaryType != h.secondaryType)
                return secondaryType < h.secondaryType;

            for (int i = 0; i < HandsLength; i++) {
                auto idx = Cards.find(cards.at(i));
                auto otherIdx = Cards.find(h.cards.at(i));
                if (idx == otherIdx) continue;
                
                return idx > otherIdx;
            }
            
            return false;
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

    int sum = 0;
    for (int i = 0; i < hands.size(); i++) {
        sum += (i+1) * hands.at(i).bid;
    }

    return sum;
}

int main() {
    cout << "Advent of Code 2023 - Day 7" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculateTotalWinnings("example.txt") << endl;
    cout << "Result for input: " << calculateTotalWinnings("input.txt") << endl << endl;
}