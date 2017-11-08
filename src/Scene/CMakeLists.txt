set(SCENE_SRC
        Scene.cpp
        SceneObject.cpp)

set(SCENE_H
        Scene.h
        SceneObject.h)


add_library(scene ${SCENE_H} ${SCENE_SRC})
