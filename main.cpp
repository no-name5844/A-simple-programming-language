#include "main.hpp"
class Interpreter;
int main(int argc, char const *argv[])
{
  
  if (argc ==3 && std::string(argv[1]) == "-f"){
    std::ifstream file(argv[2]);
    std::string data((std::istreambuf_iterator<char>(file)),
                     std::istreambuf_iterator<char>());
    Interpreter interpreter(data);
    interpreter.run();
    delete &data,&file;

  }
  
  while (true){
    std::string input;
    std::getline(std::cin, input);
    Interpreter interpreter=Interpreter();
    if (input == "exit"){
      break;
    } else if (input == "step"){
      interpreter.step();
    } else if (input == "run"){
      interpreter.run();
    } else{
      interpreter.add(input);
    }
  }
  return 0;
}
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

};
Interpreter::Interpreter(std::string data ){
  bool isEnd = false;
    int j=0;
  for (int i=0;j<data.size();i++){
    std::string tempData;
    
    while (data[j]!='\n')
    {
      tempData+=data[i];
      j++;
    } 
    this->data.push_back(tempData);
  }
}
Interpreter::~Interpreter(){
  this->data.clear();
}
void Interpreter::add(std::string str){
  this->data.push_back(str);
}
//./md
void Interpreter::run(){
  while (this->pc < this->data.size()){
    this->step();
  }
}
void Interpreter::step(){
  if (this->pc < this->data.size()){
    std::string line = this->data[this->pc];
    std::vector<std::string> token ;
    std::string tempToken;
    for (int i=0;i<line.size();i++){
      if (line[i] == ' '){
        token.push_back(tempToken);
        tempToken="";
      } else{
        tempToken+=line[i];
      }
    }
    token.push_back(tempToken);
    if (token[0] == "up"&&token.size() == 2&&isNumber(token[1])){
      
        this->reg[std::stoi(token[1])]++;
      
    } else if (token[0] == "down"&&token.size() == 2&&isNumber(token[1])){
        this->reg[std::stoi(token[1])]--;
    }
    
    else if (token[0] == "set"&&token.size() == 3&&isNumber(token[1])&&isNumber(token[2])){         
      this->reg[std::stoi(token[1])] = this->reg[std::stoi(token[2])];
    }
    else if (token[0] == "in"&&token.size() == 2&&isNumber(token[1])){
      std::cin>>this->reg[std::stoi(token[1])];
      
    }
    else if (token[0] == "out"&&token.size() == 2&&isNumber(token[1])){
      std::cout<<this->reg[std::stoi(token[1])]<<std::endl;
      
    }
    else if (token[0] == "ifpos"&&token.size() == 4&&isNumber(token[1])&&token[2] == "goto"&&isNumber(token[3])&&this->pc > std::stoi(token[3])){
      if (this->reg[std::stoi(token[1])] > 0&&std::stoi(token[3]) >= 0){
        if(this->reg[std::stoi(token[1])]>0){
        this->pc = std::stoi(token[3]);
        return;
      }
      }
      
    }
    else if (token[0] == "ifnng"&&token.size() == 4&&isNumber(token[1])&&token[2] == "goto"&&isNumber(token[3])&&this->pc > std::stoi(token[3])){
      if (this->pc > std::stoi(token[3])&&std::stoi(token[3]) >= 0){
        if(this->reg[std::stoi(token[1])]>=0){
        this->pc = std::stoi(token[3]);
        return;
      }
      }
    }
    else if (token[0] == "ifeq"&&token.size() == 5&&isNumber(token[1])&&token[3] == "=="&&isNumber(token[4])&&isNumber(token[2])&&this->pc > std::stoi(token[4])){  
      if (this->reg[std::stoi(token[1])] == this->reg[std::stoi(token[4])]&&std::stoi(token[4]) >= 0){
        this->pc = std::stoi(token[4]);
        return;
      }
    }
    else if (token[0] == "ifneq"&&token.size() == 5&&isNumber(token[1])&&token[3] == "!="&&isNumber(token[4])&&isNumber(token[2])&&this->pc > std::stoi(token[4])){  
      if (this->reg[std::stoi(token[1])] != this->reg[std::stoi(token[4])]&&std::stoi(token[4]) >= 0){
        this->pc = std::stoi(token[4]);
        return;
      }
    }
    else
    {
      throw std::runtime_error("Invalid instruction");
    }
    
    this->pc++;
  }
}
bool isNumber(std::string str){
  for (int i=0;i<str.size();i++){
    if (str[i] < '0' || str[i] > '9'||str[i] == '-'){
      return false;
    }
  }
  return true;
}

  
