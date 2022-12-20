#include <iostream>
#include <fstream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
#include <regex>
#include "../custom_functions/custom_functions.h"

using namespace std;

map<string, pair<int, vector<string>>> data_map;
map<string, map<string, int>> paths;
set<string> valves_to_open;

void check_neighbors(string next_pos, map<string, int>& visited, vector<string>& todo) {
  for (string n : data_map[next_pos].second) {
    if (visited.count(n) == 0 && find(todo.begin(), todo.end(), n) == todo.end()) {
      visited[n] = visited[next_pos] + 1;
      todo.push_back(n);
    }
  }
}

map<string, int> pathfinding(string start_pos) {
  map<string, int> visited;
  vector<string> todo = {start_pos};
  visited[start_pos] = 0;

  while (!todo.empty()) {
    check_neighbors(todo.front(), visited, todo);
    todo.erase(todo.begin());
  }

  visited[start_pos] = 1;
  return visited;
}

int next_valve(string current_pos, int remaining_time, set<string> open_valves) {
  if (remaining_time <= 0) {
    return 0;
  }

  vector<int> rets;
  // Open valve if possible and if it has not already been opened
  if (remaining_time >= 1 && data_map[current_pos].first > 0 && open_valves.count(current_pos) == 0) {
    set<string> new_open_valves = open_valves;
    new_open_valves.insert(current_pos);
    rets.push_back((remaining_time - 1) * data_map[current_pos].first + next_valve(current_pos, remaining_time - 1, new_open_valves));
  } else {
    // Move to all valves that are not yet open
    for (string n : valves_to_open) {
      if (open_valves.count(n) == 0) {
        rets.push_back(next_valve(n, remaining_time - paths[current_pos][n], open_valves));
      }
    }
  }
  rets.push_back(0);
  return *max_element(rets.begin(), rets.end());
}

int main() {
  // Parse input data
  string line;
  ifstream file("aoc16.txt");
  regex pattern("Valve (\\w+) has flow rate=(\\d+); tunnel[s]? lead[s]? to valve[s]? (.*)");
  smatch matches;
  while (getline(file, line)) {
    if (regex_search(line, matches, pattern)) {
      string valve = matches[1];
      cout << valve << endl;
      int flow_rate = stoi(matches[2]);
      cout << flow_rate << endl;
      vector<string> neighbors;
      string neighbor;
      for (string neighbor : split(matches[3], ", ")) {
        cout << neighbor << endl;
        neighbors.push_back(neighbor);
      }
      cout << endl;
      data_map[valve] = make_pair(flow_rate, neighbors);
    }
  }
  file.close();

  // Compute paths between all valves
  for (auto& [valve, _] : data_map) {
    paths[valve] = pathfinding(valve);
  }

  // Find valves that have a non-zero flow rate
  for (auto& [valve, pair] : data_map) {
    if (pair.first > 0) {
      valves_to_open.insert(valve);
    }
  }

  // Find maximum flow rate starting at valve "AA"
  int result = next_valve("AA", 30, set<string>());
  cout << result << endl;

  return 0;
}
