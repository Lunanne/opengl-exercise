#ifndef DEFAULTSHADER_H
#define DEFAULTSHADER_H

#include <glm/glm.hpp>

#include "Shader.h"
#include "Camera.h"
#include "./GraphicsTypes.h"
#include "Light.h"

class DefaultShader : public Shader
{
private:
    GLint m_mvpLocation;
    glm::mat4 m_mvpMatrix;
    GLubyte *m_blockBuffer;
    GLint m_uniformOffset[4];
    GLuint m_uboHandle;
    GLint m_blockSize;


public:
    DefaultShader(const char* p_vsFilePath, const char* p_fsFilePath, Camera camera, Light light);
    virtual void Use(MaterialPtr p_material);

    float xfov_to_yfov(float xfov, float aspect);
};

#endif
