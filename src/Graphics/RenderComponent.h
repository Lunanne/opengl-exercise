#ifndef RENDERCOMPONENT_H
#define RENDERCOMPONENT_H

#ifdef _WIN32
#include <Windows.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#include <vector>
#include <string>

#include <glm/glm.hpp>

#include "GraphicsTypes.h"

class RenderComponent
{
public:
    RenderComponent(std::vector<Vertex> p_vertices);
    ~RenderComponent();
    void Render();
    const int GetVertexCount() const;

private:
    GLuint                     m_vboID;
    GLuint                     m_vaoID;
    GLuint                     m_matrixID;
    GLuint                     m_programID;
    GLuint                     m_vertexShaderID;
    GLuint                     m_fragmentShaderID;
    const GLchar*              m_vertexShader;
    const GLchar*              m_fragmentShader;
    glm::mat4                  m_mvpMatrix;
    std::vector<Vertex>        m_verticesCoords;
    bool                       m_vertexDataChanged;

    void CreateVAO();
    void DestroyVAO();
    void CreateShaders();
    void DestroyShaders();
};

#endif