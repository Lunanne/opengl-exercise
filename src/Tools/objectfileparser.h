#include "../Global/structs.h"
#include <functional>
#include <map>
#include <QString>
#include <qmap.h>
class ObjectFileParser
{
private:
    QMap<QString,std::function<void(QString,objectStruct*)>> parseFuntions;

public:
    ObjectFileParser();
    const objectStruct ParseObjFile();
};

