#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <SceneObject.h>
#include <MainTypes.h>
#include <Graphics/RenderComponent.h>

#include "objectfileparser.h"

void ObjectFileParser::CreateFunctions()
{
    m_parseName = [](Words& words)
    {
        return SceneObjectPtr(new SceneObject(words[0]));
    };

    m_parseVertices = [this](Words& words)
    {
        Vertex v;
        v.x = boost::lexical_cast<float>(words[0]);
        v.y = boost::lexical_cast<float>(words[1]);
        v.z = boost::lexical_cast<float>(words[2]);
        m_indexedVertices.push_back(v);
    };

    m_parseFaces = [this](Words& words)
    {
        std::vector<std::string> coords;
        for (std::string word : words)
        {
            boost::split(coords, word, boost::is_any_of("/"));
            Face f;
            f.vertexIndexes.push_back(boost::lexical_cast<short>(coords[0]) - m_faceStartCount);
            if (coords.size() > 1)
            {
                f.textureIndexes.push_back(boost::lexical_cast<short>(coords[1]) - m_faceStartCount);
            }

            m_faces.push_back(f);
            //todo deal with texture coords
        }
    };

    m_parseVertices = [this](Words& words)
    {
        Vertex v;
        v.x = boost::lexical_cast<float>(words[0]);
        v.y = boost::lexical_cast<float>(words[1]);
        v.z = boost::lexical_cast<float>(words[2]);
        m_indexedVertices.push_back(v);
    };

    m_parseTextureVertices = [this](Words& words)
    {
        TextureVertex vt;
        vt.u = boost::lexical_cast<float>(words[0]);
        vt.v = boost::lexical_cast<float>(words[1]);
        m_indexedTextureVert.push_back(vt);
    };

    std::pair<std::string, ParsingFunction> vertex("v", m_parseVertices);
    std::pair<std::string, ParsingFunction> faces("f", m_parseFaces);
    std::pair<std::string, ParsingFunction> texture("vt", m_parseTextureVertices);
    m_parseFunctions.insert(vertex);
    m_parseFunctions.insert(faces);
    m_parseFunctions.insert(texture);
}

ObjectFileParser::ObjectFileParser() :
m_faceStartCount(1)
{
    CreateFunctions();
}

void ObjectFileParser::ParseObjFile(const std::string& p_filePath, std::vector<SceneObjectPtr>& p_sceneObjects)
{
    std::cout << "reading file \n";
    std::ifstream file(p_filePath);
    std::string line;
    Words words;
    SceneObjectPtr currentObject;
    while (std::getline(file, line))
    {
        boost::split(words, line, boost::is_any_of(" "));
        if (words[0].compare("o") == 0)
        {
            if (currentObject == nullptr)
            {
                currentObject = m_parseName(words);
            }
            else
            {
                m_faceStartCount = m_indexedVertices.size();
                RenderComponentPtr currentComponent = CreateRenderComponent();
                currentObject->SetRenderComponent(currentComponent);
                p_sceneObjects.push_back(currentObject);
                currentObject = m_parseName(words);
            }
        }
        else
        {
            if (m_parseFunctions.count(words[0]) > 0)
            {
                ParsingFunction function = m_parseFunctions.at(words[0]);
                words.erase(words.begin());
                function(words);
            }
        }
    }

    if (currentObject != NULL)
    {
        RenderComponentPtr currentComponent = CreateRenderComponent();
        currentObject->SetRenderComponent(currentComponent);
        p_sceneObjects.push_back(currentObject);
    }
}

RenderComponentPtr ObjectFileParser::CreateRenderComponent()
{
    m_faceStartCount += m_indexedVertices.size();
    std::vector<Vertex> vertices;
    std::vector<TextureVertex> texCoords;
    for (Face face : m_faces)
    {
        for (GLshort index : face.vertexIndexes)
        {
            vertices.push_back(m_indexedVertices.at(index));
        }
        for (GLshort index1 : face.textureIndexes)
        {
            texCoords.push_back(m_indexedTextureVert.at(index1));
        }
    }
    m_indexedVertices.clear();
    m_indexedTextureVert.clear();
    m_faces.clear();
    return RenderComponentPtr(new RenderComponent(vertices, texCoords));
}