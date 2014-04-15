#ifndef FILEREADER_H
#define FILEREADER_H

#include "../Graphics/GraphicsTypes.h"

class FileReader
{
public:
    static char* ReadFile(const char* p_fileName);
    static Image ReadPNG(const char* p_fileName);
};
#endif
