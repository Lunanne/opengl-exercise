#include <fstream>
#include <iostream>
#include <vector>
#include <string>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include "../SceneObject.h"
#include "types.h"
#include "RenderComponent.h"

#include "objectfileparser.h"

std::function<SceneObjectPtr(std::string p_data)> ParseName =
[](std::string p_data)
{
    std::vector<std::string> words;
    boost::split(words, p_data, boost::is_any_of(" "));
    SceneObjectPtr sceneObject = SceneObjectPtr(new SceneObject());
    sceneObject->SetName(words[1]);
    return sceneObject;
};

std::function<void(std::string p_data, RenderComponentPtr p_renderComponent)> ParseVertices =
[](std::string p_data, RenderComponentPtr p_renderComponent)
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

std::function<void(std::string p_data, RenderComponentPtr p_renderComponent)> ParseFaces =
[](std::string p_data, RenderComponentPtr p_renderComponent)
{
    std::vector<std::string> words;
    std::vector<std::string> coords;
    boost::split(words, p_data, boost::is_any_of(" "));
    for (std::string word : words)
    {
        if (word.compare("f") != 0)
        {
            boost::split(coords, word, boost::is_any_of("/"));
            p_renderComponent->AddFaceIndex(boost::lexical_cast<short>(coords[0]) - 1); //todo deal with texture coords
        }
    }
};

ObjectFileParser::ObjectFileParser()
{
    std::pair<std::string, std::function<void(std::string, RenderComponentPtr)>> vertex("v ", ParseVertices);
    std::pair<std::string, std::function<void(std::string, RenderComponentPtr)>> face("f ", ParseFaces);
    m_parseFunctions.insert(vertex);
    m_parseFunctions.insert(face);
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
                currentObject = ParseName(line);
                currentComponent = RenderComponentPtr(new RenderComponent);
            }
            else
            {
                currentObject->SetRenderComponent(currentComponent);
                p_sceneObjects->push_back(currentObject);
                currentObject = ParseName(line);
                currentComponent = RenderComponentPtr(new RenderComponent);
            }
        }

        else
        {
            std::function<void(std::string data, RenderComponentPtr object)> function = m_parseFunctions[line.substr(0, 2)];
            if (function != nullptr)
                function(line, currentComponent);
        }
    }

    if (currentObject != NULL && currentComponent != NULL)
    {
        currentObject->SetRenderComponent(currentComponent);
        p_sceneObjects->push_back(currentObject);
    }
}