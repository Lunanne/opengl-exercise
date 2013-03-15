cmake_minimum_required(VERSION 2.8.9)
project(opengl-exercise)
set(CMAKE_AUTOMOC ON)
  # As moc files are generated in the binary dir, tell CMake
  # to always look for includes there:
  set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")
IF(WIN32) #the qt5 version on windows is compiled with opengl es2 which has issues with glew
        find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL REQUIRED)
	INCLUDE(${QT_USE_FILE})
	ADD_DEFINITIONS(${QT_DEFINITIONS})
	SET(EXTRA_LIBS "glu32.lib" "opengl32.lib")
ENDIF(WIN32)

IF(UNIX)#$on linux at least we can use qt5
	find_package(Qt5Core REQUIRED )
	find_package(Qt5OpenGL REQUIRED)
	find_package(Qt5Gui REQUIRED)
	find_package(Qt5Widgets REQUIRED)
	include_directories(${Qt5Core_INCLUDE_DIRS} ${Qt5OpenGL_INCLUDE_DIRS} ${Qt5Gui_INCLUDE_DIRS} ${Qt5Widgets_INCLUDE_DIRS})
	add_definitions(${Qt5Widgets_DEFINITIONS})
	set(CMAKE_CXX_FLAGS "${Qt5Widgets_EXECUTABLE_COMPILE_FLAGS}")
ENDIF(UNIX)
set(CMAKE_CXX_FLAGS "-std=c++0x ${CMAKE_CXX_FLAGS}")
find_package(OpenGL REQUIRED)
find_package(GLEW REQUIRED)
find_package(Boost REQUIRED)
find_package(GLM REQUIRED)


include_directories(${OPENGL_INCLUDE_DIRS})
include_directories(${GLEW_INCLUDE_DIRS})
include_directories(${GLM_INCLUDE_DIRS})

set(CMAKE_VERBOSE_MAKEFILE true)

add_subdirectory(Global)
add_subdirectory(Tools)
add_subdirectory(Graphics)


set(MAIN_SRC
main.cpp)

 

add_executable(opengl-exercise ${MAIN_SRC})

target_link_libraries(opengl-exercise tools graphics)
target_link_libraries(opengl-exercise ${OPENGL_LIBRARIES})
message(${GLEW_LIBRARIES})
target_link_libraries(opengl-exercise ${GLEW_LIBRARIES})

IF(WIN32)
message(${QT_LIBRARIES})
	target_link_libraries(opengl-exercise ${QT_LIBRARIES})
ENDIF(WIN32)

IF(UNIX)
	qt5_use_modules(opengl-exercise Widgets OpenGL Gui)
ENDIF(UNIX)
