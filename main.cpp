#include "main.hpp"
#include "Interpreter.hpp"
#include <cstring>
int main(int argc, char const *argv[])
{

  Interpreter interpreter=Interpreter("",1000/60);
  if (argc ==3 && (int)strcmp(argv[1],"-f") == 0){
    std::ifstream file(argv[2]);
    std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    interpreter=Interpreter(data);
    
  } 
    while (true){

      std::string input;
      std::getline(std::cin, input);
      
      if (input == "exit"){
        break;
      } else if (input == "step"){
        interpreter.step();
      } else if (input == "run"){
        interpreter.run();
      } else if (input == "debug"){
        interpreter.debug();
      }
      else if (input == "clear"){
        interpreter=Interpreter();
      }
      else if(input == "reset"){
        interpreter.reset();
      }
      else{
        interpreter.add(input);
      }
      _sleep(1000/60);
    }
  
  return 0;
}
