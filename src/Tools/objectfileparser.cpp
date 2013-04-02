#include "objectfileparser.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
ObjectFileParser::ObjectFileParser()
{
    std::function<void(std::string data,objectStruct* object)> ParseName =
    [](std::string data,objectStruct* object) {
        std::vector<std::string> words;
        boost::split(words,data,boost::is_any_of(" "));
        object->name = words.at(1);
    };

    std::function<void(std::string data,objectStruct* object)> ParseVertices =
    [](std::string data,objectStruct* object) {
        std::vector<std::string> words;
        boost::split(words,data,boost::is_any_of(" "));
        for(std::string word : words)
        {
            if(word.compare("v")!=0)
            {
                object->vertices.push_back(boost::lexical_cast<GLfloat>(word));
                std::cout<<"parsing vertex data "<<std::endl;
            }
        }
    };

    std::function<void(std::string data,objectStruct* object)> ParseFaces =
    [](std::string data,objectStruct* object) {
        std::vector<std::string> words;
        boost::split(words,data,boost::is_any_of(" "));
        for(std::string word : words)
        {
            if(word.compare("f")!=0)
            {
                object->faces.push_back(boost::lexical_cast<GLshort>(word));
            }
        }
    };

    std::pair<std::string,std::function<void(std::string,objectStruct*)>> name("o",ParseName);
    std::pair<std::string,std::function<void(std::string,objectStruct*)>> vertex("v",ParseVertices);
    std::pair<std::string,std::function<void(std::string,objectStruct*)>> face("f",ParseFaces);
    parseFunctions.insert(name);
    parseFunctions.insert(vertex);
    parseFunctions.insert(face);
}

const objectStruct ObjectFileParser::ParseObjFile() {
     std::cout<<"reading file \n";
     std::ifstream file ( "Resources/cube.obj" );
     std::string line;
     objectStruct output;
     while(std::getline(file,line)) {
         //std::cout<<line.substr(0,1)<<"\n";
         std::function<void(std::string data,objectStruct* object)> function = parseFunctions[line.substr(0,1)];
         if(function != nullptr)
             function(line,&output);
     }
     std::cout<<"Object name : " <<output.name <<"\n";
 	std::cout<<"Object vertices : \n ";
     for(GLfloat coord : output.vertices)
 	{
         std::cout<<coord <<"\n";
 	}
     return output;
}
