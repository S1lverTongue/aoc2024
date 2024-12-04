#include <iostream>
#include <iterator>
#include <regex>
#include <string>
#include <vector>

int multiply_between_parentheses(std::string regex_match)
{
  std::regex number_regex("\\d+");

  auto words_begin = std::sregex_iterator(regex_match.begin(), regex_match.end(), number_regex);
  auto words_end = std::sregex_iterator();

  int x = 1;
  for (std::sregex_iterator i = words_begin; i != words_end; i++) {
    std::smatch match = *i;
    x *= stoi(match.str());
  }

  return x;
}

int main(int argc, char** argv)
{
  std::regex word_regex("mul\\(\\d+,\\d+\\)");
  std::regex dont_regex("don\'t\\(\\)");
  std::regex do_regex("do\\(\\)");

  std::vector<std::string> lines;

  std::string input;
  int x = 0;

  while(std::getline(std::cin, input)) {
    lines.push_back(input);
  }

  for (int index = 0; index < lines.size(); index++) {
  auto words_begin = std::sregex_iterator(lines.at(index).begin(), lines.at(index).end(), word_regex);
  auto words_end = std::sregex_iterator();

  for (std::sregex_iterator i = words_begin; i != words_end; i++)
  {
    std::smatch match = *i;
    x += multiply_between_parentheses(match.str());
  }
  }

  std::cout << "We have " << x << " from the multiplications." << std::endl;

  bool enabled = true;
  std::smatch dont_match;
  std::smatch do_match;
  x = 0;
  for (int index = 0; index < lines.size(); index++) {
    std::string current_line = lines.at(index);
    
    auto words_begin = std::sregex_iterator(current_line.begin(), current_line.end(), word_regex);
    auto words_end = std::sregex_iterator();

    int starting_substring = 0;
    for (std::sregex_iterator i = words_begin; i != words_end; i++) {
      if (enabled) {
        if (std::regex_search(current_line.substr(starting_substring, (*i).position() - starting_substring), dont_regex)) {
          enabled = false;
        }
      }

      if (!enabled) {
        if (std::regex_search(current_line.substr(starting_substring, (*i).position() - starting_substring), do_regex)) {
          enabled = true;
        }
      }

      starting_substring = (*i).position() + (*i).str().size();

      if (enabled) {
        std::smatch match = *i;
        x += multiply_between_parentheses(match.str());
      }
    }
  }

  std::cout << "We have enabled " << x << " from the multiplications." << std::endl;

  return 0;
}