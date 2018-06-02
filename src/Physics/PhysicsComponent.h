#ifndef OPENGL_EXERCISE_PHYSICSCOMPONENT_H
#define OPENGL_EXERCISE_PHYSICSCOMPONENT_H


#include <BulletCollision/CollisionShapes/btCollisionShape.h>
#include <BulletDynamics/Dynamics/btRigidBody.h>
#include <assimp/scene.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>


#include "../Graphics/GraphicsTypes.h"

class PhysicsComponent {
public:
    PhysicsComponent(const aiNode* p_node, const aiMesh* p_mesh);
    ~PhysicsComponent();
    btRigidBody* GetRigidBody() const;
    btCollisionShape* GetCollisionShape() const;
    const Vertex GetPositionOrigin() const;
private:
    float m_mass;
    btCollisionShape* m_collisionShape;
    btRigidBody* m_rigidBody;
};


#endif //OPENGL_EXERCISE_PHYSICSCOMPONENT_H
