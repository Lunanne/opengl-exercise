#ifndef SCENE_H
#define SCENE_H

#include <vector>

#include <GLFW/glfw3.h>

#include "MainTypes.h"

class Scene
{
public:
    Scene(const std::string& p_filePath);
    ~Scene();
    const std::vector<SceneObjectPtr> GetSceneObjects() const;

private:
    std::vector<SceneObjectPtr> m_sceneObjects;
};
#endif
