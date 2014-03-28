#ifndef OBJECTFILEPARSER_H
#define OBJECTFILEPARSER_H

#include <functional>
#include <unordered_map>
#include <string>
#include <vector>
#include <memory>
#include <string>

#include "../MainTypes.h"
#include "../Graphics/GraphicsTypes.h"
#include "materialfileparser.h"

typedef std::vector<std::string> Words;
typedef std::function<void(Words&)> ParsingFunction;

class ObjectFileParser
{
public:
    ObjectFileParser();
    void ParseObjFile(const std::string& p_filePath, std::vector<SceneObjectPtr>& p_sceneObjects);

private:
    int m_faceStartCount;
    std::vector<Vertex> m_indexedVertices;
    std::vector<Face>   m_faces;
    std::vector<TextureVertex> m_indexedTextureVert;
    MaterialFileParser m_materialParser;
    std::string m_materialName;

    std::unordered_map<std::string, ParsingFunction > m_parseFunctions;
    std::function<SceneObjectPtr(Words& p_data)> m_parseName;
    ParsingFunction m_parseVertices;
    ParsingFunction m_parseFaces;
    ParsingFunction m_parseTextureVertices;
    ParsingFunction m_parseMaterialName;

    void CreateFunctions();
    RenderComponentPtr CreateRenderComponent();
};

#endif
