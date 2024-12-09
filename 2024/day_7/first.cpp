#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>

int evaluate_expression(std::vector<long>& operands, std::stack<char>& operations){
  std::stack<int> stack;
  std::stack<char> ops = operations;
  for(int i = operands.size() -1; i >= 0; i--){
    stack.push(operands[i]);
  }

  while(!ops.empty()){
    long first = stack.top();
    stack.pop();
    long second = stack.top();
    stack.pop();

    if(ops.top() == '+'){
      stack.push(first + second);
    }
    else{
      stack.push(first * second);
    }
    ops.pop();
  }
  return stack.top();
}

bool is_valid(std::vector<long> operands, std::stack<char>& operations, int target){
  // we have filled all of them
  if(operations.size() == operands.size() - 1){
    return evaluate_expression(operands,  operations) == target;
  }

  bool result;
  operations.push('*');
  result = is_valid(operands, operations, target);
  operations.pop();
  if(result) return true;

  operations.push('+');
  result = is_valid(operands, operations, target);
  operations.pop();

  return result;
}
int main() {
  std::string line;
  long result = 0;
  while (getline(std::cin, line)) { // Read all pairings
    long expected;
    char _c;
    std::vector<long> operands;
    std::stringstream s(line);

    s >> expected;
    s >> _c;
    while(!s.eof()){
      long op;
      s >> op;
      operands.push_back(op);
    }
    std::stack<char> ops;
    if(is_valid(operands,ops,expected)){
      result += expected;
    }

  }
  std::cout << result << std::endl;
  return 0;
}
