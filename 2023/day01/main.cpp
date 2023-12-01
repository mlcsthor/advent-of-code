#include <fstream>
#include <iostream>
#include <string>
#include <regex>

using namespace std;

char const* DIGITS = "123456789";
vector<string> const DIGITS_SPELLED = { "zero", "one", "two", "three", "four", "five", "six", "seven", "eight", "nine" };

int calculateCalibrationValue(string line) {
    size_t firstDigit = line.find_first_of(DIGITS);
    size_t lastDigit = line.find_last_of(DIGITS);

    string v;
    v.push_back(line.at(firstDigit));
    v.push_back(line.at(lastDigit));

    return stoi(v);
}

int calculateCalibrationSum(string fileName) {
  string line;
  ifstream File(fileName);
  int sum = 0;

  while (getline(File, line)) {
    sum += calculateCalibrationValue(line);
  }

  File.close();
  return sum;
}

int calculateCalibrationSumWithSpelled(string fileName) {
  string line;
  ifstream File(fileName);
  int sum = 0;

  while (getline(File, line)) {
    for (int i = 0; i < DIGITS_SPELLED.size(); i += 1) {
      line = regex_replace(line, regex(DIGITS_SPELLED[i]), DIGITS_SPELLED[i] + to_string(i) + DIGITS_SPELLED[i]);
    }

    sum += calculateCalibrationValue(line);
  }

  File.close();

  return sum;
}

int main()
{
  cout << "Advent of Code 2023 - Day 1" << endl << endl;

  cout << "Part 1" << endl;
  cout << "Result for example: " << calculateCalibrationSum("example.txt") << endl;
  cout << "Result for input: " << calculateCalibrationSum("input.txt") << endl << endl;

  cout << "Part 2" << endl;
  cout << "Result for example: " << calculateCalibrationSumWithSpelled("example2.txt") << endl;
  cout << "Result for input: " << calculateCalibrationSumWithSpelled("input.txt") << endl;
}