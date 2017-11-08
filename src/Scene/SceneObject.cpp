#include <iostream>

#include <assimp/scene.h>

#include "../Graphics/RenderComponent.h"

#include "SceneObject.h"

SceneObject::SceneObject(const std::string &p_name) {
    m_name = p_name;
}

SceneObject::SceneObject(const aiNode *p_node, const aiScene &p_scene) {
    for (unsigned int i = 0; i < p_node->mNumMeshes; ++i) {
        const aiMesh *mesh = p_scene.mMeshes[p_node->mMeshes[i]];
        aiMaterial *aiMaterial = p_scene.mMaterials[mesh->mMaterialIndex];
        m_renderComponents = RenderComponentPtr(new RenderComponent(mesh, aiMaterial));
    }
}

RenderComponentPtr SceneObject::GetRenderComponent() { return m_renderComponents; }
