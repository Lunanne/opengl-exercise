#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <cstdio>

#include "DefaultShader.h"
#include "./GraphicsTypes.h"
#include "./Material.h"
#include "Light.h"

DefaultShader::DefaultShader(const char *p_vsFilePath, const char *p_fsFilePath, const Camera camera, const Light light)
        : Shader(
        p_vsFilePath, p_fsFilePath) {
    glm::mat4 projectionMatrix = glm::perspective(camera.m_viewAngle, camera.m_viewRatio, camera.m_nearDistance,
                                                  camera.m_farDistance);
    glm::mat4 viewMatrix = glm::lookAt(camera.m_position, camera.m_lookAtVec, camera.m_up);

    glm::mat4 modelMatrix = glm::mat4(1.0f);
    glm::mat4 modelViewMatrix = viewMatrix * modelMatrix;
    m_mvpMatrix = projectionMatrix * modelViewMatrix;
    m_mvpLocation = glGetUniformLocation(m_programID, "MVP");
    glLinkProgram(m_programID);
    glUseProgram(m_programID);
    glUniformMatrix4fv(m_mvpLocation, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    GLuint mvLoc = glGetUniformLocation(m_programID, "ModelViewMatrix");
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, &modelViewMatrix[0][0]);
    GLuint pLoc = glGetUniformLocation(m_programID, "ProjectionMatrix");
    glUniformMatrix4fv(pLoc, 1, GL_FALSE, &projectionMatrix[0][0]);
    glm::mat4 normalMatrix = glm::transpose(glm::inverse(modelViewMatrix));
    GLuint nLoc = glGetUniformLocation(m_programID, "NormalMatrix");
    glUniformMatrix3fv(nLoc, 1, GL_FALSE, &normalMatrix[0][0]);
    GLuint lightPositionLoc = glGetUniformLocation(m_programID, "LightPosition");
    glm::vec4 lightEyePos = modelViewMatrix * glm::vec4(light.m_position.x, light.m_position.y, light.m_position.z, 1.0f);
    glUniform4f(lightPositionLoc, lightEyePos.x,lightEyePos.y, lightEyePos.z, lightEyePos.w);

    GLuint lightIntensityLoc = glGetUniformLocation(m_programID, "Ld");
    glUniform3f(lightIntensityLoc, light.m_intensity, light.m_intensity, light.m_intensity);
}

void DefaultShader::Use(MaterialPtr material) {
    GLuint materialReflectivityLoc = glGetUniformLocation(m_programID, "Kd");
    glUniform3f(materialReflectivityLoc, material->getDiffuseColour().r, material->getDiffuseColour().g,
                material->getDiffuseColour().b);
    Shader::Use(material);
}
