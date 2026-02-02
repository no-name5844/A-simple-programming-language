#include "main.hpp"
#include "Interpreter.hpp"
#include <cstring>
int main(int argc, char const *argv[])
{
  std::fstream fileConfig;
  fileConfig.open("config.json", std::ios::in);
  if (!fileConfig.is_open()){
    fileConfig.close();
    fileConfig.open("config.json", std::ios::out);
    fileConfig<<"{\n\t\"delay\": 10\n}";
    fileConfig.close();
    fileConfig.open("config.json", std::ios::in);
  }
  nlohmann::json config;
  if (fileConfig.is_open()) {
    fileConfig >> config;
    fileConfig.close();
  } else {
    config["delay"] = 1000/60;
  }
  
  Interpreter interpreter=Interpreter("",config["delay"]);

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
      _sleep(config["delay"]);
    }
  
  return 0;
}
