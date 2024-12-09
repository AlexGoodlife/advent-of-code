#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

int main(){
  std::vector<int> left;
  std::vector<int> right;

  int first;
  int second;
  while( std::cin >> first){
    std::cin >> second;
    // std::cout << first;
    // std::cout << second;
    left.push_back(first);
    right.push_back(second);
  }
  std::sort(left.begin(), left.end());
  std::sort(right.begin(), right.end());

  unsigned long distance = 0;
  for (unsigned long i = 0; i < std::min(left.size(), right.size()); i++){
    distance += abs(left[i] - right[i]);
  }

  std::cout << distance << std::endl;

  return 0;

}
