#ifndef DEFAULTSHADER_H
#define DEFAULTSHADER_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"

class DefaultShader : public Shader
{
private:
    GLint m_mvpLocation;
    glm::mat4 m_mvpMatrix;

public:
    DefaultShader(const char* p_vsFilePath, const char* p_fsFilePath, Camera camera);
    virtual void Use();

    float xfov_to_yfov(float xfov, float aspect);
};

#endif
