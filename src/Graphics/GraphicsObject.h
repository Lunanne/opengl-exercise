#ifndef GRAPHICSOBJ_H
#define GRAPHICSOBJ_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#ifdef __APPLE__
#include <OpenGL/gl.h>
#else
#include <GL/gl.h>
#endif
class GraphicsObject
{

private:
	GLuint vboID;
    GLuint vaoID;
    GLuint matrixID;
    GLuint programID;
    GLuint indexBufferID;
    glm::mat4 mvpMatrix;
	std::string name;
	std::vector<GLfloat> verticesCoords;
	std::vector<GLshort> faceIndexes;
    void CreateVBO();
    void DestroyVBO();
	
public:
	GraphicsObject();
    GraphicsObject(const GLuint &programID);
    ~GraphicsObject();
    void Render();
	void SetName(std::string name);
	void AddVertCoord(GLfloat coordinate);
	void AddFaceIndex(GLushort faceIndex);

};

#endif