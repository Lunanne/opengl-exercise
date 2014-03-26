cmake_minimum_required(VERSION 2.8.12)
project(opengl-exercise)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(WIN32)
set(CMAKE_CXX_FLAGS "/Wall ${CMAKE_CXX_FLAGS}")
endif(WIN32)
if(!WIN32)
set(CMAKE_CXX_FLAGS "-Werror -Wall -std=c++11 ${CMAKE_CXX_FLAGS}")
endif(!WIN32)

find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
#find_package(GLUT REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED)
find_package(GLFW REQUIRED)
find_package(GLI REQUIRED)

if(APPLE)
SET(CMAKE_CXX_FLAGS "-std=c++11")
    set(CMAKE_FIND_FRAMEWORK ONLY)
    find_package(COCOA REQUIRED)
    find_package(CoreVideo REQUIRED)
    find_package(IOKit REQUIRED)

    include_directories(${COCOA_INCLUDE_DIRS})
    include_directories(${CoreVideo_INCLUDE_DIRS})
    include_directories(${IOKit_INCLUDE_DIRS})
endif (APPLE)

include_directories(${INCLUDE_DIRECTORIES} ${Boost_INCLUDE_DIRS})
include_directories(${GLFW3_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIR})

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

add_subdirectory(Tools)
add_subdirectory(Graphics)

include_directories(Graphics)


set(MAIN_SRC
main.cpp
Scene.cpp
SceneObject.cpp)

set(MAIN_H
Scene.h
SceneObject.h
MainTypes.h)



add_executable(opengl-exercise ${MAIN_SRC} ${MAIN_H})

target_link_libraries(opengl-exercise graphics)
target_link_libraries(opengl-exercise tools)


target_link_libraries(opengl-exercise ${GLFW_LIBRARIES})
target_link_libraries(opengl-exercise ${GLEW_LIBRARY})
target_link_libraries(opengl-exercise ${Boost_LIBRARIES})


target_link_libraries(opengl-exercise ${OPENGL_LIBRARIES})
if(APPLE)
target_link_libraries(opengl-exercise ${GLFW_LIBRARY})
    target_link_libraries(opengl-exercise ${CoreVideo_LIBRARIES})
    target_link_libraries(opengl-exercise ${IOKit_LIBRARIES})
    target_link_libraries(opengl-exercise ${COCOA_LIBRARIES})
endif (APPLE)
