#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <unordered_map>
#include <vector>

using namespace std;

struct Vec2{
  long x;
  long y;

public:
  Vec2(long x, long y) {
    this->x = x;
    this->y = y;
  }

  bool operator==(const Vec2 &other) const {
    return x == other.x && y == other.y;
  }
  struct hash_func
  {
    size_t operator()(const Vec2& point) const
    {
      size_t xHash = std::hash<long>()(point.x);
      size_t yHash = std::hash<long>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };

};

Vec2 get_button(string line){
    int x_start = line.find('X');
    long x;
    long y;
    stringstream s(line.substr(x_start + 2));
    s >> x;
    char _c;
    s >> _c;
    while(_c != 'Y'){
      s >> _c;
    }
    s >> _c;
    s >> y;
    return Vec2(x,y);
}
// Memoization cache
unordered_map<Vec2, long, Vec2::hash_func> memo;

//Lets use DFS for this
long get_best(Vec2& a_button, Vec2& b_button, Vec2& prize, Vec2 curr_pos, long total_cost, int a_depth, int b_depth){
  if((curr_pos.x > prize.x || curr_pos.y > prize.y) || a_depth >= 100 || b_depth >= 100) // we have overshot
    return LONG_MAX;
  if(curr_pos.x == prize.x && curr_pos.y == prize.y)
    return total_cost;
// Check memoization
  auto state = curr_pos;
  if (memo.find(state) != memo.end()) {
      return memo[state];
  }

  long a_cost = get_best(a_button, b_button, prize, Vec2(curr_pos.x + a_button.x, curr_pos.y + a_button.y), total_cost + 3, a_depth + 1, b_depth);
  long b_cost = get_best(a_button, b_button, prize, Vec2(curr_pos.x + b_button.x, curr_pos.y + b_button.y), total_cost + 1, a_depth, b_depth + 1);
  memo[state] =  min(a_cost, b_cost);
  return memo[state];
}
int main() {
  string line;
  vector<string> grid;
  long result = 0;
  while(getline(cin, line)){
    // find X and Y
    Vec2 a_button = get_button(line);
    getline(cin, line);
    Vec2 b_button = get_button(line);
    getline(cin, line);
    Vec2 destination = get_button(line);
    getline(cin, line);

    long num_tokens = get_best(a_button,b_button,destination, Vec2(0,0), 0,0,0);
    if(num_tokens < LONG_MAX){
      result += num_tokens;
    }
    memo.clear();
  };

  cout << "result: " << result << endl;
  return 0;
}
