#include <cstdio>
#include <iostream>
#include <string>
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
};

std::array<struct Vec2, 8> directions = {Vec2(0,1), Vec2(1,0), Vec2(0,-1), Vec2(-1,0), Vec2(1,1), Vec2(-1,1), Vec2(1,-1), Vec2(-1,-1)};

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}


bool search_helper(std::vector<std::string> mat, int y, int x,Vec2 dir, std::string needle, int index){

  if(index == (int)needle.size()){
    return true;
  }
  if (!in_bounds(y, x, mat.size(), mat.size())){
    return false;
  }

  if(mat[y][x] != needle[index]){
    return false;
  }
  else{
    return search_helper(mat, y + dir.x , x + dir.y, dir, needle, index + 1);
  }
}

bool search(std::vector<std::string> mat, int y, int x,Vec2 dir, std::string needle){
  return search_helper(mat, y, x, dir, needle, 0);
}

int main() {

  std::string line;
  std::vector<std::string> mat;
  while (getline(std::cin, line)) {
    mat.push_back(line);
  }

  int result = 0;
  std::string needle = "XMAS";
  for(int i = 0; i < (int)mat.size();i++){
    for(int j = 0; j < (int)mat.size();j++){
      if(mat[i][j] == 'X'){
        for(int dir = 0; dir < (int)directions.size();dir++){
          result = search(mat,i,j,directions[dir],needle) ? result + 1 : result;
        }
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}
