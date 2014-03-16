#ifndef OBJECTFILEPARSER_H
#define OBJECTFILEPARSER_H

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>

#include "../MainTypes.h"
#include "../Graphics/GraphicsTypes.h"

typedef std::function<void(const std::string&, RenderComponentPtr)> ParsingFunction;

class ObjectFileParser
{
    
public:
    ObjectFileParser();
    const void ParseObjFile(const std::string& p_filePath, std::vector<SceneObjectPtr>* p_sceneObjects);

private:
    int m_faceStartCount;
    std::unordered_map<std::string, ParsingFunction > m_parseFunctions;
    std::function<SceneObjectPtr(std::string p_data)> m_parseName;
    std::function<void(std::string p_data, RenderComponentPtr p_renderComponent)> m_parseVertices;
    std::function<void(std::string p_data, RenderComponentPtr p_renderComponent)> m_parseFaces;
    
    void CreateFunctions();
};

#endif
