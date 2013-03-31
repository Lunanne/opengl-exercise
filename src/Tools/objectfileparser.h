#include "structs.h"
#include <functional>
#include <unordered_map>
#include <string>
class ObjectFileParser
{
private:
    std::unordered_map<std::string,std::function<void(std::string,objectStruct*)>> parseFunctions;

public:
    ObjectFileParser();
    const objectStruct ParseObjFile();
};

