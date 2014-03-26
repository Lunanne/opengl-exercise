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

private:
    RenderComponentPtr m_renderComponent;
    std::string        m_name;
};
#endif