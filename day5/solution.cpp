#include <iostream>
#include <queue>
#include <map>
#include <set>
#include <string>
#include <regex>
#include <algorithm>

bool is_valid_line(std::vector<int> pages, std::map<int, std::set<int>> rule_book)
{
  for (int i = 0; i < pages.size(); i++) {
    if (rule_book.count(pages.at(i)) > 0) {
    std::set<int> before_pages = rule_book.at(pages.at(i));
    for (int j = 0; j < pages.size(); j++) {
      if (j == i) continue;

      if (j < i) {
        if (before_pages.count(pages.at(j)) != 0) {
          return false;
        }
      }

      if (j > i) {
        if (before_pages.count(pages.at(j)) == 0) {
          return false;
        }
      }
    }
    }
  }
  return true;
}

std::vector<int> custom_sort(std::vector<int>& pages, std::map<int, std::set<int>> rule_book)
{
  std::vector<int> sorted_pages;

  for (int i = 0; i < pages.size(); i++) {
    sorted_pages.push_back(pages.at(i));
    int starting_index = sorted_pages.size() - 1;
    while (!is_valid_line(sorted_pages, rule_book)) {
      std::swap(sorted_pages[starting_index], sorted_pages[starting_index - 1]);
      starting_index--;
      if (starting_index <= 0) {
        break;
      }
    }
  }

  return sorted_pages;
}

int main(int argc, char **argv)
{

  std::string input_line;
  std::regex number_regex("\\d+");
  std::map<int, std::set<int>> rule_book;

  while (std::getline(std::cin, input_line)) {
    if (input_line == "") {
      std::cout << "End of rule book encountered" << std::endl;
      break;
    } else {
      auto match_begin = std::sregex_iterator(input_line.begin(), input_line.end(), number_regex);
      auto match_end = std::sregex_iterator();

      for (std::sregex_iterator i = match_begin; i != match_end; i++) {
        int current_key;
        if (i == match_begin) {
          std::smatch match = *i;
          int key = stoi(match.str());
          current_key = key;

          if (!(rule_book[key].size() > 0)) {
            std::set<int> s;
            rule_book.insert_or_assign(key, s);
          }
        } else {
          std::smatch match = *i;
          rule_book[current_key].insert(stoi(match.str()));
        }
      }
    }
  }

  int middle_addition = 0;
  int wrong_middle_addition = 0;
  while (std::getline(std::cin, input_line)) {
    std::vector<int> pages;

    auto numbers_begin = std::sregex_iterator(input_line.begin(), input_line.end(), number_regex);
    auto numbers_end = std::sregex_iterator();

    for (std::sregex_iterator i = numbers_begin; i != numbers_end; i++) {
      std::smatch match = *i;
      pages.push_back(stoi(match.str()));
    }

    if (is_valid_line(pages, rule_book)) {
      int middle_index = pages.size() / 2;
      middle_addition += pages.at(middle_index);
    } else {
      pages = custom_sort(pages, rule_book);
      int middle_index = pages.size() / 2;
      wrong_middle_addition += pages.at(middle_index);
    }
  }

  std::cout << "After adding the middle indexes: " << middle_addition << std::endl;
  std::cout << "After reording the wrong lists: " << wrong_middle_addition << std::endl;

  return 0;
}