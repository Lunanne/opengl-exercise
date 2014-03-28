#include <iostream>

#include "Graphics/RenderComponent.h"

#include "SceneObject.h"

SceneObject::SceneObject(const std::string& p_name)
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

const std::string& SceneObject::GetMaterialName()
{
    return m_renderComponent->GetMaterialName();
}

void SceneObject::SetMaterial(MaterialPtr p_material)
{
    m_renderComponent->SetMaterial(p_material);
}