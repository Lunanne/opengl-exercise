#include <vector>
#include <iostream>

#include "Tools/objectfileparser.h"

#include "Scene.h"

Scene::Scene(const std::string& p_filePath)
{
    ObjectFileParser parser;
    parser.ParseObjFile(p_filePath, &m_sceneObjects);
    std::cout << "Number of read objects : " << m_sceneObjects.size() << std::endl;
}

const std::vector<SceneObjectPtr> Scene::GetSceneObjects() const
{
    return m_sceneObjects;
}

Scene::~Scene()
{
    m_sceneObjects.clear();
}