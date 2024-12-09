#include <cassert>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>

void copy_vecs(std::vector<int>& a, std::vector<int>& b){
  for(const auto& i : a){
    b.push_back(i);
  }
}
bool is_fault(std::vector<int> &a, int start_depth) {
  int prev = a[0];
  int current = a[1];
  bool ascending = (prev - current) > 0;
  for (int i = 1; i < a.size(); i++) {
    current = a[i];
    if (std::abs(prev - current) < 1 || std::abs(prev - current) > 3 ||
        (ascending != ((prev - current) > 0))) {
      if (start_depth < 1) {
        // remove prev and remove current and search through
        std::vector<int> a_1 = a;
        a_1.erase(a_1.begin() + i);
        std::vector<int> a_2 = a;
        a_2.erase(a_2.begin() + (i - 1));
        if ((i - 2) >= 0) {
          std::vector<int> a_3 = a;
          a_3.erase(a_3.begin() + (i - 2));
          return is_fault(a_1, start_depth + 1) &&
                 is_fault(a_2, start_depth + 1) &&
                 is_fault(a_3, start_depth + 1);
        }

        return is_fault(a_1, start_depth + 1) && is_fault(a_2, start_depth + 1);
      }
      return true;
    }
    prev = current;
  }
  return false;
}

void test_fault() {
  std::vector<int> a = {7, 6, 4, 2, 1};
  assert(!is_fault(a, 0));
  assert(!is_fault(a, 1));

  a = {1, 2, 7, 8, 9};
  assert(is_fault(a, 0));
  assert(is_fault(a, 1));

  a = {9, 7, 6, 2, 1};
  assert(is_fault(a, 0));
  assert(is_fault(a, 1));

  a = {1, 3, 2, 4, 5};
  assert(is_fault(a, 1));
  assert(!is_fault(a, 0));

  a = {8, 6, 4, 4, 1};
  assert(is_fault(a, 1));
  assert(!is_fault(a, 0));

  a = {1, 3, 6, 7, 9};
  assert(!is_fault(a, 0));
  assert(!is_fault(a, 1));
}

void test_fault_edge() {
  std::vector<int> a = {1, 4, 3, 2, 1};
  assert(is_fault(a, 1));
  assert(!is_fault(a, 0));

  a = {1, 2, 3, 4, 25};
  assert(is_fault(a, 1));
  assert(!is_fault(a, 0));
}

int main(int argc, const char **argv) {
  if (argc > 1) {
    std::string first(argv[1]);
    if (first == "test") {
      std::cout << "Testing example_input..." << std::endl;
      test_fault();
      std::cout << "Passed" << std::endl;
      std::cout << "Testing edge..." << std::endl;
      test_fault_edge();
      std::cout << "Passed" << std::endl;
    }
    return 0;
  }
  std::string line;
  unsigned long result = 0;
  unsigned long total = 0;
  while (std::getline(std::cin, line)) {
    int t;
    std::stringstream s(line);
    std::vector<int> vec;
    while (s >> t) {
      vec.push_back(t);
    }
    result = is_fault(vec, 0) ? result + 1 : result;
    total++;
  }
  std::cout << total - result << std::endl;
  return 0;
}
