#include "../Global/structs.h"
#include <functional>
#include <map>
class ObjectFileParser
{
  private:
	  boost::unordered_map<std::string,std::function<void(std::string data,objectStruct* object)>> parseFuntions;
  
public:
  ObjectFileParser();
  const objectStruct ParseObjFile();
};

