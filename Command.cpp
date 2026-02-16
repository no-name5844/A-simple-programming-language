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
    return Command{OpType::Null, {}, ErrorType::None, ""};
  }
  else if ((!tokens[0].empty())&&tokens[0] == "up"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::Up, {std::stoll(tokens[1])}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "down"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::Down, {std::stoll(tokens[1])}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "in"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::In, {std::stoll(tokens[1])}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "out"&&tokens.size() == 2&&!tokens[1].empty()&&isNumber(tokens[1])){
    return Command{OpType::Out, {std::stoll(tokens[1])}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifpos"&&tokens.size() == 4&&!tokens[1].empty()&&isNumber(tokens[1])&&tokens[2] == "goto"&&!tokens[3].empty()&&isNumber(tokens[3])){
    return Command{OpType::IfPos, {std::stoll(tokens[1]), std::stoll(tokens[3])-1}, ErrorType::None, ""};    
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifnng"&&tokens.size() == 4&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&tokens[2] == "goto"&&!tokens[3].empty()&&isNumber(tokens[3])){
    return Command{OpType::IfNng, {std::stoll(tokens[1]), std::stoll(tokens[3])-1}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifeq"&&tokens.size() == 5&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&isNumber(tokens[2])&&!tokens[3].empty()&&tokens[3]=="goto"&&!tokens[4].empty()&&isNumber(tokens[4])){
    return Command{OpType::IfEq, {std::stoll(tokens[1]), std::stoll(tokens[2]), std::stoll(tokens[4])-1}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "ifneq"&&tokens.size() == 5&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&isNumber(tokens[2])&&tokens[3]=="goto"&&!tokens[4].empty()&&isNumber(tokens[4])){     
    return Command{OpType::IfNeq, {std::stoll(tokens[1]), std::stoll(tokens[2]), std::stoll(tokens[4])-1}, ErrorType::None, ""};
  }
  else if (!tokens[0].empty()&&tokens[0] == "set"&&tokens.size() == 3&&!tokens[1].empty()&&isNumber(tokens[1])&&!tokens[2].empty()&&isNumber(tokens[2]  )){
    return Command{OpType::Set, {std::stoll(tokens[1]), std::stoll(tokens[2])}, ErrorType::None, ""};
  }
  else{
    // 分析具体错误类型
    ErrorType errorType = ErrorType::InvalidOp;
    std::string errorMessage = "Invalid operation";
    
    if (!tokens.empty()) {
      std::string op = tokens[0];
      if (op == "up" || op == "down" || op == "in" || op == "out") {
        if (tokens.size() != 2) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Incorrect number of arguments for " + op + " command";
        } else if (!isNumber(tokens[1])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid register number for " + op + " command";
        }
      } else if (op == "ifpos" || op == "ifnng") {
        if (tokens.size() != 4) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Incorrect number of arguments for " + op + " command";
        } else if (!isNumber(tokens[1])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid register number for " + op + " command";
        } else if (tokens[2] != "goto") {
          errorType = ErrorType::InvalidSyntax;
          errorMessage = "Expected 'goto' after register number in " + op + " command";
        } else if (!isNumber(tokens[3])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid line number for " + op + " command";
        }
      } else if (op == "ifeq" || op == "ifneq") {
        if (tokens.size() != 5) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Incorrect number of arguments for " + op + " command";
        } else if (!isNumber(tokens[1])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid register number for " + op + " command";
        } else if (!isNumber(tokens[2])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid register number for " + op + " command";
        } else if (tokens[3] != "goto") {
          errorType = ErrorType::InvalidSyntax;
          errorMessage = "Expected 'goto' after register numbers in " + op + " command";
        } else if (!isNumber(tokens[4])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid line number for " + op + " command";
        }
      } else if (op == "set") {
        if (tokens.size() != 3) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Incorrect number of arguments for set command";
        } else if (!isNumber(tokens[1])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid register number for set command";
        } else if (!isNumber(tokens[2])) {
          errorType = ErrorType::InvalidVal;
          errorMessage = "Invalid register number for set command";
        }
      }
    }
    
    return Command{OpType::Error, {}, errorType, errorMessage};
  }
}
std::vector<std::string> strToTokens(std::string str){

  std::vector<std::string> tokens;
  std::string tempToken;
  int j=0;
  
  // 跳过开头的空白字符
  while (j<str.size() && (str[j] == ' '||str[j] == '\t'||str[j] == '\n'||str[j] == '\r')){
      j++;
  }
  
  // 处理非空字符串
  while (j<str.size()){
      if (str[j] == '#'){
        // 遇到注释，结束处理
        break;
      }
      else if (str[j] == ' '||str[j] == '\t'||str[j] == '\n'||str[j] == '\r'){
        // 遇到空白字符，添加当前token并重置
        if (!tempToken.empty()) {
          tokens.push_back(tempToken);
          tempToken.clear();
        }
        // 跳过连续的空白字符
        while (j<str.size() && (str[j] == ' '||str[j] == '\t'||str[j] == '\n'||str[j] == '\r')){
            j++;
        }
        continue;
      }
      else
      {
        // 添加字符到当前token
        tempToken+=str[j];
        j++;
      }
  }
  
  // 添加最后一个token（如果非空）
  if (!tempToken.empty()) {
    tokens.push_back(tempToken);
  }
  
  return tokens;
}
