#include <iostream>
#include <fstream>
#include <string>
#include <regex>
using namespace std;

// Part 1
bool checkColor(string sets, string color, int number) {
  smatch sm;
  string::const_iterator searchStart(sets.cbegin());
  while (regex_search(searchStart, sets.cend(), sm, regex("([[:digit:]]{1,2}) " + color)))
  {
    if (stoi(sm[1]) > number) 
      return false;
    searchStart = sm.suffix().first;
  }

  return true;
}

bool checkSets(string sets, int red, int green, int blue) {
  return checkColor(sets, "red", red) && 
    checkColor(sets, "green", green) && 
    checkColor(sets, "blue", blue);
}

int calculateSumOfPossible(string fileName) {
  string line;
  ifstream File(fileName);
  int sum = 0;
  int game = 1;

  while (getline(File, line)) {
    string sets = line.substr(line.find(':') + 2, line.length());

    if (checkSets(sets, 12, 13, 14))
      sum += game;

    game++;
  }

  File.close();

  return sum;
}

// Part 2
int getMaxForColor(string sets, string color) {
  int maxNb = 0;

  smatch sm;
  string::const_iterator searchStart(sets.cbegin());
  while (regex_search(searchStart, sets.cend(), sm, regex("([[:digit:]]{1,2}) " + color)))
  {
    maxNb = max(maxNb, stoi(sm[1])); 
    searchStart = sm.suffix().first;
  }

  return maxNb;
}

int getPowerOfSets(string sets) {
  return getMaxForColor(sets, "red") * getMaxForColor(sets, "green") * getMaxForColor(sets, "blue");
}

int calculateSumOfPower(string fileName) {
  string line;
  ifstream File(fileName);
  int sum = 0;

  while (getline(File, line)) {
    string sets = line.substr(line.find(':') + 2, line.length());

    sum += getPowerOfSets(sets);
  }

  File.close();

  return sum; 
}

int main()
{
  cout << "Advent of Code 2023 - Day 1" << endl << endl;

  cout << "Part 1" << endl;
  cout << "Result for example: " << calculateSumOfPossible("example.txt") << endl;
  cout << "Result for input: " << calculateSumOfPossible("input.txt") << endl << endl;

  cout << "Part 2" << endl;
  cout << "Result for example: " << calculateSumOfPower("example.txt") << endl;
  cout << "Result for input: " << calculateSumOfPower("input.txt") << endl;
}