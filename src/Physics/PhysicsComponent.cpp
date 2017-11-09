#include <BulletCollision/CollisionShapes/btBoxShape.h>
#include <LinearMath/btDefaultMotionState.h>
#include "PhysicsComponent.h"
#include "../Graphics/GraphicsTypes.h"

PhysicsComponent::PhysicsComponent() {
    m_mass = 0.01f;
    m_collisionShape = new btBoxShape(btVector3(1, 1, 1));

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

btRigidBody *PhysicsComponent::GetRigidBody() const{
    return m_rigidBody;
}

btCollisionShape *PhysicsComponent::GetCollisionShape() const{
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
