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
#include <assimp/mesh.h>
#include <assimp/material.h>


#include <glm/glm.hpp>

#include "GraphicsTypes.h"

class RenderComponent
{
public:
    RenderComponent(const aiMesh* p_mesh, const aiMaterial* p_aiMaterial);
    ~RenderComponent();
    void Render();

private:
    GLuint                     m_vertexArrayID;
    GLuint                     m_vertexBufferID;
    GLuint                     m_positionLoc;
    GLuint                     m_programId;
    GLint m_transformVertex;
    std::vector<Vertex>        m_vertices; //vertices in the right order to render(unindexed).
    std::vector<Vertex>        m_normalVertices; //normal vertices in right order.
    MaterialPtr                m_material;
    ShaderType                 m_shaderType;
    bool                       m_createdVao = false;

    void CreateVAO();
    void DestroyVAO();
};

#endif