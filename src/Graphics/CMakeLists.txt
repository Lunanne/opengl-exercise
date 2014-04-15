include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${SOIL_INCLUDE_DIR})
include_directories("..")
include_directories("../Tools")

 set(GRAPHICS_SRC
 Graphics.cpp
 RenderComponent.cpp
 Material.cpp)

 set(GRAPHICS_H
 Graphics.h
 GraphicsTypes.h
 RenderComponent.h
 Material.h)


add_library(graphics ${GRAPHICS_H} ${GRAPHICS_SRC})
