 include_directories(${OPENGL_INCLUDE_DIR})
 
 set(GRAPHICS_SRC
 glwidget.cpp)
 
 set(GRAPHICS_H
 glwidget.h)
 
 add_library(Graphics ${GRAPHICS_H} ${GRAPHICS_SRC})