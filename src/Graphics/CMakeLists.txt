include_directories(${OPENGL_INCLUDE_DIR})
include_directories(${GLEW_INCLUDE_DIRS})


 set(GRAPHICS_SRC
 glwidget.cpp)
 
 set(GRAPHICS_H
 glwidget.h)


add_library(Graphics ${GRAPHICS_H} ${GRAPHICS_SRC})
IF(WIN32)
	target_link_libraries(Graphics ${QT_LIBRARIES})
ENDIF(WIN32)

IF(UNIX)
	qt5_use_modules(Graphics Widgets OpenGL Gui)
ENDIF(UNIX)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")

target_link_libraries(Graphics ${OPENGL_LIBRARIES})
target_link_libraries(Graphics ${GLEW_LIBRARIES})
