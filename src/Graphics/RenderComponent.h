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

class RenderComponent
{
public:
    RenderComponent();
    ~RenderComponent();
    void Render();
    void AddVertCoord(GLfloat p_coordinate);
    void AddFaceIndex(GLushort p_faceIndex);
    const int GetVertexCount() const;

private:
    GLuint                     m_vboID;
    GLuint                     m_vaoID;
    GLuint                     m_matrixID;
    GLuint                     m_programID;
    GLuint                     m_indexBufferID;
    GLuint                     m_vertexShaderID;
    GLuint                     m_fragmentShaderID;
    const GLchar*              m_vertexShader;
    const GLchar*              m_fragmentShader;
    glm::mat4                  m_mvpMatrix;
    std::vector<GLfloat>       m_verticesCoords;
    std::vector<GLshort>       m_faceIndexes;
    bool                       m_vertexDataChanged;

    void CreateVBO();
    void DestroyVBO();
    void CreateShaders();
    void DestroyShaders();
};

#endif