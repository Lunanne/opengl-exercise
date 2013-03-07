 cmake_minimum_required(VERSION 2.6)
project(opengl-exercise)

find_package(Qt4 REQUIRED)
find_package(OpenGL REQUIRED)

set(QT_USE_QTOPENGL 1)
INCLUDE(${QT_USE_FILE})
include_directories(${OPENGL_INCLUDE_DIRS})

add_subdirectory(Graphics)

set(MAIN_SRC
main.cpp)

add_executable(opengl-exercise ${MAIN_SRC})
target_link_libraries(opengl-exercise Graphics)

target_link_libraries(opengl-exercise ${QT_LIBRARIES})
target_link_libraries(opengl-exercise ${OPENGL_LIBRARIES})
