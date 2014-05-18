#ifndef DEFAULTSHADER_H
#define DEFAULTSHADER_H

#include <glm/glm.hpp>

#include "Shader.h"

class DefaultShader : public Shader
{
private:
    GLuint m_mvpLocation;
    glm::mat4 m_mvpMatrix;
    
    GLuint m_texSamplerLoc;

public:
    DefaultShader(const char* p_vsFilePath, const char* p_fsFilePath);
    virtual void Use();
    
};

#endif
