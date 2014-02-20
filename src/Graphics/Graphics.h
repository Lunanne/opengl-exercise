#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <GL/glew.h>
#include <glfw/glfw3.h>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
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
    const GLchar* vertexShader;
    const GLchar* fragmentShader;

    GraphicsObject* triangle;
};

#endif
