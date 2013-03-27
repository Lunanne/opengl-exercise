#include "objectfileparser.h"
#include <qstringlist.h>

#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/concept_check.hpp>
ObjectFileParser::ObjectFileParser()
{
    std::function<void ( QString data,objectStruct* object ) > ParseName =
    [] ( QString data,objectStruct* object ) {
        QStringList words = data.split ( " " );
        object->name = words.at ( 1 );
    };

    std::function<void ( QString data,objectStruct* object ) > ParseVertices =
    [] ( QString data,objectStruct* object ) {
        QStringList words = data.split ( " " );
        float x = words[1].toFloat();
        float y = words[2].toFloat();
        float z = words[3].toFloat();
        glm::vec4 vertex ( x,y,z,0.0f );
        object->vertices.push_back ( vertex );
    };
    std::function<void ( QString data,objectStruct* object ) > ParseFaces =
    [] ( QString data,objectStruct* object ) {
        QStringList words = data.split ( " " );
        uint8_t vertex1 = words[1].toUInt()-1;
        uint8_t vertex2 = words[2].toUInt()-1;
        uint8_t vertex3 = words[3].toUInt()-1;
        
        
        uint8_t maxSize = object->vertices.size();
       // printf("%i, %i,%i,%i",vertex1,vertex2,vertex3,maxSize);
        if(vertex1<maxSize && vertex2<maxSize && vertex3<maxSize)
        {
        faceStruct face;
        face.vertices[0] = &object->vertices.at(vertex1);
        face.vertices[1] = &object->vertices.at(vertex2);
        face.vertices[2] = &object->vertices.at(vertex3);
        object->faces.push_back(face);
        }
    };


    parseFuntions.insert ( QString ( "o" ),ParseName );
    parseFuntions.insert ( QString ( "v" ),ParseVertices );
    parseFuntions.insert ( QString ( "f" ),ParseFaces );
}

const objectStruct ObjectFileParser::ParseObjFile()
{
    objectStruct outputValue;
    std::cout<<"reading file \n";
    std::ifstream file ( "Resources/cube.obj" );
    std::string line;
    objectStruct object;
    while ( std::getline ( file,line ) ) {
        QString qline ( line.c_str() );
        std::cout<<line<<"\n";
        std::function<void ( QString data,objectStruct* object ) > function = parseFuntions[qline.left ( 1 )];
        if ( function != nullptr ) {
            function ( qline,&object );
        }
    }
    std::cout<<"Object name : " <<object.name.toStdString() <<"\n";
    std::cout<<"Object vertices : \n ";
    
    for(faceStruct face : object.faces)
    {
      if(face.vertices[0] ==nullptr)
      {
        std::cout<<"vertice is null";
      }
    }
    return outputValue;
}