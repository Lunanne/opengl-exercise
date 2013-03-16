
#include "../Global/structs.h"
#include <map>

class ObjectFileParser
{
  private:
    std::map<std::string,std::function<void(std::string data,objectStruct* object)>> parseFuntions;
  
public:
  ObjectFileParser();
  const objectStruct ParseObjFile();
};

