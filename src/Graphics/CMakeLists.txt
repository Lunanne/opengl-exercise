include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

include_directories(../Tools)
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

 set(GRAPHICS_SRC
 glwidget.cpp)
 
 set(GRAPHICS_H
 glwidget.h)


add_library(graphics ${GRAPHICS_H} ${GRAPHICS_SRC})
target_link_libraries(graphics tools)
qt5_use_modules(graphics Widgets OpenGL Gui)
target_link_libraries(graphics ${OPENGL_LIBRARIES})
target_link_libraries(graphics ${GLEW_LIBRARIES})