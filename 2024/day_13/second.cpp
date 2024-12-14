#include <cassert>
#include <climits>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <vector>

using namespace std;

struct Vec2{
  unsigned long x;
  unsigned long y;

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

  struct tuple_hash_func
  {
    size_t operator()(const std::tuple<Vec2,int,int>& point) const
    {
      Vec2::hash_func f;
      return f(get<0>(point)) ^ std::hash<int>()(get<1>(point)) ^ std::hash<int>()(get<2>(point));
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
long get_best(Vec2 &a_button, Vec2 &b_button, Vec2 &prize) {
  // a_button * x + b_button* y = prize
  // a_x*A + B*b_x = prize_x
  // a_y*A + B*b_y = prize_b
  // Using cramers rule this is easy
  long determinant = a_button.x *b_button.y - a_button.y * b_button.x;
  if(determinant == 0){
    return -1;
  }
  long dx = prize.x * b_button.y - prize.y * b_button.x;
  long dy = prize.y * a_button.x - prize.x * a_button.y;
  long a = dx/determinant;
  long b = dy/determinant;
  if(a*a_button.x + b*b_button.x == prize.x && a*a_button.y + b*b_button.y == prize.y){
    return (dx/determinant) * 3 + (dy/determinant);
  }
  else{
    return -1;
  }
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

    destination.x += 10000000000000;
    destination.y += 10000000000000;
    long num_tokens = get_best(a_button,b_button,destination);
    if(num_tokens > -1){
      result += num_tokens;
    }
    cout << num_tokens << "\n";
  };

  cout << "result: " << result << endl;
  return 0;
}
