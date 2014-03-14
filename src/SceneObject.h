#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include "Graphics\types.h"

class SceneObject
{
public:
    void SetRenderComponent(RenderComponentPtr p_renderComponent);

    void Render();

    void SetName(std::string p_name);

private:
    RenderComponentPtr m_renderComponent;
    std::string        m_name;
};
#endif