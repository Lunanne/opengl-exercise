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
    RenderComponent(std::vector<Vertex> p_vertices, std::vector<TextureVertex> p_textureVertices, std::vector<Vertex> p_normalVertices);
    RenderComponent(const aiMesh* p_mesh, const aiMaterial* p_aiMaterial);
    ~RenderComponent();
    void Render();
    const int GetVertexCount() const;
    void SetMaterial(MaterialPtr p_material);

private:
    GLuint                     m_vertexArrayID;
    GLuint                     m_vertexBufferID;
    GLuint                     m_textureBufferID;
    GLuint                     m_positionLoc;
    GLuint                     m_textureCoordsLoc;
    glm::mat4                  m_mvpMatrix;
    std::vector<Vertex>        m_vertices; //vertices in the right order to render(unindexed).
    std::vector<Vertex>        m_normalVertices; //normal vertices in right order.
    std::vector<TextureVertex> m_textureVertices; //vertices in the right order to render(unindexed).
    MaterialPtr                m_material;
    ShaderType                 m_shaderType;

    void CreateVAO();
    void DestroyVAO();
};

#endif