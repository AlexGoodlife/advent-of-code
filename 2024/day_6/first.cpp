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
  bool operator==(const Vec2& otherVec2) const
  {
    if (this->x == otherVec2.x && this->y == otherVec2.y) return true;
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
};

std::array<struct Vec2, 4> directions = {Vec2(-1,0), Vec2(0,1), Vec2(1,0), Vec2(0,-1)};

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}

int trace_path(std::vector<std::string> grid){
  std::unordered_set<Vec2, Vec2::hash_func> dist;

  //find where guard lies
  int x, y;
  for(int i  = 0; i < (int)grid.size();i++){
    for(int j = 0; j < (int)grid[0].size(); j++){
      if(grid[i][j] == '^'){
        y = i;
        x = j;
      }
    }
  }

  int dir_index = 0;
  Vec2 dir = directions[dir_index];
  while(in_bounds(y,x,grid.size(), grid[0].size())){
    if(grid[y][x] == '#'){
      y -= dir.x;
      x -= dir.y;
      dir_index = (dir_index + 1) % directions.size();
      dir = directions[dir_index];
    }
    else{
      dist.insert(Vec2(y,x));
      y += dir.x;
      x += dir.y;
    }
  }


  return dist.size();
}

int main() {
  std::string line;
  std::vector<std::string> grid;
  while (getline(std::cin, line)) { // Read all pairings
    grid.push_back(line);
  }
  std::cout << trace_path(grid) << std::endl;
  return 0;
}
