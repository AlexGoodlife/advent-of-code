#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
  std::ostringstream sstr;
  sstr << std::cin.rdbuf();
  std::string contents = sstr.str();

  std::regex r("do\\(\\)|don\\'t\\(\\)");
  std::sregex_iterator iterator{contents.begin(), contents.end(), r};
  std::sregex_iterator end;

  std::vector<std::tuple<int, int>> ranges;
  int start_range = -4;
  int end_range = 0;
  bool accumulating = true;
  while (iterator != end) {
    auto match = *iterator;
    if (match.str() == "do()") {
      if (!accumulating){
        start_range = match.position();
        accumulating = true;
      }
    } else {
      if(accumulating){
        end_range = match.position();
        ranges.push_back(std::make_tuple(start_range + 4, std::max(0,end_range-1)));
        accumulating = false;
      }
    }
    ++iterator;
  }
  if (accumulating) {
    ranges.push_back(std::make_tuple(start_range + 4, contents.size() - 1));
  }

  std::regex e("mul\\(\\d+,\\d+\\)");
  long total = 0;
  std::vector<std::smatch> matches;
  std::sregex_iterator iterator_2{contents.begin(), contents.end(), e};
  while (iterator_2 != end) {
    matches.push_back(*iterator_2++);
  }
  for (const auto &match : matches) {
    // get the digits

    int first;
    int second;
    char throwaway;

    for (const auto &[start, finish] : ranges) {
      if (match.position() >= start && match.position() < finish) {
        std::string matchs = match.str();
        size_t i = matchs.find("(");
        std::stringstream s(matchs.substr(i + 1));
        s >> first;
        s >> throwaway;
        s >> second;
        total += first * second;
        break;
      }
    }
  }
  std::cout << total << std::endl;
  return 0;
}
