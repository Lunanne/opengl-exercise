#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <glfw/glfw3.h>

#include "..\types.h"

class Graphics
{
public:
    ~Graphics();
    void InitializeGL();
    void PaintGL(GLFWwindow* p_window, const std::vector<SceneObjectPtr> p_sceneObjects);
};

#endif
