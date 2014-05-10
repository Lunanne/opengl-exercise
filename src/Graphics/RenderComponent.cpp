#ifndef __APPLE__
#include <GL/glew.h>
#include <GL/GL.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#endif

#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../Tools/objectfileparser.h"
#include "../Tools/FileReader.h"

#include "Material.h"
#include "RenderComponent.h"


RenderComponent::RenderComponent(std::vector<Vertex> p_vertices, std::vector<TextureVertex> p_textureVertices, std::vector<Vertex> p_normalVertices) :
m_vertexDataChanged(true),
m_vertices(p_vertices),
m_textureVertices(p_textureVertices),
m_normalVertices(p_normalVertices)
{
    Init();
}

RenderComponent::RenderComponent(const aiMesh* p_mesh, const aiMaterial* p_aiMaterial)
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

    Init();

    m_material = MaterialPtr(new Material(p_aiMaterial));
}
RenderComponent::~RenderComponent()
{
    DestroyVAO();
    DestroyShaders();
}

void RenderComponent::Init()
{
    CreateShaders();
    CreateVAO();
    glm::mat4 projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.01f, 100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    m_matrixID = glGetUniformLocation(m_programID, "MVP");
    m_texSamplerLoc = glGetUniformLocation(m_programID, "texSampler");
}


void RenderComponent::CreateVAO()
{
    glGenVertexArrays(1, &m_vertexArrayID);
    glBindVertexArray(m_vertexArrayID);

    glGenBuffers(1, &m_vertexBufferID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
    m_positionLoc = glGetAttribLocation(m_programID, "in_position");
    glVertexAttribPointer(m_positionLoc, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    if (m_textureVertices.empty() == false)
    {
        glGenBuffers(1, &m_textureBufferID);
        glBindBuffer(GL_ARRAY_BUFFER, m_textureBufferID);
        glBufferData(GL_ARRAY_BUFFER, m_textureVertices.size() * 2 * sizeof(GLfloat), m_textureVertices.data(), GL_STATIC_DRAW);

        m_textureCoordsLoc = glGetAttribLocation(m_programID, "in_texCoords");
        glVertexAttribPointer(m_textureCoordsLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);
        glBindBuffer(GL_ARRAY_BUFFER, 0);
    }
    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    m_vertexDataChanged = false;
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
    glUseProgram(m_programID);
    //CreateVAO();

    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    glBindVertexArray(m_vertexArrayID);

    glBindBuffer(GL_ARRAY_BUFFER, m_vertexBufferID);
    glEnableVertexAttribArray(m_positionLoc);

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, m_material->GetTextureID());
    glUniform1i(m_texSamplerLoc, 0);

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
        
        m_textureCoordsLoc = glGetAttribLocation(m_programID, "in_texCoords");
        glVertexAttribPointer(m_textureCoordsLoc, 2, GL_FLOAT, GL_FALSE, 0, (void*)0);

    }

    glDrawArrays(GL_TRIANGLES, 0, m_vertices.size());
    glBindVertexArray(0);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void RenderComponent::CreateShaders()
{
    GLint result = GL_FALSE;
    int infoLogLength;

    m_vertexShader = FileReader::ReadFile("./Resources/vertexShader.vert");
    m_fragmentShader = FileReader::ReadFile("./Resources/fragmentShader.frag");

    m_vertexShaderID = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(m_vertexShaderID, 1, const_cast<const GLchar**>(&m_vertexShader), NULL);
    glCompileShader(m_vertexShaderID);

    glGetShaderiv(m_vertexShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderiv(m_vertexShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> VertexShaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(m_vertexShaderID, infoLogLength, NULL, &VertexShaderErrorMessage[0]);
        fprintf(stdout, "vertex shader error output: %s\n", &VertexShaderErrorMessage[0]);
    }

    m_fragmentShaderID = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(m_fragmentShaderID, 1, const_cast<const GLchar**>(&m_fragmentShader), NULL);
    glCompileShader(m_fragmentShaderID);

    glGetShaderiv(m_fragmentShaderID, GL_COMPILE_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetShaderiv(m_fragmentShaderID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> FragmentShaderErrorMessage(infoLogLength);
        glGetShaderInfoLog(m_fragmentShaderID, infoLogLength, NULL, &FragmentShaderErrorMessage[0]);
        fprintf(stdout, "fragment shader error output : %s\n", &FragmentShaderErrorMessage[0]);
    }

    m_programID = glCreateProgram();
    glAttachShader(m_programID, m_fragmentShaderID);
    glAttachShader(m_programID, m_vertexShaderID);
    glLinkProgram(m_programID);

    // Check the program
    glGetProgramiv(m_programID, GL_LINK_STATUS, &result);
    if (result == GL_FALSE)
    {
        glGetProgramiv(m_programID, GL_INFO_LOG_LENGTH, &infoLogLength);
        std::vector<char> ProgramErrorMessage(std::max(infoLogLength, int(1)));
        glGetProgramInfoLog(m_programID, infoLogLength, NULL, &ProgramErrorMessage[0]);
        fprintf(stdout, "program error output: %s\n", &ProgramErrorMessage[0]);
    }

    glUseProgram(m_programID);
}
void RenderComponent::DestroyShaders()
{
    glUseProgram(0);
    glDetachShader(m_programID, m_vertexShaderID);
    glDetachShader(m_programID, m_fragmentShaderID);

    glDeleteShader(m_fragmentShaderID);
    glDeleteShader(m_vertexShaderID);

    glDeleteProgram(m_programID);
    delete m_vertexShader;
    delete m_fragmentShader;
}

const int RenderComponent::GetVertexCount() const
{
    return m_vertices.size();
}

void RenderComponent::SetMaterial(MaterialPtr p_material)
{
    m_material = p_material;
}