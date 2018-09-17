#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <cstdio>

#include "DefaultShader.h"
#include "./GraphicsTypes.h"
#include "./Material.h"

DefaultShader::DefaultShader(const char *p_vsFilePath, const char *p_fsFilePath, const Camera camera) : Shader(
        p_vsFilePath, p_fsFilePath) {
    glm::mat4 projectionMatrix = glm::perspective(camera.m_viewAngle, camera.m_viewRatio, camera.m_nearDistance,
                                                  camera.m_farDistance);
    glm::mat4 viewMatrix = glm::lookAt(camera.m_position, camera.m_lookAtVec, camera.m_up);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    m_mvpLocation = glGetUniformLocation(m_programID, "MVP");
    glLinkProgram(m_programID);
    glUseProgram(m_programID);
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    GLuint blockIndex = glGetUniformBlockIndex(m_programID, "BlobSettings");
    glGetActiveUniformBlockiv(m_programID, blockIndex, GL_UNIFORM_BLOCK_DATA_SIZE, &m_blockSize);
    m_blockBuffer = (GLubyte *) malloc(m_blockSize);

    const GLchar *names[] = {"InnerColor", "OuterColor", "InnerRadius", "OuterRadius"};
    GLuint indices[4];
    glGetUniformIndices(m_programID, 4, names, indices);
    glGetActiveUniformsiv(m_programID, 4, indices, GL_UNIFORM_OFFSET, m_uniformOffset);

    GLfloat outerColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    GLfloat innerRadius = 1.f, outerRadius = 4.f;
    GLfloat innerColor[] = {0.0f, 0.0f, 0.0f, 0.0f};
    memcpy(m_blockBuffer + m_uniformOffset[0], innerColor, 4 * sizeof(GLfloat));
    memcpy(m_blockBuffer + m_uniformOffset[1], outerColor, 4 * sizeof(GLfloat));
    memcpy(m_blockBuffer + m_uniformOffset[2], &innerRadius, sizeof(GLfloat));
    memcpy(m_blockBuffer + m_uniformOffset[3], &outerRadius, sizeof(GLfloat));

    glGenBuffers(1, &m_uboHandle);
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, m_blockSize, m_blockBuffer, GL_DYNAMIC_DRAW);
    glBindBufferBase(GL_UNIFORM_BUFFER, 0, m_uboHandle);

}

void DefaultShader::Use(MaterialPtr material) {
    GLfloat innerColor[] = {material->getDiffuseColour().r, material->getDiffuseColour().g,
                            material->getDiffuseColour().b, material->getDiffuseColour().a};
    memcpy(m_blockBuffer + m_uniformOffset[0], innerColor, 4 * sizeof(GLfloat));
    glBindBuffer(GL_UNIFORM_BUFFER, m_uboHandle);
    glBufferData(GL_UNIFORM_BUFFER, m_blockSize, m_blockBuffer, GL_DYNAMIC_DRAW);
    Shader::Use(material);
}
