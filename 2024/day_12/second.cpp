#include <algorithm>
#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <set>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <array>

using namespace std;

struct Vec2{
  double x;
  double y;

public:
  Vec2(double x, double y) {
    this->x = x;
    this->y = y;
  }

  bool operator==(const Vec2 &other) const {
    return x == other.x && y == other.y;
  }

  bool operator<(const Vec2 &other) const {
    if (y != other.y) {
      return y < other.y;
    }
    return x < other.x;
  }

  struct hash_func
  {
    size_t operator()(const Vec2& point) const
    {
      size_t xHash = std::hash<double>()(point.x);
      size_t yHash = std::hash<double>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };

  struct pair_hash_func
  {
    size_t operator()(const std::pair<Vec2,Vec2>& point) const
    {
      Vec2::hash_func f;
      return f(point.first) ^ f(point.second);
    }
  };
};

std::array<struct Vec2, 4> directions = {Vec2(1,0), Vec2(0,1), Vec2(-1,0), Vec2(0,-1)};
enum dirs {
  RIGHT,
  DOWN,
  LEFT,
  UP
};

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}

void fill_region(vector<string>& grid, char c, int start_y, int start_x, unordered_set<Vec2, Vec2::hash_func>& visited,vector<Vec2>& result){
  visited.insert(Vec2(start_x, start_y));
  result.push_back(Vec2(start_x, start_y));
  for (const auto &dir : directions) {
    int dy = start_y + dir.y;
    int dx = start_x + dir.x;
    bool valid = in_bounds(dy, dx, grid.size(), grid[0].size());
    if(valid && grid[dy][dx] == c && visited.find(Vec2(dx,dy)) == visited.end()){
      fill_region(grid, c, dy,dx,visited,result);
    }
  }
}

vector<vector<Vec2>> get_regions(vector<string>& grid){
  unordered_set<Vec2, Vec2::hash_func> visited;
  vector<vector<Vec2>> result;
  int n = grid.size();
  int m = grid[0].size();
  for(int y = 0; y < n; y++){
    for(int x = 0; x < m; x++){
      if(visited.find(Vec2(x,y)) == visited.end()){
        vector<Vec2> region;
        fill_region(grid, grid[y][x],y,x,visited,region);
        result.push_back(region);
      }
    }
  }
  return result;
}

bool is_adjacent(Vec2& a, Vec2& b,bool vertical){
  return vertical ? abs((int)a.y - (int)b.y) == 1 && a.x == b.x : abs((int)a.x - (int)b.x) == 1 && a.y == b.y;
}

int get_num_connecting(vector<Vec2>& positions, bool vertical){
  int result = 0;
  int i = 0;
  int n = positions.size();
  while(i < n){
    while(++i < n && is_adjacent(positions[i], positions[i-1],vertical));
    result++;
  }
  return result;
}

double truncate_nearest_half(double value) {
    return std::round(value * 2.0) / 2.0;
}
//Group by connecting perimeters
int get_perimeter(vector<string>& grid, const vector<Vec2>& region){
  unordered_set<Vec2, Vec2::hash_func> inside_region;
  for(const auto& p : region){
    inside_region.insert(p);
  }
  vector<Vec2> horizontal_fences;

  vector<Vec2> vertical_fences;
  int result = 0;
  for(const auto& p : region){
    for(int i = 0; i < UP + 1; i++){
      Vec2 dir = directions[i];
      int dy = p.y + dir.y;
      int dx = p.x + dir.x;
      bool valid = in_bounds(dy, dx, grid.size(), grid[0].size());
      if(valid && inside_region.find(Vec2(dx,dy)) != inside_region.end()){
        continue;
      }
      double ddx = (dx - dir.x*0.75f); //offset them so we can put them "closer" to the tile they are actually bordering
      double ddy = (dy - dir.y*0.75f);
      if(i == UP || i == DOWN)
        horizontal_fences.push_back(Vec2(ddx,ddy)); // if we found an out of bounds above, that means the fence is horizontal, offset them a bit to avoid overlapping ones
      else{
        vertical_fences.push_back(Vec2(ddx,ddy));
      }
    }
  }
  //if we sort we get all of them in a row instead of using something like DFS
  sort(horizontal_fences.begin(), horizontal_fences.end());
  int horizontal_sides = get_num_connecting(horizontal_fences,false);
  sort(vertical_fences.begin(), vertical_fences.end(), [](auto a, auto b){
    if(a.x != b.x)
      return a.x < b.x;
    return a.y < b.y;
  });
  int vertical_sides = get_num_connecting(vertical_fences,true);
  return horizontal_sides + vertical_sides;
}

int main() {
  string line;
  vector<string> grid;

  while(getline(cin, line)){
    grid.push_back(line);
  };

  vector<vector<Vec2>> regions = get_regions(grid);
  long result = 0;
  for(const auto& region : regions){
    long perimeter = get_perimeter(grid, region);
    cout << "perm :" << perimeter << endl;
    result += perimeter * region.size();
  }
  cout << result;
  return 0;
}
