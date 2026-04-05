#pragma once
#include"main.hpp"
#include"Command.hpp"

// Function declarations

class Interpreter{
public:
  Interpreter(std::string data="");
  ~Interpreter();
  std::vector<Command> data;

  int pc=0;
  void add(std::string str);
  std::unordered_map<int64_t,int64_t> reg;
  void debug();
  void run();//不建议使用
  void step();
  void reset();


};