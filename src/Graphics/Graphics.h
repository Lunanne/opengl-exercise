#ifndef GRAPHICS_H
#define GRAPHICS_H

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __APPLE__
#define GLFW_INCLUDE_GLCOREARB
#else
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "../MainTypes.h"

class Graphics
{
public:
    ~Graphics();
    void InitializeGL();
    void PaintGL(GLFWwindow* p_window, const std::vector<SceneObjectPtr> p_sceneObjects);
};

#endif
