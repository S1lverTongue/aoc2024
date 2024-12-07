#include <iostream>
#include <string>
#include <vector>
#include <tuple>
#include <map>

enum traversal_direction {
  N,
  NE,
  E,
  SE,
  S,
  SW,
  W,
  NW
};

std::tuple<int, int> x_y_from_direction(traversal_direction td) {
  std::tuple<int,int> coords(0,0);

  switch (td)
  {
  case N:
    coords = std::make_tuple(0,-1);  
    break;
  case NE:
    coords = std::make_tuple(1,-1);
    break;
  case E:
    coords = std::make_tuple(1,0);
    break;
  case SE:
    coords = std::make_tuple(1,1);
    break;
  case S:
    coords = std::make_tuple(0,1);
    break;
  case SW:
    coords = std::make_tuple(-1,1);
    break;
  case W:
    coords = std::make_tuple(-1,0);
    break;
  case NW:
    coords = std::make_tuple(-1,-1);
    break;
  default:
    break;
  }

  return coords;
}

int travel_in_direction_to_search_for_string(
  std::map<std::tuple<int, int>, char>& character_map,
  std::tuple<int, int>& current_location,
  traversal_direction direction_to_look,
  std::string& string_to_search_for,
  int x_max, int x_min, int y_max, int y_min
) {
  int current_x = std::get<0>(current_location);
  int current_y = std::get<1>(current_location);

  if (current_x < x_min || current_x > x_max || current_y < y_min || current_y > y_max) {
    return 0;
  }

  std::tuple<int, int> traveling_direction = x_y_from_direction(direction_to_look);

  if (string_to_search_for.size() == 1 && character_map[current_location] == string_to_search_for.at(0)) {
    return 1;
  } else if (character_map[current_location] == string_to_search_for.at(0)) {
    int next_x = current_x + std::get<0>(traveling_direction);
    int next_y = current_y + std::get<1>(traveling_direction);

    std::tuple<int, int> next_location = std::make_tuple(next_x, next_y);
    std::string next_to_search_for = string_to_search_for.substr(1, string_to_search_for.size() - 1);
    return travel_in_direction_to_search_for_string(character_map, next_location, direction_to_look, next_to_search_for, x_max, x_min, y_max, y_min);
  }

  return 0;
}

int check_for_string(
  std::map<std::tuple<int, int>, char>& character_map,
  std::tuple<int, int>& current_location,
  std::string& searching_for,
  int x_max, int x_min, int y_max, int y_min)
{
  int correct_strings = 0;

  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, N, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, NE, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, E, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, SE, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, S, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, SW, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, W, searching_for, x_max, x_min, y_max, y_min);
  correct_strings += travel_in_direction_to_search_for_string(character_map, current_location, NW, searching_for, x_max, x_min, y_max, y_min);

  return correct_strings;
}

int check_for_string_part_2(
  std::map<std::tuple<int, int>, char>& character_map,
  std::tuple<int, int>& current_location,
  std::string& searching_for,
  int x_max, int x_min, int y_max, int y_min
) {
  int correct_strings = 0;

  std::string am = searching_for + "M";
  std::string as = searching_for + "S";

  if (travel_in_direction_to_search_for_string(character_map, current_location, NE, as, x_max, x_min, y_max, y_min) && travel_in_direction_to_search_for_string(character_map, current_location, SW, am, x_max, x_min, y_max, y_min)) {
    correct_strings += 1;
  }

  if (travel_in_direction_to_search_for_string(character_map, current_location, NE, am, x_max, x_min, y_max, y_min) && travel_in_direction_to_search_for_string(character_map, current_location, SW, as, x_max, x_min, y_max, y_min)) {
    correct_strings += 1;
  }

  if (travel_in_direction_to_search_for_string(character_map, current_location, SE, am, x_max, x_min, y_max, y_min) && travel_in_direction_to_search_for_string(character_map, current_location, NW, as, x_max, x_min, y_max, y_min)) {
    correct_strings += 1;
  }

  if (travel_in_direction_to_search_for_string(character_map, current_location, SE, as, x_max, x_min, y_max, y_min) && travel_in_direction_to_search_for_string(character_map, current_location, NW, am, x_max, x_min, y_max, y_min)) {
    correct_strings += 1;
  }

  if (correct_strings < 2) {
    correct_strings = 0;
  } else {
    correct_strings = 1;
  }

  return correct_strings;
}

int traverse_map_for_string(
  std::map<std::tuple<int, int>, char>& character_map,
  std::string& to_search_for,
  int x_max, int x_min, int y_max, int y_min)
{
  int correct_strings = 0;

  for (auto pr : character_map) {
    if (pr.second == to_search_for.at(0)) {
      std::tuple<int, int> location = pr.first;
      correct_strings += check_for_string(character_map, location, to_search_for, x_max, x_min, y_max, y_min);
    }
  }

  return correct_strings;
}

int traverse_map_for_string_part_2(
  std::map<std::tuple<int, int>, char>& character_map,
  std::string& to_search_for,
  int x_max, int x_min, int y_max, int y_min)
{
  int correct_strings = 0;
  for (auto pr : character_map) {
    if (pr.second == to_search_for.at(0)) {
      std::tuple<int, int> location = pr.first;
      correct_strings += check_for_string_part_2(character_map, location, to_search_for, x_max, x_min, y_max, y_min);
    }
  }

  return correct_strings;
}

int main(int argc, char** argv)
{
  std::string line;
  std::vector<std::string> input_lines;

  while (std::getline(std::cin, line)) {
    input_lines.push_back(line);
  }

  int x_min_limit = 0;
  int x_max_limit = input_lines.at(0).size() - 1;

  int y_min_limit = 0;
  int y_max_limit = input_lines.size() - 1;

  std::map<std::tuple<int, int>, char> character_map;

  for (int y = 0; y < input_lines.size(); y++) {
    for (int x = 0; x < input_lines.at(y).size(); x++) {
      std::tuple<int, int> coords(x, y);
      character_map[coords] = input_lines.at(y).at(x);
    }
  }

  std::string searching_for("XMAS");
  int correct_strings = traverse_map_for_string(character_map, searching_for, x_max_limit, x_min_limit, y_max_limit, y_min_limit);

  std::cout << "We found " << correct_strings << " correct strings in the map." << std::endl;

  searching_for = "A";
  correct_strings = traverse_map_for_string_part_2(character_map, searching_for, x_max_limit, x_min_limit, y_max_limit, y_min_limit);
  std::cout << "For part 2 we found " << correct_strings << " correct strings in the map." << std::endl;

  return 0;
}