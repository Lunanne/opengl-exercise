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


RenderComponent::RenderComponent(const aiMesh* p_mesh, const aiMaterial* p_aiMaterial) :
m_shaderType(ShaderType_Default)
{

    for (unsigned int v = 0; v < p_mesh->mNumVertices; ++v)
    {
        const aiVector3D vert = p_mesh->mVertices[v];

        m_vertices.push_back(Vertex(vert.x, vert.y, vert.z));
       if (p_mesh->HasNormals())
        {
            const aiVector3D normal = p_mesh->mNormals[v];
            m_normalVertices.push_back(Vertex(normal.x, normal.y, normal.z));
        }
    }

    m_material = std::make_shared<Material>(p_aiMaterial);

}
RenderComponent::~RenderComponent()
{
    DestroyVAO();
}


void RenderComponent::CreateVAO()
{
    m_programId = ShaderManager::GetProgramID(m_shaderType);
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);


    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
    m_positionLoc = glGetAttribLocation(m_programId, "in_position");
    glVertexAttribPointer(m_positionLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

   glEnableVertexAttribArray(0);
    glBindVertexArray(0);

}



void RenderComponent::DestroyVAO()
{
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &m_vertexBufferID);
    glDeleteVertexArrays(1, &m_vertexArrayID);

    m_vertices.clear();
}
void RenderComponent::Render()
{
    if(!m_createdVao){
        CreateVAO();
        m_createdVao = true;
    }
    ShaderManager::UseShader(m_shaderType);
    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glEnableVertexAttribArray(m_positionLoc);

    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
}
