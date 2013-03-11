cmake_minimum_required(VERSION 2.8.9)
project(opengl-exercise)
set(CMAKE_AUTOMOC ON)
  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
 
 
find_package(Qt5Core REQUIRED )
find_package(Qt5OpenGL REQUIRED)
find_package(Qt5Gui REQUIRED)
find_package(Qt5Widgets REQUIRED)
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})

set(CMAKE_VERBOSE_MAKEFILE true)

add_subdirectory(Global)
add_subdirectory(Tools)
add_subdirectory(Graphics)


set(MAIN_SRC
main.cpp)

 add_definitions(${Qt5Widgets_DEFINITIONS})
set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")

add_executable(opengl-exercise ${MAIN_SRC})

target_link_libraries(opengl-exercise tools graphics)

qt5_use_modules(opengl-exercise Widgets OpenGL Gui)
target_link_libraries(opengl-exercise ${OPENGL_LIBRARIES})
target_link_libraries(opengl-exercise ${GLEW_LIBRARY})
