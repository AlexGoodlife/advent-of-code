#include <iostream>
#include <unordered_map>
#include <vector>
#include <algorithm>

int main(){
  std::vector<int> left;
  std::vector<int> right;

  int first;
  int second;
  while( std::cin >> first){
    std::cin >> second;
    left.push_back(first);
    right.push_back(second);
  }

  std::unordered_map<int, int> counts;
  for(const auto& x : left){
    counts[x] = 0;
  }

  for(const auto& x : right){
    if(counts.find(x) != counts.end()){
      counts[x]++;
    }
  }

  unsigned long result = 0;
  for(const auto& x : left){
    int value = counts[x];
    // std::cout << x << '*' << value << '\n';
    result += x * value;
  }

  std::cout << result << std::endl;

  return 0;

}
