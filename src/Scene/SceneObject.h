#ifndef SCENEOBJECT_H
#define SCENEOBJECT_H

#include <string>

#include <assimp/scene.h>

#include "../Graphics/GraphicsTypes.h"
#include "../Physics/PhysicsTypes.h"

class SceneObject {
public:
    SceneObject(const std::string &p_name);

    SceneObject(const aiNode *p_node, const aiScene &p_scene);

    PhysicsComponentPtr getPhysicsComponent() const;

    void Render();

private:
    RenderComponentPtr m_renderComponent;
    PhysicsComponentPtr m_physicsComponent;
    std::string m_name;
};

#endif