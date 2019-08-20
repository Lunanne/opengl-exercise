include_directories(${GLFW3_INCLUDE_DIRS})

set(SCENE_SRC
        Scene.cpp
        SceneObject.cpp)

set(SCENE_H
        Scene.h
        SceneObject.h SceneTypes.h)


add_library(scene ${SCENE_H} ${SCENE_SRC})
