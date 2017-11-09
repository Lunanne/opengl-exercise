cmake_minimum_required(VERSION 2.8.12)
project(opengl-exercise)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

if(WIN32)
set(CMAKE_CXX_FLAGS "/Wall ${CMAKE_CXX_FLAGS}")
endif(WIN32)
if(NOT WIN32)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
endif(NOT WIN32)


find_package(OpenGL REQUIRED)
find_package(GLM REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost 1.55 REQUIRED)
find_package(GLFW REQUIRED)
find_package(PNG REQUIRED)
find_package(ASSIMP REQUIRED)
find_package(Bullet REQUIRED)

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

include_directories(${Boost_INCLUDE_DIRS})
include_directories(${GLFW3_INClLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIR})

include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})
include_directories(${BULLET_INCLUDE_DIRS})

include_directories(${PNG_INCLUDE_DIRS})

add_subdirectory(Tools)
add_subdirectory(Graphics)
add_subdirectory(Scene)
add_subdirectory(Physics)


set(MAIN_SRC
main.cpp
ThirdParty/stb_image.c)

set(MAIN_H
        ThirdParty/stb_image.h)



add_executable(opengl-exercise ${MAIN_SRC} ${MAIN_H})

set_property(TARGET opengl-exercise PROPERTY CXX_STANDARD 11)

target_link_libraries(opengl-exercise graphics)
target_link_libraries(opengl-exercise tools)
target_link_libraries(opengl-exercise scene)
target_link_libraries(opengl-exercise physics)

target_link_libraries(opengl-exercise ${BULLET_LIBRARIES})
target_link_libraries(opengl-exercise ${GLFW_LIBRARIES})
target_link_libraries(opengl-exercise ${GLEW_LIBRARY})
target_link_libraries(opengl-exercise ${Boost_LIBRARIES})
target_link_libraries(opengl-exercise ${PNG_LIBRARIES})
target_link_libraries(opengl-exercise ${ASSIMP_LIBRARIES})

target_link_libraries(opengl-exercise ${OPENGL_LIBRARIES})
if(APPLE)
target_link_libraries(opengl-exercise ${GLFW_LIBRARY})
    target_link_libraries(opengl-exercise ${COCOA_LIBRARIES})
    target_link_libraries(opengl-exercise ${COCOA_LIBRARY})
    target_link_libraries(opengl-exercise ${CoreVideo_LIBRARIES})
    target_link_libraries(opengl-exercise ${IOKit_LIBRARIES})
endif (APPLE)
