include_directories(${BULLET_INCLUDE_DIRS})

message(${BULLET_INCLUDE_DIRS})
set(PHYSICS_SRC
        World.cpp
        PhysicsComponent.cpp)

set(PHYSICS_H
        World.h
        PhysicsComponent.h
        PhysicsTypes.h)


add_library(physics ${PHYSICS_H} ${PHYSICS_SRC})
