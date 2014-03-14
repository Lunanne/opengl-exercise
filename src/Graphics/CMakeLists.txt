include_directories(${OPENGL_INCLUDE_DIR})

 set(GRAPHICS_SRC
 Graphics.cpp
 RenderComponent.cpp)

 set(GRAPHICS_H
 Graphics.h
 RenderComponent.h
 types.h)


add_library(graphics ${GRAPHICS_H} ${GRAPHICS_SRC})