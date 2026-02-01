#include "main.hpp"
#include "Interpreter.hpp"
int main(int argc, char const *argv[])
{
  
  if (argc ==3 && std::string(argv[1]) == "-f"){
    std::ifstream file(argv[2]);
    std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    Interpreter interpreter(data);
    interpreter.run();
    return 0;
  } else {
    Interpreter interpreter=Interpreter();
    while (true){
      std::string input;
      std::getline(std::cin, input);
      
      if (input == "exit"){
        break;
      } else if (input == "step"){
        interpreter.step();
      } else if (input == "run"){
        interpreter.run();
        interpreter=Interpreter();
      } else if (input == "debug"){
        interpreter.debug();
      }
      else{
        interpreter.add(input);
      }
    }
  }
  return 0;
}
