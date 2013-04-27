#include "GraphicsObject.h"
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/transform.hpp>
#include "../Tools/objectfileparser.h"

GraphicsObject::GraphicsObject(const GLuint &programID)
{
	ObjectFileParser parser;
	parser.ParseObjFile(this);

    CreateVBO();
    this->programID = programID;
    glm::mat4 projectionMatrix = glm::perspective(60.0f,4.0f/3.0f,0.1f,100.0f);
    glm::mat4 viewMatrix = glm::lookAt(glm::vec3(4,3,3),glm::vec3(0,0,0),glm::vec3(0,1,0));
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    mvpMatrix = projectionMatrix * viewMatrix*modelMatrix;
    matrixID = glGetUniformLocation(programID,"MVP");

}
GraphicsObject::~GraphicsObject()
{
    DestroyVBO();
}

void GraphicsObject::SetName(std::string name)
{
	this->name = name;
}
void GraphicsObject::AddVertCoord(GLfloat coordinate)
{
	verticesCoords.push_back(coordinate);
}

void GraphicsObject::AddFaceIndex(GLushort faceIndex)
{
	faceIndexes.push_back(faceIndex);
}

void GraphicsObject::CreateVBO()
{
    glGenVertexArrays(1,&vaoID);
    glBindVertexArray(vaoID);

    glGenBuffers(1,&vboID);
    glBindBuffer(GL_ARRAY_BUFFER,vboID);
	glBufferData(GL_ARRAY_BUFFER,verticesCoords.size() * sizeof(GLfloat),verticesCoords.data(),GL_STATIC_DRAW);

    glGenBuffers(1,&indexBufferID);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferID);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER,faceIndexes.size() * sizeof(GLushort),faceIndexes.data(),GL_STATIC_DRAW);
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

   glBindBuffer(GL_ELEMENT_ARRAY_BUFFER,indexBufferID);

	glDrawElements(GL_LINE_STRIP,faceIndexes.size(),GL_UNSIGNED_SHORT,(void*)0);

    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
}
