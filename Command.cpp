//Command.cpp
#include "Command.hpp"

// Function implementations
bool isNumber(std::string str){
  for (int i=0;i<str.size();i++){
    if (str[i] < '0' || str[i] > '9'){// 不允许负号
      return false;
    }
  }
  return true;
}
Command getOpType(std::vector<std::string> tokens){
  if (tokens.empty()){
    return Command{OpType::Null, {}};
  }
  else if ((!tokens[0].empty())&&tokens[0] == "up"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::Up, {std::stoll(tokens[1])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "down"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::Down, {std::stoll(tokens[1])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "in"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::In, {std::stoll(tokens[1])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "out"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::Out, {std::stoll(tokens[1])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifpos"&&tokens.size() == 4&&!tokens[1].empty()&&isNumber(tokens[1])&&tokens[2] == "goto"&&!tokens[3].empty()&&isNumber(tokens[3])){
    return Command{OpType::IfPos, {std::stoll(tokens[1]), std::stoll(tokens[3])}};    
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifnng"&&tokens.size() == 4&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&tokens[2] == "goto"&&!tokens[3].empty()&&isNumber(tokens[3])){
    return Command{OpType::IfNng, {std::stoll(tokens[1]), std::stoll(tokens[3])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifeq"&&tokens.size() == 5&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&isNumber(tokens[2])&&!tokens[3].empty()&&tokens[3]=="goto"&&!tokens[4].empty()&&isNumber(tokens[4])){
    return Command{OpType::IfEq, {std::stoll(tokens[1]), std::stoll(tokens[2]), std::stoll(tokens[4])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifneq"&&tokens.size() == 5&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&isNumber(tokens[2])&&tokens[3]=="goto"&&!tokens[4].empty()&&isNumber(tokens[4])){     
    return Command{OpType::IfNeq, {std::stoll(tokens[1]), std::stoll(tokens[2]), std::stoll(tokens[4])}};
  }
  else if (!tokens[0].empty()&&tokens[0] == "set"&&tokens.size() == 3&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&isNumber(tokens[2]  )){
    return Command{OpType::Set, {std::stoll(tokens[1]), std::stoll(tokens[2])}};
  }
  else{
    return Command{OpType::Error, {}};
  }
}
std::vector<std::string> strToTokens(std::string str){

  std::vector<std::string> tokens;
  std::string tempToken;
  int j=0;
  while (str[j] == ' '||str[j] == '\0'||str[j] == '\n'||str[j] == '\r'){
      j++;
  }
  while (j<str.size()){
      if (str[j] == '#'){
        break;
      }
      else if (str[j] == ' '||str[j] == '\0'||str[j] == '\n'||str[j] == '\r'||j==str.size()){
        tokens.push_back(tempToken);
        tempToken.clear();
      }
      else
      {
        tempToken+=str[j];
      }
      j++;
  }
  return tokens;
}
