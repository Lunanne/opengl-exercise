#include <vector>
#include "World.h"
#include "../Scene/SceneTypes.h"


void World::InitializeBullet() {
    m_collisionConfiguration = new btDefaultCollisionConfiguration();
    m_collisionDispatcher = new btCollisionDispatcher(m_collisionConfiguration);
    m_btBroadphaseInterface = new btDbvtBroadphase();
    m_solver = new btSequentialImpulseConstraintSolver();
    m_dynamicsWorld = new btDiscreteDynamicsWorld(m_collisionDispatcher, m_btBroadphaseInterface, m_solver,
                                                  m_collisionConfiguration);

    m_dynamicsWorld->setGravity(btVector3(0, -10, 0));
}

World::~World() {
    for (int i = m_dynamicsWorld->getNumCollisionObjects() - 1; i >= 0; i--) {
        btCollisionObject *object = m_dynamicsWorld->getCollisionObjectArray()[i];
        m_dynamicsWorld->removeCollisionObject(object);
    }

    for (int j = 0; j < m_collisionShapes.size(); j++) {
        m_collisionShapes[j] = 0;
    }

    delete m_dynamicsWorld;
    delete m_solver;
    delete m_btBroadphaseInterface;
    delete m_collisionDispatcher;
    delete m_collisionConfiguration;
}

void World::addPhysicsComponent(const PhysicsComponentPtr physicsComponentPtr) {
    m_collisionShapes.push_back(physicsComponentPtr->GetCollisionShape());
    m_dynamicsWorld->addRigidBody(physicsComponentPtr->GetRigidBody());
}

void World::SimulatePhysics() {
    m_dynamicsWorld->stepSimulation(1.f / 60.f, 10);

    //print positions of all objects
    for (int j = m_dynamicsWorld->getNumCollisionObjects() - 1; j >= 0; j--)
    {
        btCollisionObject* obj = m_dynamicsWorld->getCollisionObjectArray()[j];
        btRigidBody* body = btRigidBody::upcast(obj);
        btTransform trans;
        if (body && body->getMotionState())
        {
            body->getMotionState()->getWorldTransform(trans);
        }
        else
        {
            trans = obj->getWorldTransform();
        }
    }
}

void World::AddPhysicComponents(const std::vector<SceneObjectPtr> sceneObjects) {
    for(SceneObjectPtr sceneObjectPtr : sceneObjects){
        if(sceneObjectPtr->getPhysicsComponent() != nullptr){
            this->addPhysicsComponent(sceneObjectPtr->getPhysicsComponent());
        }
    }
}
