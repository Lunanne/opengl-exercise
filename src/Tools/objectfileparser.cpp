#include "objectfileparser.h"

#include <fstream>
#include <iostream>
#include <boost/algorithm/string.hpp>

const objectStruct ObjectFileParser::ParseObjFile(){
  objectStruct outputValue;
  std::cout<<"reading file \n";
  std::ifstream file("Resources/cube.obj");
  std::string line;
  while(std::getline(file,line)){
    std::cout<<line<<"\n";
      
  }
  return outputValue;
}