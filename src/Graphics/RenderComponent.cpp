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


RenderComponent::RenderComponent(const aiMesh *p_mesh, const aiMaterial *p_aiMaterial) :
        m_shaderType(ShaderType_Default) {

    for (unsigned int v = 0; v < p_mesh->mNumVertices; ++v) {
        const aiVector3D vert = p_mesh->mVertices[v];

        m_vertices.push_back(Vertex(vert.x, vert.y, vert.z));
        if (p_mesh->HasNormals()) {
            const aiVector3D normal = p_mesh->mNormals[v];
            m_normalVertices.push_back(Vertex(normal.x, normal.y, normal.z));
//            printf("vertex %d %f %f %f\n", v, vert.x,vert.y,vert.z);
//            printf("normal %d %f %f %f\n",v, normal.x,normal.y,normal.z);
        }
        if (p_mesh->HasTextureCoords(0))
        {
            const aiVector3D textVert = p_mesh->mTextureCoords[0][v];
            m_textureVertices.push_back(TextureVertex(textVert.x, textVert.y));
//            printf("texture %d %f %f \n", v, textVert.x,textVert.y);
        }

    }

    m_material = std::make_shared<Material>(p_aiMaterial);

}

RenderComponent::~RenderComponent() {
    DestroyVAO();
}


void RenderComponent::CreateVAO() {
    m_programId = ShaderManager::GetProgramID(m_shaderType);

    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);


    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
    m_positionLoc = glGetAttribLocation(m_programId, "VertexPosition");
    glEnableVertexAttribArray(m_positionLoc);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glVertexAttribPointer(m_positionLoc, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

    glGenBuffers(1, &m_normalBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_normalVertices.size() * 3 * sizeof(GLfloat), m_normalVertices.data(),
                 GL_STATIC_DRAW);
    m_normalLoc = 1;// glGetAttribLocation(m_programId, "VertexNormal");
    glEnableVertexAttribArray(m_normalLoc);
    glBindBuffer(GL_ARRAY_BUFFER, m_normalBufferID);
    glVertexAttribPointer(m_normalLoc, 3, GL_FLOAT, GL_FALSE, 0, (void *) 0);

//    glGenBuffers(1, &m_textureBufferID);
//    glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferID);
//    glBufferData(GL_ARRAY_BUFFER, m_textureVertices.size() * 2 * sizeof(GLfloat), m_textureVertices.data(), GL_STATIC_DRAW);
//    m_textureCoordsLoc = glGetAttribLocation(m_programId, "VertexTexCoord");
//    glEnableVertexAttribArray(m_textureCoordsLoc);
//    glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferID);
//    glVertexAttribPointer(m_textureCoordsLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindVertexArray(0);
}


void RenderComponent::DestroyVAO() {
    glDisableVertexAttribArray(0);
    glDeleteBuffers(1, &m_vertexBufferID);
    glDeleteVertexArrays(1, &m_vertexArrayID);
    glDeleteBuffers(1, &m_normalBufferID);
    glDeleteBuffers(1, &m_textureBufferID);

    m_vertices.clear();
    m_normalVertices.clear();
}
void RenderComponent::Render(Vertex physicsTransform)
{
    if(!m_createdVao){
        CreateVAO();
        m_createdVao = true;
    }
    ShaderManager::UseShader(m_shaderType, m_material);

    glm::vec3 v(physicsTransform.x, physicsTransform.y, physicsTransform.z);
    fprintf(stdout,"%f %f %f \n", v.x, v.y, v.z);

    m_transformVertex= glGetUniformLocation(m_programId, "transform_position");
    glUniform3fv(m_transformVertex, 1, &v[0]);

  glDisable(GL_CULL_FACE);
    glFrontFace(GL_CW);
    glBindVertexArray(m_vertexArrayID);
    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
}
