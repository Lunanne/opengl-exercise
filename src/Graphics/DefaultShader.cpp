#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#define GLM_ENABLE_EXPERIMENTAL

#include <glm/gtx/transform.hpp>
#include <glm/ext.hpp>
#include <cstdio>
#include <iostream>

#include "DefaultShader.h"
#include "./GraphicsTypes.h"
#include "./Material.h"
#include "Light.h"

DefaultShader::DefaultShader(const char *p_vsFilePath, const char *p_fsFilePath, const Camera camera, const Light light)
        : Shader(
        p_vsFilePath, p_fsFilePath) {
    glm::mat4 projectionMatrix = glm::perspective(camera.m_viewAngle,
                                                  camera.m_viewRatio, camera.m_nearDistance,
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
    glm::vec4 lightEyePos =
            modelViewMatrix * glm::vec4(light.m_position.x, light.m_position.y, light.m_position.z, 1.0f);
    glUniform4f(lightPositionLoc, lightEyePos.x, lightEyePos.y, lightEyePos.z, lightEyePos.w);

    GLuint lightDiffuseLoc = glGetUniformLocation(m_programID, "LightIntensity");
    glUniform3f(lightDiffuseLoc, light.m_diffColour.r, light.m_diffColour.g, light.m_diffColour.b);


    GLuint fogMaxLoc = glGetUniformLocation(m_programID, "Fog.maxDist");
    glUniform1f(fogMaxLoc, 500.f);

    GLuint fogMinLoc = glGetUniformLocation(m_programID, "Fog.minDist");
    glUniform1f(fogMaxLoc, 8.f);

    GLuint fogColorLoc = glGetUniformLocation(m_programID, "Fog.color");
    glUniform3f(fogColorLoc, 0.0f, 0.0f, 0.0f);

}

void DefaultShader::Use(MaterialPtr material) {
    GLuint materialDiffuseLoc = glGetUniformLocation(m_programID, "Kd");
    glUniform3f(materialDiffuseLoc, material->getDiffuseColour().r, material->getDiffuseColour().g,
                material->getDiffuseColour().b);
    GLuint materialAmbientLoc = glGetUniformLocation(m_programID, "Ka");
    glUniform3f(materialAmbientLoc, material->getAmbientColour().r, material->getAmbientColour().g,
                material->getAmbientColour().b);
    GLuint materialSpecular = glGetUniformLocation(m_programID, "Ks");
    glUniform3f(materialSpecular, material->getSpecularColour().r, material->getSpecularColour().g,
                material->getSpecularColour().b);
    GLuint materialShininess = glGetUniformLocation(m_programID, "Shininess");
    glUniform1f(materialShininess,material->getShininess());


    Shader::Use(material);
}


