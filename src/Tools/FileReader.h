#ifndef FILEREADER_H
#define FILEREADER_H

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "../Graphics/GraphicsTypes.h"


class FileReader
{
public:
    static char* ReadFile(const char* p_fileName);
    static Image ReadPNG(const char* p_fileName);
    static const aiScene*  ReadScene(const std::string& p_filePath, Assimp::Importer& p_importer);
};
#endif
