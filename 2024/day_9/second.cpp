#include <cmath>
#include <cstdio>
#include <iostream>
#include <list>
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

struct Chunk {
  int start;
  int size;
  Chunk(int start, int size): start(start) ,size(size) {}
  friend ostream &operator<<(ostream &os, const Chunk& c) {
    return os << "[start: " << c.start << ", size: " << c.size << "]";
  }

  bool operator==(const Chunk& otherChunk) const
  {
    return this->start == otherChunk.start && this->size == otherChunk.size;
  }
};

list<Chunk> get_free_memory(vector<int> & disk){
  int i = disk.size() -1;
  list<Chunk> result;
  while(i >= 0){
    while(i >= 0 && disk[i] >= 0){
      i--;
    }
    int size = 0;
    int id = disk[i];
    while(i >= 0 && disk[i] == id){
      size++;
      i--;
    }
    if(size > 0){
      result.push_front(Chunk(i+1,size));
    }
  }
  return result;
}

void swap_chunks(const Chunk& c1, const Chunk& c2, vector<int> &disk){
  int i = c1.start;
  int j = c2.start;

  int limit = min(c1.size,c2.size);
  for(int _ = 0; _ < limit;_++){
    swap(disk[i++], disk[j++]);
  }
}

// TODO: This probably could be a better algorithm but its just what I came up with
void compact(vector<int> &disk){
  int j = disk.size()-1;
  list<Chunk> free_chunks = get_free_memory(disk);

  while(j >= 0){
    //for j skip empty spaces
    while(j >= 0 && disk[j] < 0){
      j--;
    }
    if(j < 0) break;

    //Check memory block
    int id = disk[j];
    int size = 0;
    while(j >= 0 && disk[j] == id){
      j--;
      size++;
    }
    if(size == 0) continue;
      //find first available memory
    for(auto& free : free_chunks){
      if(free.start < j+1 && free.size >= size){
        Chunk occupied(j+1,size);
        swap_chunks(free,occupied,disk);

        if(free.size == size){
          free_chunks.remove(free);
        }
        else{
          free.start += size;
          free.size -= size;
        }
        break;
      }
    }
  }
}

long compute_checksum(vector<int> &disk){
  int i = 0;
  long result = 0;
  int n = disk.size();
  while(i < n){
    if(disk[i] >= 0){
      result += i * disk[i];
    }
    i++;
  }
  return result;
}

int main() {
  string line;
  vector<string> grid;
  string input;
  cin >> input;

  vector<int> disk = build_disk(input);
  compact(disk);
  long checksum = compute_checksum(disk);

  cout << checksum << "\n";
  return 0;
}
