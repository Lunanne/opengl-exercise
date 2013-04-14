cmake_minimum_required(VERSION 2.8.7)
project(opengl-exercise)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

set(CMAKE_CXX_FLAGS "-std=c++0x -o0 ${CMAKE_CXX_FLAGS}")
find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
#find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED)
find_package(GLFW REQUIRED)


include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
include_directories(${GLFW_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIR})

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

set(CMAKE_VERBOSE_MAKEFILE true)

#add_subdirectory(Global)
add_subdirectory(Tools)
add_subdirectory(Graphics)


set(MAIN_SRC
main.cpp)



add_executable(opengl-exercise ${MAIN_SRC})

target_link_libraries(opengl-exercise graphics)
target_link_libraries(opengl-exercise ${OPENGL_LIBRARIES})
target_link_libraries(opengl-exercise ${GLFW_LIBRARY})
target_link_libraries(opengl-exercise ${GLEW_LIBRARY})
target_link_libraries(opengl-exercise ${Boost_LIBRARIES})
