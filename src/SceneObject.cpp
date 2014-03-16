#include <iostream>

#include "Graphics/RenderComponent.h"

#include "SceneObject.h"

void SceneObject::SetName(std::string p_name)
{
    m_name = p_name;
}

void SceneObject::Render()
{
    if (m_renderComponent != NULL)
    {
        m_renderComponent->Render();
    }
}

void SceneObject::SetRenderComponent(RenderComponentPtr p_renderComponent)
{
    m_renderComponent = p_renderComponent;
}