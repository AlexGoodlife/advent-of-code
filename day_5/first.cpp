#include <cstdio>
#include <iostream>
#include <sstream>
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


int main() {

  std::string line;
  std::unordered_map<int, std::vector<int>> orders;
  std::vector<std::pair<int,int>> pairs;
  while (getline(std::cin, line) && line != "") { // Read all pairings
    int key;
    int value;
    char _t;
    std::stringstream s(line);

    s >> key;
    s >> _t;
    s >> value;
    pairs.push_back(std::make_pair(key, value));
    if(orders.find(key) != orders.end())
      orders[key].push_back(value);
    else
      orders[key] = {value};
  }

  std::vector<std::vector<int>> updates;
  while(getline(std::cin, line)){
    updates.push_back({});
    std::stringstream s(line);
    char _c;
    int page;
    while(!s.eof()) {
      s >> page;
      s >> _c;
      updates[updates.size()-1].push_back(page);
    }
  }

  std::vector<std::vector<int>*> correct_updates;
  for(auto& update : updates){
    if(is_correct(update, orders)){
        correct_updates.push_back(&update);
      }
  }
  std::cout << correct_updates.size() << std::endl;

  int result = 0;
  for(const auto& update : correct_updates){
    result += (*update)[update->size()/2];
  }
  std::cout << result << std::endl;
  return 0;
}
