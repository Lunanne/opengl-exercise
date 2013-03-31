include_directories(${OPENGL_INCLUDE_DIR})

 set(GRAPHICS_SRC
 Graphics.cpp)

 set(GRAPHICS_H
 Graphics.h)


add_library(graphics ${GRAPHICS_H} ${GRAPHICS_SRC})

set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
