#include <vector>
#include <iostream>

#include <assimp/scene.h>
#include <assimp/Importer.hpp>

#include "../Tools/FileReader.h"
#include "../Graphics/RenderComponent.h"
#include "SceneObject.h"
#include "Scene.h"

Scene::Scene(const std::string& p_filePath)
{
    Assimp::Importer importer;
    const aiScene* scene = FileReader::ReadScene(p_filePath, importer);
    ConvertNodesToObjects(scene->mRootNode, *scene);

}

const std::vector<SceneObjectPtr> Scene::GetSceneObjects() const
{
    return m_sceneObjects;
}

Scene::~Scene()
{
    m_sceneObjects.clear();
}

void Scene::ConvertNodesToObjects(const aiNode* p_node, const aiScene& p_scene)
{
    if (p_node->mNumMeshes > 0)
    {
        SceneObjectPtr object = SceneObjectPtr(new SceneObject(p_node, p_scene));        
        m_sceneObjects.push_back(object);
    }
    for (unsigned int c = 0; c < p_node->mNumChildren; ++c)
    {
        ConvertNodesToObjects(p_node->mChildren[c], p_scene);
    }
}