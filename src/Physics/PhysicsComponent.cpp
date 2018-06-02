#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <LinearMath/btDefaultMotionState.h>
#include <assimp/scene.h>
#include <BulletCollision/CollisionShapes/btConvexHullShape.h>
#include <BulletCollision/CollisionShapes/btConvexTriangleMeshShape.h>
#include "PhysicsComponent.h"

PhysicsComponent::PhysicsComponent(const aiNode *p_node, const aiMesh *p_mesh) {
    std::string name = std::string(p_node->mName.C_Str());
    if (name.substr(0, 2).compare("dr") == 0) {
        int pos = name.find("_");
        float test = std::stoi(name.substr(2, pos - 2));
        m_mass = std::stoi(name.substr(2, pos - 2)) / 1000.0f;
    } else if (name.substr(0, 2).compare("sr") == 0) {
        m_mass = 0;
    }

    m_collisionShape = new btConvexHullShape();
    for (int i = 0; i < p_mesh->mNumVertices; i++) {
        (dynamic_cast<btConvexHullShape *>(m_collisionShape))->addPoint(
                btVector3(p_mesh->mVertices[i].x, p_mesh->mVertices[i].y, p_mesh->mVertices[i].z));
    }
    btTransform startTransform;
    startTransform.setIdentity();

    btScalar mass(this->m_mass);

    btVector3 localInertia(0, 0, 0);
    m_collisionShape->calculateLocalInertia(mass, localInertia);
    startTransform.setOrigin(btVector3(0.5, 0.5, 0.5));
    btDefaultMotionState *myMotionState = new btDefaultMotionState(startTransform);
    btRigidBody::btRigidBodyConstructionInfo rbInfo(mass, myMotionState, m_collisionShape, localInertia);
    m_rigidBody = new btRigidBody(rbInfo);
}

btRigidBody *PhysicsComponent::GetRigidBody() const {
    return m_rigidBody;
}

btCollisionShape *PhysicsComponent::GetCollisionShape() const {
    return m_collisionShape;
}

PhysicsComponent::~PhysicsComponent() {
    delete m_rigidBody->getMotionState();
    delete m_rigidBody;
    delete m_collisionShape;
}

const Vertex PhysicsComponent::GetPositionOrigin() const {
    btTransform transform;
    m_rigidBody->getMotionState()->getWorldTransform(transform);
    return Vertex(transform.getOrigin().getX(), transform.getOrigin().getY(), transform.getOrigin().getZ());
}
