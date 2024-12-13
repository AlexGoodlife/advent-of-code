#include <cassert>
#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
#include <string>
#include <sstream>
#include <unordered_set>
#include <vector>
#include <array>

using namespace std;

const int num_blinks = 25;

void blink(list<long>& stones){
  list<long>::iterator it;
  for(it = stones.begin(); it != stones.end(); it++){
    long val = *it;
    string val_str = to_string(val);
    if(val == 0){
      *it = 1;
    }
    else if(val_str.size() % 2 == 0){
      string first = val_str.substr(0,val_str.size()/2 );
      string second = val_str.substr(val_str.size()/2);
      it = stones.insert(it, stol(first));
      it++;
      *it = stol(second);
    }
    else{
      *it = val*2024;
    }
  }
}

int main() {
  string line;
  list<long> stones;
  getline(cin, line);
  stringstream s(line);
  while(!s.eof()){
    int digit;
    s >> digit;
    stones.push_back(digit);
  }
  for(int i = 0; i < num_blinks; i++){
    blink(stones);
  }
  cout << stones.size() << endl;
  return 0;
}
