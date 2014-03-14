#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <fstream>
#include <iostream>
#include <algorithm>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>

#include "../Tools/objectfileparser.h"

#include "RenderComponent.h"

#ifdef __APPLE__
#define glBindVertexArray		glBindVertexArrayAPPLE
#define glDeleteVertexArrays	glDeleteVertexArraysAPPLE
#define glGenVertexArrays  	glGenVertexArraysAPPLE
#endif

GLchar* readFile(const char* p_fileName)
{
    GLchar* content = "";
    std::ifstream file(p_fileName, std::ios::in | std::ios::binary);
    if (file)
    {
        file.seekg(0, std::ios::end);
        const int length = file.tellg();
        content = new char[length + 1];
        file.seekg(0, std::ios::beg);
        file.read(content, length);
        content[length] = '\0';
    }
    else
    {
        std::printf("Can't open file at %s \n", p_fileName);
    }
    return content;
}

RenderComponent::RenderComponent()
{
    CreateShaders();
    CreateVBO();
    glm::mat4 projectionMatrix = glm::perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4, 3, 3), glm::vec3(0, 0, 0), glm::vec3(0, 1, 0));
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    m_mvpMatrix = projectionMatrix * viewMatrix * modelMatrix;
    m_matrixID = glGetUniformLocation(m_programID, "MVP");
}
RenderComponent::~RenderComponent()
{
    DestroyVBO();
}

void RenderComponent::AddVertCoord(GLfloat coordinate)
{
    m_verticesCoords.push_back(coordinate);
}

void RenderComponent::AddFaceIndex(GLushort faceIndex)
{
    m_faceIndexes.push_back(faceIndex);
}

void RenderComponent::CreateVBO()
{
    glGenVertexArrays(1, &m_vaoID);
    glBindVertexArray(m_vaoID);

    glGenBuffers(1, &m_vboID);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glBufferData(GL_ARRAY_BUFFER, m_verticesCoords.size() * sizeof(GLfloat), m_verticesCoords.data(), GL_STATIC_DRAW);

    glGenBuffers(1, &m_indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_faceIndexes.size() * sizeof(GLushort), m_faceIndexes.data(), GL_STATIC_DRAW);
}
void RenderComponent::DestroyVBO()
{
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);

    glDeleteBuffers(1, &m_vboID);

    glBindVertexArray(0);
    glDeleteVertexArrays(1, &m_vaoID);
}
void RenderComponent::Render()
{
    glUseProgram(m_programID);

    glUniformMatrix4fv(m_matrixID, 1, GL_FALSE, &m_mvpMatrix[0][0]);

    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, m_vboID);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, (void*)0);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_indexBufferID);

    glDrawElements(GL_LINE_STRIP, m_faceIndexes.size(), GL_UNSIGNED_SHORT, (void*)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
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