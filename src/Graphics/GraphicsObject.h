#ifndef GRAPHICSOBJ_H
#define GRAPHICSOBJ_H

#ifdef _WIN32
	#include <Windows.h>
#endif

#ifdef __APPLE__
	#include <OpenGL/gl.h>
#else
	#include <GL/gl.h>
#endif

#include <vector>
#include <string>

#include <glm/glm.hpp>
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