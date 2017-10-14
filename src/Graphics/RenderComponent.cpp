#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/gl.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#endif

#include <algorithm>

#include "../Tools/FileReader.h"

#include "ShaderManager.h"
#include "Material.h"
#include "RenderComponent.h"


RenderComponent::RenderComponent(std::vector<Vertex> p_vertices, std::vector<TextureVertex> p_textureVertices, std::vector<Vertex> p_normalVertices) :
m_vertices(p_vertices),
m_textureVertices(p_textureVertices),
m_normalVertices(p_normalVertices),
m_shaderType(ShaderType_Default)
{
    CreateVAO();
}

RenderComponent::RenderComponent(const aiMesh* p_mesh, const aiMaterial* p_aiMaterial) : 
m_shaderType(ShaderType_Default)
{
    
    for (unsigned int v = 0; v < p_mesh->mNumVertices; ++v)
    {
        const aiVector3D vert = p_mesh->mVertices[v];
        m_vertices.push_back(Vertex(vert.x, vert.y, vert.z));
        if (p_mesh->HasTextureCoords(0))
        {
            const aiVector3D textVert = p_mesh->mTextureCoords[0][v];
            m_textureVertices.push_back(TextureVertex(textVert.x, textVert.y));
        }
        if (p_mesh->HasNormals())
        {
            const aiVector3D normal = p_mesh->mNormals[v];
            m_normalVertices.push_back(Vertex(normal.x, normal.y, normal.z));
        }
    }
    m_material = MaterialPtr(new Material(p_aiMaterial));
    CreateVAO();
}
RenderComponent::~RenderComponent()
{
    DestroyVAO();
}


void RenderComponent::CreateVAO()
{
    const GLuint programID = ShaderManager::GetProgramID(m_shaderType);
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
    m_positionLoc = glGetAttribLocation(programID, "in_position");
    glVertexAttribPointer(m_positionLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (m_textureVertices.empty() == false)
    {
        glGenBuffers(1, &m_textureBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_textureVertices.size() * 2 * sizeof(GLfloat), m_textureVertices.data(), GL_STATIC_DRAW);

        m_textureCoordsLoc = glGetAttribLocation(programID, "in_texCoords");
        glVertexAttribPointer(m_textureCoordsLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
}
void RenderComponent::DestroyVAO()
{
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &m_vertexBufferID);
    if (m_textureVertices.empty() == false)
        glDeleteBuffers(1, &m_textureBufferID);
    glDeleteVertexArrays(1, &m_vertexArrayID);

    m_vertices.clear();
}
void RenderComponent::Render()
{
    ShaderManager::UseShader(m_shaderType);
    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glEnableVertexAttribArray(m_positionLoc);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_material->GetTextureID());
    
    if (m_textureVertices.empty() == false)
    {
        glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferID);
        glEnableVertexAttribArray(m_textureCoordsLoc);
    }
    else
    {
        TextureVertex tv;
        tv.u = 0;
        tv.v = 0;
        m_textureVertices.push_back(tv);
        glGenBuffers(1, &m_textureBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_textureVertices.size() * 2 * sizeof(GLfloat), m_textureVertices.data(), GL_STATIC_DRAW);
        
        m_textureCoordsLoc = glGetAttribLocation(ShaderManager::GetProgramID(m_shaderType), "in_texCoords");
        glVertexAttribPointer(m_textureCoordsLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    }

    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

const int RenderComponent::GetVertexCount() const
{
    return m_vertices.size();
}

void RenderComponent::SetMaterial(MaterialPtr p_material)
{
    m_material = p_material;
}