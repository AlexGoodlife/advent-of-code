#include <iostream>
#include <sstream>
#include <string>

int main() {

  std::string line;
  unsigned long result = 0;
  unsigned long total = 0;
  while (std::getline(std::cin, line)) {
    int t;
    int prev;
    std::stringstream s(line);

    bool first_iteration = true;
    bool ascending = false;
    while (s >> t) {
      if(first_iteration){
        prev = t;
        s >> t;
        ascending = (prev - t) > 0;
        first_iteration = false;
      }
      if (std::abs(prev - t)< 1 || std::abs(prev - t) > 3 || (ascending != ((prev - t) > 0))) {
        result++;
        break;
      }
      prev = t;
    }
    total++;
  }
  std::cout << total - result << std::endl;
  return 0;
}
