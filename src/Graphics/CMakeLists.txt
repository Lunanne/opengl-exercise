include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})


 set(GRAPHICS_SRC
 glwidget.cpp)
 
 set(GRAPHICS_H
 glwidget.h)


add_library(Graphics ${GRAPHICS_H} ${GRAPHICS_SRC})
qt5_use_modules(Graphics Widgets OpenGL Gui)


target_link_libraries(Graphics ${OPENGL_LIBRARIES})
target_link_libraries(Graphics ${GLEW_LIBRARIES})
target_link_libraries(Graphics ${Qt5Widgets_LIBRARIES})