#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <assimp/scene.h>
#include <GLFW/glfw3.h>
#include "SceneTypes.h"


class Scene
{
public:
    Scene(const std::string& p_filePath);
    ~Scene();
    const std::vector<SceneObjectPtr> GetSceneObjects() const;

private:
    void ConvertNodesToObjects(const aiNode* p_node, const aiScene& p_scene);
    std::vector<SceneObjectPtr> m_sceneObjects;
};
#endif
