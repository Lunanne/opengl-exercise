#include <iostream>

#include <assimp/scene.h>

#include "../Graphics/RenderComponent.h"

#include "SceneObject.h"
#include "glm/ext.hpp"

SceneObject::SceneObject(const std::string &p_name) {
    m_name = p_name;
}


//TODO retrieve transformation from blender
SceneObject::SceneObject(const aiNode *p_node, const aiScene &p_scene) {
    m_name = p_node->mName.C_Str();
    for (unsigned int i = 0; i < p_node->mNumMeshes; ++i) {
        const aiMesh *mesh = p_scene.mMeshes[i];
        aiMaterial *aiMaterial = p_scene.mMaterials[mesh->mMaterialIndex];
        m_renderComponent = std::make_shared<RenderComponent>(mesh, aiMaterial);
        m_physicsComponent = std::make_shared<PhysicsComponent>(p_node, mesh);
    }
}

PhysicsComponentPtr SceneObject::getPhysicsComponent() const {
    return m_physicsComponent;
}


void SceneObject::Render() {
    if (m_renderComponent != nullptr) {
        m_renderComponent->Render(m_physicsComponent->GetPositionOrigin());
    }
}
