#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <SceneObject.h>
#include <MainTypes.h>
#include <Graphics/RenderComponent.h>

#include "objectfileparser.h"

void ObjectFileParser::CreateFunctions()
{
    m_parseName = [](std::string p_data)
    {
        std::vector<std::string> words;
        boost::split(words, p_data, boost::is_any_of(" "));
        SceneObjectPtr sceneObject = SceneObjectPtr(new SceneObject());
        sceneObject->SetName(words[1]);
        return sceneObject;
    };

    m_parseVertices = [this](Words p_data)
    {
        Vertex v;
        v.x = boost::lexical_cast<float>(p_data[0]);
        v.y = boost::lexical_cast<float>(p_data[1]);
        v.z = boost::lexical_cast<float>(p_data[2]);
        m_indexedVertices.push_back(v);
    };

    m_parseFaces = [this](Words p_data)
    {
        std::vector<std::string> coords;
        for (std::string word : p_data)
        {
            boost::split(coords, word, boost::is_any_of("/"));
            Face f;
            f.vertexIndex = boost::lexical_cast<short>(coords[0]) - m_faceStartCount;
            m_faces.push_back(f);
            //todo deal with texture coords
        }
    };
    std::pair<std::string, ParsingFunction> vertex("v", m_parseVertices);
    std::pair<std::string, ParsingFunction> face("f", m_parseFaces);
    m_parseFunctions.insert(vertex);
    m_parseFunctions.insert(face);
}

ObjectFileParser::ObjectFileParser() :
m_faceStartCount(1)
{
    CreateFunctions();
}

const void ObjectFileParser::ParseObjFile(const std::string& p_filePath, std::vector<SceneObjectPtr>* p_sceneObjects)
{
    std::cout << "reading file \n";
    std::ifstream file(p_filePath);
    std::string line;
    SceneObjectPtr currentObject = nullptr;
    Words words;
    while (std::getline(file, line))
    {
        boost::split(words, line, boost::is_any_of(" "));
        if (words[0].compare("o") == 0)
        {
            if (currentObject == nullptr)
            {
                currentObject = m_parseName(line);
            }
            else
            {
                currentObject->SetRenderComponent(CreateRenderComponent());
                p_sceneObjects->push_back(currentObject);
                currentObject = m_parseName(line);
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

    if (currentObject != nullptr)
    {
        currentObject->SetRenderComponent(CreateRenderComponent());
        p_sceneObjects->push_back(currentObject);
    }
}

RenderComponentPtr ObjectFileParser::CreateRenderComponent()
{
    m_faceStartCount += m_indexedVertices.size();
    std::vector<Vertex> vertices;
    for (Face face : m_faces)
    {
        Vertex v = m_indexedVertices.at(face.vertexIndex);
        vertices.push_back(v);
    }
    m_indexedVertices.clear();
    m_faces.clear();
    return RenderComponentPtr(new RenderComponent(vertices));
}