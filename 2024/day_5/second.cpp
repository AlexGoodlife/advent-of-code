#include <cstdio>
#include <iostream>
#include <sstream>
#include <stack>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <utility>
#include <vector>

bool is_correct(std::vector<int>& update, std::unordered_map<int, std::vector<int>>& orders){
  std::unordered_set<int> already_appeared;

  for(const int& page : update){
    for(const int& requirement : orders[page]){
      if(already_appeared.find(requirement) != already_appeared.end()){
        return false;
      }
    }
    already_appeared.insert(page);
  }
  return true;
}

void swap(int& a, int &b){
  int tmp = a;
  a = b;
  b = tmp;
}

void dfs(int v, std::unordered_set<int> &elements, std::unordered_map<int, std::vector<int>> &orders, std::unordered_set<int>& visited, std::stack<int>& stack){
  visited.insert(v);

  for(const auto& neighbour : orders[v]){
    if(elements.find(neighbour) != elements.end() && visited.find(neighbour) == visited.end()){
      dfs(neighbour, elements, orders, visited,stack);
    }
  }
  stack.push(v);
}

// https://en.wikipedia.org/wiki/Topological_sorting
// Topological sort, go through the vector, dfs through its dependencies and their dependencies, put them on a stack so they are always
// before each other, the stack ends up being perfectly sorted and balanced according to the dependencies
std::vector<int> correct_update(std::vector<int> &update, std::unordered_map<int, std::vector<int>> &orders) {

  std::unordered_set<int> visited;
  std::vector<int> result;
  std::unordered_set<int> elements;
  std::stack<int> stack;
  for(const auto& i : update){
    elements.insert(i);
  }
  for (const auto& i : update) {
    if(visited.find(i) == visited.end()){
      dfs(i,elements,orders,visited,stack);
    }
  }

  while(!stack.empty()){
    result.push_back(stack.top());
    stack.pop();
  }
  return result;
}

int main() {

  std::string line;
  std::unordered_map<int, std::vector<int>> orders;
  std::vector<std::pair<int, int>> pairs;
  while (getline(std::cin, line) && line != "") { // Read all pairings
    int key;
    int value;
    char _t;
    std::stringstream s(line);

    s >> key;
    s >> _t;
    s >> value;
    pairs.push_back(std::make_pair(key, value));
    if (orders.find(key) != orders.end())
      orders[key].push_back(value);
    else
      orders[key] = {value};
  }

  std::vector<std::vector<int>> updates;
  while (getline(std::cin, line)) {
    updates.push_back({});
    std::stringstream s(line);
    char _c;
    int page;
    while (!s.eof()) {
      s >> page;
      s >> _c;
      updates[updates.size() - 1].push_back(page);
    }
  }

  std::vector<std::vector<int> *> incorrect_updates;
  for (auto &update : updates) {
    if (!is_correct(update, orders)) {
      incorrect_updates.push_back(&update);
    }
  }

  int result = 0;
  for (const auto &update : incorrect_updates) {
    std::vector corrected = correct_update(*update, orders);
    result += corrected[corrected.size() / 2];
  }
  std::cout << result << std::endl;

  return 0;
}
