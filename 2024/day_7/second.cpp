#include <cstdio>
#include <iostream>
#include <stack>
#include <string>
#include <sstream>
#include <vector>
#include <array>

std::array<std::string, 3> possible_operators = {"+", "*", "||"};

long concat(long first, long second){
  return std::stol(std::to_string(first) + std::to_string(second));
}

long evaluate_expression(std::vector<long>& operands, std::vector<std::string>& operations){
  std::stack<long> stack;
  for(int i = operations.size(); i >= 0; i--){
    stack.push(operands[i]);
  }
  int stack_index = operations.size() - 1;

  while(stack_index >= 0){
    long first = stack.top();
    stack.pop();
    long second = stack.top();
    stack.pop();

    std::string op = operations[stack_index];
    if(op == "+"){
      stack.push(first + second);
    }
    else if(op == "||"){
      stack.push(concat(first, second));
    }
    else{
      stack.push(first * second);
    }
    stack_index--;
  }
  return stack.top();
}

// TODO: This can get slow, some pruning would be nice ans: 105517128211543
bool is_valid(std::vector<long>& operands, std::vector<std::string>& operations, long target){
  // we have reached a terminal node
  if(operations.size() == operands.size() - 1){
    return evaluate_expression(operands,  operations) == target;
  }

  if(evaluate_expression(operands , operations) > target){
    return false;
  }

  bool result;
  for(const auto& o : possible_operators){
    operations.push_back(o);
    result = is_valid(operands, operations, target);
    if(result) return true;
    operations.pop_back();
  }
  return result;
}

int main(int argc, const char** argv) {
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
    std::vector<std::string> ops;
    if(is_valid(operands,ops,expected)){
      result += expected;
    }

  }
  std::cout << result << std::endl;
  return 0;
}
