#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#define GLM_ENABLE_EXPERIMENTAL
#include <glm/gtx/transform.hpp>
#include <cstdio>

#include "DefaultShader.h"

DefaultShader::DefaultShader(const char* p_vsFilePath, const char* p_fsFilePath, const Camera camera) : Shader(p_vsFilePath, p_fsFilePath)
{
    glm::mat4 projectionMatrix = glm::perspective(camera.m_viewAngle, camera.m_viewRatio, camera.m_nearDistance, camera.m_farDistance);
    glm::mat4 viewMatrix = glm::lookAt(camera.m_position, camera.m_lookAtVec, camera.m_up);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    m_mvpLocation = glGetUniformLocation(m_programID, "MVP");


}

void DefaultShader::Use()
{
    glLinkProgram(m_programID);
    glUseProgram(m_programID);
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    Shader::Use();
}