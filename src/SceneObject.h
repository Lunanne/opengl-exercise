#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include "Graphics/GraphicsTypes.h"

class SceneObject
{
public:
    SceneObject(const std::string& p_name);
    void SetRenderComponent(RenderComponentPtr p_renderComponent);
    void Render();
    void SetName(std::string p_name);
    const std::string& GetMaterialName();
    void SetMaterial(MaterialPtr p_material);

private:
    RenderComponentPtr m_renderComponent;
    std::string        m_name;
};
#endif