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

m_parseVertices = [](std::string p_data, RenderComponentPtr p_renderComponent)
{
    std::vector<std::string> words;
    boost::split(words, p_data, boost::is_any_of(" "));
    for (std::string word : words)
    {
        if (word.compare("v") != 0)
        {
            p_renderComponent->AddVertCoord(boost::lexical_cast<float>(word));
        }
    }
};

m_parseFaces = [this](std::string p_data, RenderComponentPtr p_renderComponent)
{
    std::vector<std::string> words;
    std::vector<std::string> coords;
    boost::split(words, p_data, boost::is_any_of(" "));
    for (std::string word : words)
    {
        if (word.compare("f") != 0)
        {
            boost::split(coords, word, boost::is_any_of("/"));
            p_renderComponent->AddFaceIndex(boost::lexical_cast<short>(coords[0]) - m_faceStartCount); //todo deal with texture coords
        }
    }
};
    std::pair<std::string, std::function<void(std::string, RenderComponentPtr)>> vertex("v ", m_parseVertices);
    std::pair<std::string, std::function<void(std::string, RenderComponentPtr)>> face("f ", m_parseFaces);
    m_parseFunctions.insert(vertex);
    m_parseFunctions.insert(face);

}


ObjectFileParser::ObjectFileParser():
m_faceStartCount(1)
{
    CreateFunctions();
}

const void ObjectFileParser::ParseObjFile(const std::string& p_filePath, std::vector<SceneObjectPtr>* p_sceneObjects)
{
    std::cout << "reading file \n";
    std::ifstream file(p_filePath);
    std::string line;
    SceneObjectPtr currentObject = NULL;
    RenderComponentPtr currentComponent = NULL;
    while (std::getline(file, line))
    {
        if (line.substr(0, 1) == "o")
        {
            if (currentObject == NULL)
            {
                currentObject = m_parseName(line);
                currentComponent = RenderComponentPtr(new RenderComponent);
            }
            else
            {
                
                m_faceStartCount = (currentComponent->GetVertexCount() / 3) + 1;
                currentObject->SetRenderComponent(currentComponent);
                p_sceneObjects->push_back(currentObject);
                currentObject = m_parseName(line);
                currentComponent = RenderComponentPtr(new RenderComponent);
            }
        }

        else
        {
            std::string key = line.substr(0, 2);
            if ( m_parseFunctions.count(key) >0)
            {
                std::function<void(std::string data, RenderComponentPtr object)> function = m_parseFunctions.at(key);
                function(line, currentComponent);
            }
        }
    }

    if (currentObject != NULL && currentComponent != NULL)
    {
        currentObject->SetRenderComponent(currentComponent);
        p_sceneObjects->push_back(currentObject);
    }
}