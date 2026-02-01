#pragma once
#include "main.hpp"
class Interpreter{
public:
  Interpreter(std::string data="" );
  ~Interpreter();
  std::vector<std::string> data;
  void run();
  void step();
  int pc=0;
  void add(std::string str);
  std::unordered_map<int,int64_t> reg;
  void debug();
};