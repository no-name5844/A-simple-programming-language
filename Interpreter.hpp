#pragma once
#include "main.hpp"
enum class OpType{
  Up,
  Down,
  In,
  Out,
  IfPos,
  IfNng,
  IfEq,
  IfNeq,
  Set,
  Null
};

struct Command
{
  OpType type;
  std::vector<int64_t> val;
};

class Interpreter{
public:
  Interpreter(std::string data="",int delay=1000/60 );
  ~Interpreter();
  std::vector<Command> data;
  void run();
  void step();
  int pc=0;
  void add(std::string str);
  std::unordered_map<int,int64_t> reg;
  void debug();
  void reset();
  int delay=1000/60;
};

enum class ErrorType{
  None,
  InvalidOp,
  InvalidVal,
  InvalidReg,
  InvalidIf,
  InvalidSet,
};

// Function declarations
bool isNumber(std::string str);
std::vector<std::string> strToTokens(std::string str);
Command getOpType(std::vector<std::string> tokens);
std::string opTypeToString(OpType type);

