#include "GraphicsObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
GraphicsObject::GraphicsObject(const GLuint &programID)
{
    CreateVBO();
    this->programID = programID;
    glm::mat4 projectionMatrix = glm::perspective(45.0f,4.0f/3.0f,0.1f,100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4,3,3),glm::vec3(0,0,0),glm::vec3(0,1,0));
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    mvpMatrix = projectionMatrix * viewMatrix*modelMatrix;
    matrixID = glGetUniformLocation(programID,"MVP");

}
GraphicsObject::~GraphicsObject()
{
    DestroyVBO();
}
void GraphicsObject::CreateVBO()
{
    glGenVertexArrays(1,&vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1,&vboID);
    glBindBuffer(GL_ARRAY_BUFFER,vboID);
    glBufferData(GL_ARRAY_BUFFER,sizeof(vertices),vertices,GL_STATIC_DRAW);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,0);
    glEnableVertexAttribArray(0);
}
void GraphicsObject::DestroyVBO()
{
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER,0);

    glDeleteBuffers(1,&vboID);

    glBindVertexArray(0);
    glDeleteVertexArrays(1,&vaoID);

}
void GraphicsObject::Render()
{
glUseProgram(programID);
    glUniformMatrix4fv(matrixID,1,GL_FALSE,&mvpMatrix[0][0]);
    glEnableVertexAttribArray(0);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,0,(void*)0 );
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glDisableVertexAttribArray(0);
}
