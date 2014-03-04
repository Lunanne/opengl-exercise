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

#include "GraphicsObject.h"
class Graphics
{

public:
    ~Graphics();
    void initializeGL();
    void paintGL(GLFWwindow* p_window);


private:
    void CreateShaders();
    void DestroyShaders();

    GLuint vertexShaderID;
    GLuint fragmentShaderID;
    GLuint programID;

    GraphicsObject* triangle;
};

#endif
