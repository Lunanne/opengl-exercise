#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "DefaultShader.h"

DefaultShader::DefaultShader(const char* p_vsFilePath, const char* p_fsFilePath) : Shader(p_vsFilePath, p_fsFilePath)
{
    glm::mat4 projectionMatrix = glm::perspective(90.0f, 4.0f / 3.0f, 0.01f, 100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    m_mvpLocation = glGetUniformLocation(m_programID, "MVP");
    m_texSamplerLoc = glGetUniformLocation(m_programID, "texSampler");


}

void DefaultShader::Use()
{
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    glUniform1i(m_texSamplerLoc, 0);

    Shader::Use();
}