#include "Compiler.hpp"
Compiler::Compiler()
{
}
Compiler::Compiler(std::string str)
{
  std::vector<Command> commands;
  std::string tempstr;
  int j=0;
  while (j<str.size() ){
    if (str[j] == '\n'||str[j]=='\r'){
      if (getOpType(strToTokens(tempstr)).type != OpType::Null){
        commands.push_back(getOpType(strToTokens(tempstr)));
      }
      tempstr.clear();
    }
    else{
      tempstr+=str[j];
    }
    j++;
  }
  commands.push_back(getOpType(strToTokens(tempstr)));
  this->commands = commands;
  
}
Compiler::Compiler(std::vector<std::string> tokens)
{
  for (auto token : tokens)
  {
    this->commands.push_back(getOpType(strToTokens(token)));
  }
}
Compiler::Compiler(std::vector<Command> commands)
{
  this->commands=commands;
} 
