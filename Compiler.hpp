#pragma once
#include "Command.hpp"
class Compiler
{
public:
  Compiler();
  Compiler(std::string str);
  Compiler(std::vector<std::string> tokens);
  Compiler(std::vector<Command> commands);

  ~Compiler();
  std::vector<Command> compile(std::string str);
  std::vector<Command> getCommands();
  
private:
  std::vector<Command> commands;
};
