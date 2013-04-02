#ifndef GRAPHICS_H
#define GRAPHICS_H
#include <GL/gl.h>

#include "GraphicsObject.h"
class Graphics
{
    
public:
    ~Graphics();

private:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();
    GLuint
        VertexShaderId,
        FragmentShaderId,
        ProgramId,
        VaoId,
        VboId,
        ColorBufferId;
    const GLchar* VertexShader;
    const GLchar* FragmentShader;
    GraphicsObject cube;


void CreateVBO();
void DestroyVBO();
void CreateShaders();
void DestroyShaders();

};

#endif 
