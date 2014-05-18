#ifndef SHADER_H
#define SHADER_H

#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#endif


#include <glm/glm.hpp>

class Shader
{
protected:
    GLuint                     m_programID;
    GLuint                     m_vertexShaderID;
    GLuint                     m_fragmentShaderID;
    
    const GLchar*              m_vertexShader;
    const GLchar*              m_fragmentShader;

public:
    Shader();
    Shader(const char* p_vsFilePath, const char* p_fsFilePath);
    ~Shader();
    
    const GLuint GetProgramID() const { return m_programID;};
    virtual void Use();
    
    
};
#endif
