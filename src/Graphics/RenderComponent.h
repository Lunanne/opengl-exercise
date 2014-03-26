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
    RenderComponent(std::vector<Vertex> p_vertices, std::vector<TextureVertex> p_textureVertices);
    ~RenderComponent();
    void Render();
    const int GetVertexCount() const;

private:
    GLuint                     m_vaoID;
    GLuint                     m_vboID;
    GLuint                     m_texvaoID;
    GLuint                     m_matrixID;
    GLuint                     m_programID;
    GLuint                     m_vertexShaderID;
    GLuint                     m_fragmentShaderID;
    const GLchar*              m_vertexShader;
    const GLchar*              m_fragmentShader;
    glm::mat4                  m_mvpMatrix;
    bool                       m_vertexDataChanged;
    std::vector<Vertex>        m_vertices; //vertices in the right order to render(unindexed).
    std::vector<TextureVertex>        m_textureVertices; //vertices in the right order to render(unindexed).

    void CreateVAO();
    void DestroyVAO();
    void CreateShaders();
    void DestroyShaders();
};

#endif