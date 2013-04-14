#include "objectfileparser.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>
ObjectFileParser::ObjectFileParser()
{
    std::function<void(std::string data,GraphicsObject* object)> ParseName =
        [](std::string data,GraphicsObject* object)
    {
        std::vector<std::string> words;
        boost::split(words,data,boost::is_any_of(" "));
		object->SetName(words.at(1));
    };

    std::function<void(std::string data,GraphicsObject* object)> ParseVertices =
        [](std::string data,GraphicsObject* object)
    {
        std::vector<std::string> words;
        boost::split(words,data,boost::is_any_of(" "));
        for(std::string word : words)
        {
            if(word.compare("v")!=0)
            {
				object->AddVertCoord(boost::lexical_cast<GLfloat>(word));
            //    std::cout<<"parsing vertex data "<<std::endl;
            }
        }
    };

    std::function<void(std::string data,GraphicsObject* object)> ParseFaces =
        [](std::string data,GraphicsObject* object)
    {
        std::vector<std::string> words;
        boost::split(words,data,boost::is_any_of(" "));
        for(std::string word : words)
        {
            if(word.compare("f")!=0)
            {
				object->AddFaceIndex(boost::lexical_cast<GLshort>(word));
            }
        }
    };

    std::pair<std::string,std::function<void(std::string,GraphicsObject*)>> name("o",ParseName);
    std::pair<std::string,std::function<void(std::string,GraphicsObject*)>> vertex("v",ParseVertices);
    std::pair<std::string,std::function<void(std::string,GraphicsObject*)>> face("f",ParseFaces);
    parseFunctions.insert(name);
    parseFunctions.insert(vertex);
    parseFunctions.insert(face);
}

const void ObjectFileParser::ParseObjFile(GraphicsObject *object)
{
    std::cout<<"reading file \n";
    std::ifstream file ( "./Resources/monkey.obj" );
    std::string line;
    while(std::getline(file,line))
    {
        //std::cout<<line.substr(0,1)<<"\n";
        std::function<void(std::string data,GraphicsObject* object)> function = parseFunctions[line.substr(0,1)];
        if(function != nullptr)
            function(line,object);
    }
}
