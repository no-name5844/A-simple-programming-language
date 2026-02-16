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
  Null,
  Error,
};

struct Command
{
  OpType type;
  std::vector<int64_t> val;
};



enum class ErrorType{
  None,
  InvalidOp,
  InvalidVal,
  InvalidReg,
  InvalidIf,
  InvalidSet,
};
bool isNumber(std::string str);
std::vector<std::string> strToTokens(std::string str);
Command getOpType(std::vector<std::string> tokens);
