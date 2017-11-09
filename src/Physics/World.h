#ifndef OPENGL_EXERCISE_WORLD_H
#define OPENGL_EXERCISE_WORLD_H

#include <btBulletDynamicsCommon.h>
#include "PhysicsTypes.h"
#include "../Scene/SceneTypes.h"

class World {
public:
    void InitializeBullet();

    ~World();

    void SimulatePhysics();

    void AddPhysicComponents(const std::vector<SceneObjectPtr> sceneObjects);

private:
    void addPhysicsComponent(const PhysicsComponentPtr physicsComponentPtr);

    btDefaultCollisionConfiguration *m_collisionConfiguration;
    btCollisionDispatcher *m_collisionDispatcher;
    btBroadphaseInterface *m_btBroadphaseInterface;
    btSequentialImpulseConstraintSolver *m_solver;
    btDiscreteDynamicsWorld *m_dynamicsWorld;
    btAlignedObjectArray<const btCollisionShape *> m_collisionShapes;

};

#endif //OPENGL_EXERCISE_WORLD_H
