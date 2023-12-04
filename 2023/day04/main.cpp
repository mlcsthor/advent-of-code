#include <iostream>
#include <fstream>
#include <regex>
#include <numeric>
using namespace std;

int calculatePoints(string fileName) {
    string line;
    ifstream File(fileName);
    int points = 0;

    while (getline(File, line)) {
        size_t begin = line.find(':');
        size_t delimiter = line.find('|');

        regex digit_regex("([[:digit:]]+)"); 
        auto it = sregex_iterator(
            line.begin() + begin, 
            line.end(), 
            digit_regex
        );    
        auto end = sregex_iterator();

        vector<string> winning = {};
        vector<string> numbers = {};

        for (auto k = it; k != end; ++k) { 
            smatch match = *k; 

            if (match.position() + begin < delimiter) {
                winning.push_back(match.str());
            } else {
                numbers.push_back(match.str());
            }

        }  

        sort(winning.begin(), winning.end());
        sort(numbers.begin(), numbers.end());

        vector<string> intersection(winning.size() + numbers.size());
        auto it_int = set_intersection(
            winning.begin(), 
            winning.end(), 
            numbers.begin(), 
            numbers.end(), 
            intersection.begin()
        );

        intersection.resize(it_int - intersection.begin());

        if (intersection.size() == 0) continue;

        points += pow(2, intersection.size() - 1);
    }

    File.close();

    return points;
}

int calculateInstances(string fileName) {
    string line;
    ifstream File(fileName);
    int l = 0;
    vector<int> instances = {0};

    while (getline(File, line)) {
        size_t begin = line.find(':');
        size_t delimiter = line.find('|');

        regex digit_regex("([[:digit:]]+)"); 
        auto it = sregex_iterator(
            line.begin() + begin, 
            line.end(), 
            digit_regex
        );    
        auto end = sregex_iterator();

        vector<string> winning = {};
        vector<string> numbers = {};

        for (auto k = it; k != end; ++k) { 
            smatch match = *k; 
            if (match.position() + begin < delimiter) {
                winning.push_back(match.str());
            } else {
                numbers.push_back(match.str());
            }
        }  

        sort(winning.begin(), winning.end());
        sort(numbers.begin(), numbers.end());

        vector<string> intersection(winning.size() + numbers.size());
        auto it_int = set_intersection(
            winning.begin(), 
            winning.end(), 
            numbers.begin(), 
            numbers.end(), 
            intersection.begin()
        );

        intersection.resize(it_int - intersection.begin());
        
        instances.resize(instances.size() + 1);
        instances.at(l) += 1;

        for (auto i = l; i < l + intersection.size(); i++) {
            instances.resize(instances.size() + 1);
            instances.at(i + 1) += instances.at(l);
        }

        l++;
    }

    File.close();

    return accumulate(instances.begin(), instances.end(), 0);
}

int main() {
    cout << "Advent of Code 2023 - Day 4" << endl << endl;

    cout << "Part 1" << endl;
    cout << "Result for example: " << calculatePoints("example.txt") << endl;
    cout << "Result for input: " << calculatePoints("input.txt") << endl << endl;

    cout << "Part 2" << endl;
    cout << "Result for example: " << calculateInstances("example.txt") << endl;
    cout << "Result for input: " << calculateInstances("input.txt") << endl;
}