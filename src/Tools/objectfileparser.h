#include "../Global/structs.h"
#include <functional>
#include <map>
#include <boost/unordered_map.hpp>
class ObjectFileParser
{
private:
    boost::unordered_map<std::string,std::function<void(std::string,objectStruct*)>> parseFuntions;

public:
    ObjectFileParser();
    const objectStruct ParseObjFile();
};

