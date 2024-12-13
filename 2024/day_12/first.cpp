#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <sys/types.h>
#include <unordered_set>
#include <vector>
#include <array>

using namespace std;

struct Vec2{
  int x;
  int y;

public:
  Vec2(int x, int y) {
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
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};

std::array<struct Vec2, 4> directions = {Vec2(0,1), Vec2(1,0), Vec2(0,-1), Vec2(-1,0)};

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


int get_perimeter(vector<string>& grid, const vector<Vec2>& region){
  unordered_set<Vec2, Vec2::hash_func> visited;
  for(const auto& p : region){
    visited.insert(p);
  }
  int result = 0;
  for(const auto& p : region){
    for(const auto& dir : directions){
      int dy = p.y + dir.y;
      int dx = p.x + dir.x;
      bool valid = in_bounds(dy, dx, grid.size(), grid[0].size());
      if(!valid || visited.find(Vec2(dx,dy)) == visited.end())
        result++;
    }
  }
  return result;
}
int main() {
  string line;
  vector<string> grid;

  while(getline(cin, line)){
    grid.push_back(line);
  };

  vector<vector<Vec2>> regions = get_regions(grid);
  int result = 0;
  for(const auto& region : regions){
    int perimeter = get_perimeter(grid, region);
    cout << "perm :" << perimeter << endl;

    // for(const auto& i : region){
    //   cout << "y :"  << i.y << " x: " << i.x << " ";
    // }
    // cout << endl;
  }
  cout << result;
  return 0;
}
