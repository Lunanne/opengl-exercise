#include "objectfileparser.h"

#include <fstream>
#include <iostream>
#include <vector>
#include <boost/algorithm/string.hpp>
#include <boost/unordered_map.hpp>

ObjectFileParser::ObjectFileParser()
{
	std::function<void(std::string data,objectStruct* object)> ParseName =
		[](std::string data,objectStruct* object){
			std::vector<std::string> words;
			boost::split(words,	data, boost::is_any_of(" "));
			object->name = words[1];
	};
	parseFuntions.insert(std::string("o"),ParseName);
}

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