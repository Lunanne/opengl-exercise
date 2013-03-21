#include "objectfileparser.h"
#include <qstringlist.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
ObjectFileParser::ObjectFileParser()
{
    std::function<void(QString data,objectStruct* object)> ParseName =
    [](QString data,objectStruct* object) {
        QStringList words = data.split(" ");        
        object->name = words.at(1);
    };
    
    std::function<void(QString data,objectStruct* object)> ParseVertices =
    [](QString data,objectStruct* object) {
        QStringList words = data.split(" ");
		float x = words[1].toFloat();
		float y = words[2].toFloat();
		float z = words[3].toFloat();
		glm::vec4 vertex(x,y,z,0.0f);
		object->vertices.push_back(vertex);
    };
    
    
    parseFuntions.insert(QString("o"),ParseName);
	parseFuntions.insert(QString("v"),ParseVertices);
}

const objectStruct ObjectFileParser::ParseObjFile() {
    objectStruct outputValue;
    std::cout<<"reading file \n";
    std::ifstream file("Resources/cube.obj");
    std::string line;
    objectStruct object;
    while(std::getline(file,line)) {
      QString qline(line.c_str());
        std::cout<<line<<"\n";
        std::function<void(QString data,objectStruct* object)> function = parseFuntions[qline.left(1)];
        if(function != nullptr)
            function(qline,&object);
    }
    std::cout<<"Object name : " <<object.name.toStdString() <<"\n";
	std::cout<<"Object vertices : \n ";
	for(glm::vec4 vec : object.vertices)
	{
		std::cout<<vec.x << " , "<<vec.y<< " , "<<vec.z <<"\n";
	}
    return outputValue;
}