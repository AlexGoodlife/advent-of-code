#include <iostream>
#include <regex>
#include <sstream>
#include <string>

int main() {
  std::ostringstream sstr;
  sstr << std::cin.rdbuf();
  std::string contents = sstr.str();
  std::vector<std::string> matches;

  std::regex r("(mul\\(\\d+,\\d+\\))");
  std::regex_token_iterator<std::string::iterator> rend;
  std::regex_token_iterator<std::string::iterator> a(contents.begin(),
                                                     contents.end(), r);
  while (a != rend)
    matches.push_back(*a++);

  long total = 0;
  for (const auto &match : matches) {
    // get the digits

    int first;
    int second;
    char throwaway;

    size_t i = match.find("(");
    std::stringstream s(match.substr(i+1));
    s >> first;
    s >> throwaway;
    s >> second;
    total += first * second;
  }
  std::cout << total << std::endl;
  return 0;
}
