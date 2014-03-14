#ifndef OBJECTFILEPARSER_H
#define OBJECTFILEPARSER_H

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

#include "..\types.h"

class ObjectFileParser
{
public:
    ObjectFileParser();
    const void ParseObjFile(const std::string& p_filePath, std::vector<SceneObjectPtr>* p_sceneObjects);

private:
    std::unordered_map<std::string, std::function<void(std::string, RenderComponentPtr)>> m_parseFunctions;
};

#endif
