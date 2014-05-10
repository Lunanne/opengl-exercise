#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include <assimp/scene.h>

#include "Graphics/GraphicsTypes.h"

class SceneObject
{
public:
    SceneObject(const std::string& p_name);
    SceneObject(const aiNode* p_node, const aiScene& p_scene);
    void AddRenderComponent(RenderComponentPtr p_renderComponent);
    void Render();
    void SetName(std::string p_name);
    const std::string& GetMaterialName();
    void SetMaterial(MaterialPtr p_material);

private:
    std::vector<RenderComponentPtr> m_renderComponents;
    std::string                     m_name;
};
#endif