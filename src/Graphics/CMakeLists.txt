include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})
include_directories("..")

 set(GRAPHICS_SRC
 Graphics.cpp
 RenderComponent.cpp
 Material.cpp)

 set(GRAPHICS_H
 Graphics.h
 GraphicsTypes.h
 RenderComponent.h
 GraphicsTypes.h
 Material.h)


add_library(graphics ${GRAPHICS_H} ${GRAPHICS_SRC})
