#include <iostream>
#include <queue>
#include <map>
#include <string>

using namespace std;

int main(int argc, char* argv[])
{
  priority_queue<int> left_q;
  priority_queue<int> right_q;
  map<int, int> similarity_map;
  string current_line;

  int first_num, second_num;

  while (getline(cin, current_line)) {
    int first_space = current_line.find_first_of(' ');
    int last_space = current_line.find_last_of(' ');

    first_num = atoi(current_line.substr(0, first_space).c_str());
    second_num = atoi(current_line.substr(last_space, current_line.size()).c_str());

    left_q.push(first_num);
    right_q.push(second_num);

    if (similarity_map[second_num] > 0) {
      similarity_map[second_num] = similarity_map[second_num] + 1;
    } else {
      similarity_map.insert_or_assign(second_num, 1);
    }
  }

  int sum_distances = 0;
  int similarity_score = 0;

  while (!left_q.empty()) {
    int num = left_q.top();
    int num2 = right_q.top();

    if (similarity_map[num] > 0) {
      similarity_score += (num * similarity_map.at(num));
    }

    sum_distances += abs(num - num2);

    left_q.pop();
    right_q.pop();
  }

  cout << "Sum Distances: " << sum_distances << endl;
  cout << "Similarity Score: " << similarity_score << endl;
  
  return 0;
}