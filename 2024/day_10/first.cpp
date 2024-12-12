#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <array>

struct Vec2{
  int x;
  int y;

public:
  Vec2(int x, int y) {
    this->x = x;
    this->y = y;
  }
  bool operator==(const Vec2& otherVec) const
  {
    if (this->x == otherVec.x && this->y == otherVec.y) return true;
    else return false;
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

  struct pair_hash_func
  {
    size_t operator()(const std::pair<Vec2,Vec2>& point) const
    {
      Vec2::hash_func f;
      return f(point.first) ^ f(point.second);
    }
  };
};

using namespace std;

std::array<Vec2, 4> directions = {Vec2(-1,0), Vec2(0,1), Vec2(1,0), Vec2(0,-1)};

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}

int follow_trail(vector<string>& grid, int y, int x, unordered_set<int>& visited){
  visited.insert(y*grid.size() + x);
  if(grid[y][x] == '9'){
    return 1;
  }
  int result = 0;
  for(const auto& dir : directions){
    int dx = x + dir.y;
    int dy = y + dir.x;
    if(!in_bounds(dy,dx,grid.size(),grid[0].size())) continue;

    int val = grid[y][x] - '0';
    int next = grid[dy][dx] - '0';
    if(next != val+1 || visited.find(dy * grid.size() + dx) != visited.end()) continue;
    result += follow_trail(grid,dy,dx,visited);
  }
  return result;
}

int count_trailheads(vector<string>& grid){
  int n = grid.size();
  int m = grid[0].size();
  unordered_set<int> visited;
  int result = 0;
  for(int y = 0; y < n; y++){
    for(int x = 0; x < m; x++){
      if(grid[y][x] == '0'){
        visited.clear();
        result += follow_trail(grid, y, x,visited);
      }
    }
  }
  return result;
}

int main() {
  string line;
  vector<string> grid;
  while(getline(cin ,line)){
    grid.push_back(line);
  }
  cout << count_trailheads(grid) << endl;
  return 0;
}
