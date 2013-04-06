#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <GL/glew.h>
#include <GL/gl.h>
#include "GraphicsObject.h"
class Graphics
{

public:
    ~Graphics();
    void initializeGL();
    void paintGL();


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
