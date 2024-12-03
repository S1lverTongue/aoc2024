#include <iostream>
#include <string>
#include <vector>

using namespace std;

string space = " ";

vector<int> split_line(string& s, string& delimiter)
{
  vector<int> split_nums;

  while (s.find(delimiter)) {
    string token = s.substr(0, s.find(delimiter) + delimiter.size());
    split_nums.push_back(stoi(token));
    s.erase(0, s.find(delimiter) + delimiter.size());
    if (s.find(delimiter) == string::npos) {
      split_nums.push_back(stoi(s));
      break;
    }
  }

  return split_nums;

}

bool is_increasing(vector<int> numbers)
{
  if (numbers.size() == 1 || numbers.size() == 0) return true;

  for (int i = 1; i < numbers.size(); i++) {
    if (numbers.at(i - 1) <= numbers.at(i)) {
      return false;
    } else {
      int difference = abs(numbers.at(i-1) - numbers.at(i));
      if (!(difference >= 1 && difference <= 3)) {
        return false;
      }
    }
  }

  return true;
}

bool is_decreasing(vector<int> numbers)
{
  if (numbers.size() == 1 || numbers.size() == 0) return true;

  for (int i = 1; i < numbers.size(); i++) {
    if (numbers.at(i - 1) >= numbers.at(i)) {
      return false;
    } else {
      int difference = abs(numbers.at(i-1) - numbers.at(i));
      if (!(difference >= 1 && difference <= 3)) {
        return false;
      }
    }
  }

  return true;
}

bool good_after_dampening(vector<int> numbers)
{
  for (int i = 0; i < numbers.size(); i++) {
    vector<int> copy = numbers;
    copy.erase(copy.begin() + i, copy.begin() + i + 1);

    if (is_decreasing(copy) || is_increasing(copy)) {
      return true;
    }
  }

  return false;
}

int main(int argc, char** argv)
{
  string current_line;
  int original_safe_count = 0;
  int after_dampening_count = 0;

  while (getline(cin, current_line)) {
    vector<int> split_nums = split_line(current_line, space);

    if (split_nums.size() == 1 || split_nums.size() == 0) {
      original_safe_count++;
      continue;
    }

    if (is_decreasing(split_nums) || is_increasing(split_nums)) {
      original_safe_count++;
      continue;
    }

    if (good_after_dampening(split_nums)) {
      after_dampening_count++;
    }
  }

  cout << "How many safe? " << original_safe_count << endl;
  cout << "After dampening? " << (original_safe_count + after_dampening_count) << endl;

  return 0;
}