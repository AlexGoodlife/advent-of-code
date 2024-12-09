#include <cmath>
#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;
struct Pointf{
  double x;
  double y;
public:
  Pointf(double x, double y) {
    this->x = x;
    this->y = y;
  }
};

struct Point{
  int x;
  int y;

public:
  Point(int x, int y) {
    this->x = x;
    this->y = y;
  }
  bool operator==(const Point& otherPoint) const
  {
    if (this->x == otherPoint.x && this->y == otherPoint.y) return true;
    else return false;
  }

  struct hash_func
  {
    size_t operator()(const Point& point) const
    {
      size_t xHash = std::hash<int>()(point.x);
      size_t yHash = std::hash<int>()(point.y) << 1;
      return xHash ^ yHash;
    }
  };
};

unordered_map<char, vector<Point>> get_all_positions(vector<string>& grid){
  unordered_map<char, vector<Point>> result;
  for(int y = 0; y < (int)grid.size();y++){
    for (int x = 0; x < (int)grid[0].size(); x++) {
      if(grid[y][x] != '.'){
        result[grid[y][x]].push_back(Point(x,y));
      }
    }
  }
  return result;
}

bool in_bounds(int y, int x, int n, int m){
  return (y >= 0 && y < n) && (x >= 0 && x < m);
}

pair<Point,Point> calculate_antinode(Point p0, Point p1){
  int dx = p1.x - p0.x;
  int dy = p1.y - p0.y;
  Point r1 = Point(p0.x - dx, p0.y-dy);
  Point r2 = Point(p1.x + dx, p1.y+dy);
  return make_pair(r1,r2);
}

void calculate_resonant_frequencies(Point p0, Point p1, int n, int m, unordered_set<Point, Point::hash_func>& visited){
  int dx = p1.x - p0.x;
  int dy = p1.y - p0.y;
  Point r1 = p0;
  Point r2 = p1;
  vector<Point> result;
  bool r1_in = in_bounds(r1.y, r1.x, n, m);
  bool r2_in = in_bounds(r2.y, r2.x, n, m);
  while(r1_in || r2_in){
    if(r1_in)
      visited.insert(r1);
    if(r2_in)
      visited.insert(r2);

    r1 = Point(r1.x - dx, r1.y - dy);
    r2 = Point(r2.x + dx, r2.y + dy);
    r1_in = in_bounds(r1.y, r1.x, n, m);
    r2_in = in_bounds(r2.y, r2.x, n, m);
  }
}

void get_antinodes(vector<Point> points, int n, int m,unordered_set<Point, Point::hash_func>& visited){
  for(int i = 0; i < (int)points.size();i++){
    for(int j = i + 1; j < (int)points.size();j++){
      calculate_resonant_frequencies(points[i], points[j], n, m, visited);
    }
  }
}

int main() {
  string line;
  vector<string> grid;
  while (getline(cin, line)) {
    grid.push_back(line);
  }
  unordered_map<char, vector<Point>> positions = get_all_positions(grid);

  int result = 0;
  unordered_set<Point, Point::hash_func> visited;
  for(const auto& [key, pair] : positions){
    get_antinodes(pair, grid.size(), grid[0].size(),visited);
  }
  result = visited.size();
  cout << result << endl;
  return 0;
}