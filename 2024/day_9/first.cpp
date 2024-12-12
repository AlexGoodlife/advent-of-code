#include <cmath>
#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
#include <sstream>

using std::ostream;

using namespace std;

vector<int> build_disk(string map){
  int id = 0;
  vector<int> result;
  stringstream s(map);
  for(int i= 0; i < (int)map.size(); i++){
    int amount = map[i] - '0';
    if(i % 2 != 0){
      for(int j = 0; j < amount; j++){
        result.push_back(-1);
      }
    }
    else{
      for(int j = 0; j < amount; j++){
        result.push_back(id);
      }
      id++;
    }
  }
  return result;
}

void swap(int& x, int& y){
  int tmp = x;
  x = y;
  y = tmp;
}

void compact(vector<int> &disk){
  int i = 0;
  int j = disk.size()-1;
  int n = disk.size();

  while(i < j && i < n && j >= 0){
    //for i skip non empty spaces
    while(i < n && disk[i] >= 0){
      i++;
    }
    //for j skip empty spaces
    while(disk[j] < 0){
      j--;
    }
    swap(disk[i++], disk[j--]);
  }
}

long compute_checksum(vector<int> &disk){
  int i = 0;
  long result = 0;
  int n = disk.size();
  int j = 0;
  while(i < n){
    if(disk[i] >= 0){
      result += j * disk[i];
      j++;
    }
    i++;
  }
  return result;
}

int main() {
  string line;
  string input;
  cin >> input;
  vector<int> disk = build_disk(input);
  compact(disk);
  cout << "size: " << disk.size() << endl;
  long checksum = compute_checksum(disk);
  cout << "\n";
  cout << checksum << "\n";

  return 0;
}
