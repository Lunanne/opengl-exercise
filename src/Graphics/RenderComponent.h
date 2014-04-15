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
    RenderComponent(std::vector<Vertex> p_vertices, std::vector<TextureVertex> p_textureVertices, const std::string& p_materialName);
    ~RenderComponent();
    void Render();
    const int GetVertexCount() const;
    const std::string& GetMaterialName() const;
    void SetMaterial(MaterialPtr p_material);

private:
    GLuint                     m_vertexArrayID;
    GLuint                     m_vertexBufferID;
    GLuint                     m_textureBufferID;
    GLuint                     m_matrixID;
    GLuint                     m_programID;
    GLuint                     m_vertexShaderID;
    GLuint                     m_fragmentShaderID;
    GLuint                     m_texSamplerLoc;
    GLuint                     m_positionLoc;
    GLuint                     m_textureCoordsLoc;
    const GLchar*              m_vertexShader;
    const GLchar*              m_fragmentShader;
    glm::mat4                  m_mvpMatrix;
    bool                       m_vertexDataChanged;
    std::vector<Vertex>        m_vertices; //vertices in the right order to render(unindexed).
    std::vector<TextureVertex> m_textureVertices; //vertices in the right order to render(unindexed).
    std::string                m_materialName;
    MaterialPtr                m_material;

    void CreateVAO();
    void DestroyVAO();
    void CreateShaders();
    void DestroyShaders();
};

#endif