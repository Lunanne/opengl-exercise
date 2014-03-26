#ifndef __APPLE__
#include <GL/glew.h>
#endif

#ifdef __APPLE__
#include <OpenGL/gl3.h>
#include <OpenGL/glu.h>
#endif

#include <fstream>
#include <iostream>
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../Tools/objectfileparser.h"

#include "RenderComponent.h"

/*
#ifdef __APPLE__
#define glBindVertexArray		glBindVertexArrayAPPLE
#define glDeleteVertexArrays	glDeleteVertexArraysAPPLE
#define glGenVertexArrays  	glGenVertexArraysA
#endif*/

const GLchar* readFile(const char* p_fileName)
{
    GLchar* content;
    std::ifstream file(p_fileName, std::ios::in | std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        const int length = static_cast<int>(file.tellg());
        content = new char[length + 1];
        file.seekg(0, std::ios::beg);
        file.read(content, length);
        content[length] = '\0';

        return content;
    }
    else
    {
        std::printf("Can't open file at %s \n", p_fileName);
    }
    return "";
}

RenderComponent::RenderComponent(std::vector<Vertex> p_vertices, std::vector<TextureVertex> p_textureVertices) :
m_vertexDataChanged(true),
m_vertices(p_vertices),
m_textureVertices(p_textureVertices)
{
    CreateVAO();
    CreateShaders();
    glm::mat4 projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    m_matrixID = glGetUniformLocation(m_programID, "MVP");
}
RenderComponent::~RenderComponent()
{
    DestroyVAO();
    DestroyShaders();
}

void RenderComponent::CreateVAO()
{
    glGenVertexArrays(1, &m_vaoID);
    GLenum errCode;
    const GLubyte *errString;

    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error in RenderComponent: %s\n", errString);
    }
    glBindVertexArray(m_vaoID);

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);

    glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * 3 * sizeof(GLfloat), m_vertices.data(), GL_STATIC_DRAW);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glEnableVertexAttribArray(0);
    glBindVertexArray(0);
    m_vertexDataChanged = false;
}
void RenderComponent::DestroyVAO()
{
    glDisableVertexAttribArray(0);
    glDeleteVertexArrays(1, &m_vaoID);

    m_vertices.clear();
}
void RenderComponent::Render()
{
    glDisable(GL_CULL_FACE);

    //CreateVAO();

    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvpMatrix[0][0]);
    glUseProgram(m_programID);

    glBindVertexArray(m_vaoID);

    glDrawArrays(GL_POINTS, 0, m_vertices.size());

    glBindVertexArray(0);
}

void RenderComponent::CreateShaders()
{
    GLint result = GL_FALSE;
    int infoLogLength;

    m_vertexShader = readFile("./Resources/vertexShader.vert");
    m_fragmentShader = readFile("./Resources/fragmentShader.frag");

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