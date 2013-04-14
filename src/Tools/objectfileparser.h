#ifndef OBJECTFILEPARSER_H
#define OBJECTFILEPARSER_H

#include <functional>
#include <unordered_map>
#include <string>
#include "../Graphics/GraphicsObject.h"
class ObjectFileParser
{
private:
	std::unordered_map<std::string,std::function<void(std::string,GraphicsObject*)>> parseFunctions;

public:
    ObjectFileParser();
    const void ParseObjFile(GraphicsObject *object);
};

#endif

