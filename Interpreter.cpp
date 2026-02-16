#include "Interpreter.hpp"


Interpreter::Interpreter(std::string data){
  
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
  commands.push_back(getOpType(strToTokens(tempstr)));
  this->data = commands;
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
    break;
  case OpType::Null:
    
    break;
  default:
    break;
  }
  
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
    std::cout << "data: " << opTypeToString(this->data[this->pc].type) << std::endl;  
    std::cout << "val: " << std::endl;
    for (auto it = this->data[this->pc].val.begin(); it != this->data[this->pc].val.end(); it++){
      std::cout << *it << std::endl;
    }
  }
}
void Interpreter::add(std::string str){
  this->data.push_back(getOpType(strToTokens(str)));
}