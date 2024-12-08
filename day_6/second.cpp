#include <cstdio>
#include <iostream>
#include <string>
#include <unordered_set>
#include <vector>
#include <array>


struct Vector2{
  int x;
  int y;

public:
  Vector2(int x, int y) {
    this->x = x;
    this->y = y;
  }
  bool operator==(const Vector2& otherPoint) const
  {
    if (this->x == otherPoint.x && this->y == otherPoint.y) return true;
    else return false;
  }

  struct hash_func
  {
    size_t operator()(const Vector2& point) const
    {
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };

  struct pair_hash_func
  {
    size_t operator()(const std::pair<Vector2,Vector2>& point) const
    {
      Vector2::hash_func f;
      return f(point.first) ^ f(point.second);
    }
  };
};

std::array<struct Vector2, 4> directions = {Vector2(-1,0), Vector2(0,1), Vector2(1,0), Vector2(0,-1)};

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}
//Return wether we are looping or not
bool path_loops(std::vector<std::string>& grid, int y, int x, int dir_index){
  std::unordered_set<std::pair<Vector2,Vector2>, Vector2::pair_hash_func> dist;

  Vector2 dir = directions[dir_index];
  while(in_bounds(y,x,grid.size(), grid[0].size())){
    if(grid[y][x] == '#' || grid[y][x] == 'O'){
      y -= dir.x;
      x -= dir.y;
      dir_index = (dir_index + 1) % directions.size();
      dir = directions[dir_index];
    }
    else{
      //We have looped and are going in the same direction
      if(dist.find(std::make_pair(Vector2(y,x), dir)) != dist.end()){
        return true;
      }
      dist.insert(std::make_pair(Vector2(y,x), dir));
      y += dir.x;
      x += dir.y;
    }
  }

  return false;
}

// Very inneficient solution, essentially just bruteforcing every possible position
int find_loops(std::vector<std::string> grid){
  //find where guard lies
  std::unordered_set<Vector2, Vector2::hash_func> visited;
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
  Vector2 dir = directions[dir_index];
  int result = 0;
  int start_x = x;
  int start_y = y;
  y += dir.x;
  x += dir.y;
  while (in_bounds(y, x, grid.size(), grid[0].size())) {
    if (grid[y][x] == '#' ) {
      y -= dir.x;
      x -= dir.y;
      dir_index = (dir_index + 1) % directions.size();
      dir = directions[dir_index];
      y += dir.x;
      x += dir.y;
    } else {
      if(grid[y][x] != '^' && (visited.find(Vector2(x,y)) == visited.end())){
        grid[y][x] = 'O';
        visited.insert(Vector2(x,y));
        if(path_loops(grid, start_y, start_x, 0)){
          result++;
        }
        grid[y][x] = '.';
      }
      y += dir.x;
      x += dir.y;
    }
  }
  return result;
}

int main() {
  std::string line;
  std::vector<std::string> grid;
  while (getline(std::cin, line)) { // Read all pairings
    grid.push_back(line);
  }
  std::cout << find_loops(grid) << std::endl;
  return 0;
}
