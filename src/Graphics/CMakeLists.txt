 include_directories(${OPENGL_INCLUDE_DIR})
 INCLUDE(${QT_USE_FILE})
 
 set(GRAPHICS_SRC
 glwidget.cpp)
 
 set(GRAPHICS_H
 glwidget.h)
 
 add_library(Graphics ${GRAPHICS_H} ${GRAPHICS_SRC})
 target_link_libraries(Graphics ${QT_LIBRARIES})