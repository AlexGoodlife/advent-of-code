#include <array>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <sstream>
#include <string>
#include <unordered_map>
#include <vector>

using namespace std;

struct hash_func {
  size_t operator()(const pair<unsigned long, unsigned long> &p) const {
    return hash<unsigned long>()(p.first) ^
           (hash<unsigned long>()(p.second) << 1);
  }
};
const unsigned long num_blinks = 75;

unsigned long calculate_stones(
    unsigned long stone, unsigned long amount,
    unordered_map<pair<unsigned long, unsigned long>, unsigned long, hash_func> &cache) {
  unsigned long result = 0;
  pair<unsigned long, unsigned long> curr = make_pair(stone, amount);

  if (cache.find(curr) != cache.end()) {
    return cache[curr];
  }
  if (amount == 0) {
    cache[curr] = 1;
    return 1;
  }
  string val_str = to_string(stone);
  if (stone == 0) {
    result += calculate_stones(1, amount - 1, cache);
  } else if (val_str.size() % 2 == 0) {
    unsigned long first = stol(val_str.substr(0, val_str.size() / 2));
    unsigned long second = stol(val_str.substr(val_str.size() / 2));

    result += calculate_stones(first, amount - 1, cache);
    result += calculate_stones(second, amount - 1, cache);
  } else {
    result += calculate_stones(stone * 2024, amount - 1, cache);
  }
  cache[curr] = result;
  return result;
}

unsigned long blink_times(
    list<unsigned long> &stones, unsigned long amount,
    unordered_map<pair<unsigned long, unsigned long>, unsigned long, hash_func> &cache) {
  unsigned long result = 0;
  for (const auto &s : stones) {
    result += calculate_stones(s, amount, cache);
  }
  return result;
}

int main() {
  string line;
  list<unsigned long> stones;
  getline(cin, line);
  stringstream s(line);
  while (!s.eof()) {
    unsigned long digit;
    s >> digit;
    stones.push_back(digit);
  }
  unordered_map<pair<unsigned long, unsigned long>, unsigned long, hash_func> cache;
  cout << blink_times(stones, num_blinks, cache) << endl;
  return 0;
}
