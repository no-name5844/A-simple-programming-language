#include "Interpreter.hpp"

// Function declarations
bool isNumber(std::string str);
std::vector<std::string> strToTokens(std::string str);
Command getOpType(std::vector<std::string> tokens);
std::string opTypeToString(OpType type);

// Function implementations
bool isNumber(std::string str){
  for (int i=0;i<str.size();i++){
    if (str[i] < '0' || str[i] > '9'||str[i] == '-'){
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
Interpreter::Interpreter(std::string data,int delay){
  this->delay=delay;
  std::vector<Command> commands;
  std::string tempstr;
  int j=0;
  while (j<data.size() ){
    if (data[j] == '\n'||data[j]=='\r'){
      if (getOpType(strToTokens(tempstr)).type != OpType::Null){
        commands.push_back(getOpType(strToTokens(tempstr)));
      }
      tempstr.clear();
    }
    else{
      tempstr+=data[j];
    }
    j++;
  }
  this->data = commands;
}
std::vector<std::string> strToTokens(std::string str){

  std::vector<std::string> tokens;
  std::string tempToken;
  int j=0;
  while (str[j] == ' '||str[j] == '\0'||str[j] == '\n'||str[j] == '\r'){
      j++;
  }
  while (j<=str.size()){
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
Interpreter::~Interpreter(){
  this->data.clear();
  this->reg.clear();
  this->pc=0;

}
void Interpreter::run(){
  while (this->pc < this->data.size()){
    this->step();
  }
}
void Interpreter::step(){
  if (this->pc >= this->data.size()){

    return;
  }
  Command command = this->data[this->pc];
  this->pc++;
  switch (command.type)
  {
  case OpType::Up:
    this->reg[command.val[0]]++;
    break;
  case OpType::Down:
    this->reg[command.val[0]]--;
    break;
  case OpType::In:
    std::cin >> this->reg[command.val[0]];
    break;
  case OpType::Out:
    std::cout << this->reg[command.val[0]] << std::endl;
    break;
  case OpType::IfPos:
    if (this->reg[command.val[0]] > 0){
      this->pc = command.val[1] ;
    }
    break;
  case OpType::IfNng:
    if (this->reg[command.val[0]] < 0){
      this->pc = command.val[1] ;
    }
    break;
  case OpType::IfEq:
    if (this->reg[command.val[0]] == this->reg[command.val[1]]){
      this->pc = command.val[2] ;
    }
    break;
  case OpType::IfNeq:
    if (this->reg[command.val[0]] != this->reg[command.val[1]]){
      this->pc = command.val[2] ;
    }
    break;
  case OpType::Set:
    this->reg[command.val[0]] = this->reg[command.val[1]];
    break;
  case OpType::Error:
    std::cout << "Error: " << opTypeToString(command.type) << " at pc: " << this->pc-1  << std::endl;
    for (auto it = command.val.begin(); it != command.val.end(); it++){
      std::cout << *it << std::endl;
    }
    std::cout << "reg: " << std::endl;
    for (auto it = this->reg.begin(); it != this->reg.end(); it++){
      std::cout << it->first << ": " << it->second << std::endl;
    }
  case OpType::Null:
    
    break;
  default:
    break;
  }
  _sleep(this->delay);
}
std::string opTypeToString(OpType type){
  switch (type){
    case OpType::Up: return "Up";
    case OpType::Down: return "Down";
    case OpType::In: return "In";
    case OpType::Out: return "Out";
    case OpType::IfPos: return "IfPos";
    case OpType::IfNng: return "IfNng";
    case OpType::IfEq: return "IfEq";
    case OpType::IfNeq: return "IfNeq";
    case OpType::Set: return "Set";
    case OpType::Error: return "Error";
    default: return "Unknown";
  }
}
void Interpreter::reset(){
  this->pc=0;
  this->reg.clear();
}
void Interpreter::debug(){
  std::cout << "pc: " << this->pc << std::endl;
  std::cout << "reg: " << std::endl;
  for (auto it = this->reg.begin(); it != this->reg.end(); it++){
    std::cout << it->first << ": " << it->second << std::endl;
  }
  if (this->pc < this->data.size()){
    std::cout << "data: " << opTypeToString(data[this->pc].type) << std::endl;
    std::cout << "val: " << std::endl;
    for (auto it = data[this->pc].val.begin(); it != data[this->pc].val.end(); it++){
      std::cout << *it << std::endl;
    }
  }
}
void Interpreter::add(std::string str){
  this->data.push_back(getOpType(strToTokens(str)));
}