#include "main.hpp"
#include "Interpreter.hpp"
#include <cstring>
#include <thread>
#include <signal.h>


enum class State{
  Add,
  Clear,
  Debug,
  Exit,
  Reset,
  Run,
  Step,
  Free
};
int main(int argc, char const *argv[])
{
  State state=State::Free;
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
  
  Interpreter interpreter=Interpreter();

  if (argc ==3 && (int)strcmp(argv[1],"-f") == 0){
    std::ifstream file(argv[2]);
    std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    interpreter=Interpreter(data);
    
  } 
    while (true){

      std::string input;
      
      
      if (state == State::Run)
      {
        if (interpreter.pc >= interpreter.data.size()){
          state=State::Free;
        }
        interpreter.step();
        std::this_thread::sleep_for(std::chrono::milliseconds(config["delay"]));
        continue;
      }
      std::getline(std::cin, input);
      if (input == "exit"){
        break;
      } else if (input == "step"){
        interpreter.step();
      } else if (input == "run"){
        state=State::Run;
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
      std::this_thread::sleep_for(std::chrono::milliseconds(config["delay"]));
    }
  
  return 0;
}
