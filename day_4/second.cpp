#include <cstdio>
#include <iostream>
#include <string>
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
};

std::array<struct Vector2, 8> directions = {Vector2(0,1), Vector2(1,0), Vector2(0,-1), Vector2(-1,0), Vector2(1,1), Vector2(-1,1), Vector2(1,-1), Vector2(-1,-1)};

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}


bool search_helper(std::vector<std::string> mat, int y, int x,Vector2 dir, std::string needle, int index){

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

bool search(std::vector<std::string> mat, int y, int x,Vector2 dir, std::string needle){
  return search_helper(mat, y, x, dir, needle, 0);
}

int main() {

  std::string line;
  std::vector<std::string> mat;
  while (getline(std::cin, line)) {
    mat.push_back(line);
  }

  int result = 0;
  std::string needle = "MAS";
  std::string needle_backwards = "SAM";
  for(int i = 0; i < (int)mat.size()-1;i++){
    for(int j = 0; j < (int)mat.size()-1;j++){
      if(mat[i][j] == 'A'){
        // search diagonally from here, starting one row up and down
        bool right_diagonal = search(mat, i - 1, j - 1, Vector2(1,1),  needle)  || search(mat, i - 1,  j - 1,  Vector2(1,1),  needle_backwards);
        bool left_diagonal =  search(mat, i - 1, j + 1, Vector2(1,-1), needle)  || search(mat, i - 1,  j + 1,  Vector2(1,-1), needle_backwards);
        result = right_diagonal && left_diagonal ? result + 1 : result;
      }
    }
  }

  std::cout << result << std::endl;

  return 0;
}
