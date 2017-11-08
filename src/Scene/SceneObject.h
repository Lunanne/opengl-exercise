#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include <assimp/scene.h>

#include "../Graphics/GraphicsTypes.h"

class SceneObject {
public:
    SceneObject(const std::string &p_name);

    SceneObject(const aiNode *p_node, const aiScene &p_scene);

    RenderComponentPtr GetRenderComponent();

    void SetName(std::string p_name);

private:
    RenderComponentPtr m_renderComponents;
    std::string m_name;
};

#endif