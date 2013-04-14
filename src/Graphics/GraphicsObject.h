#ifndef GRAPHICSOBJ_H
#define GRAPHICSOBJ_H

#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <GL/gl.h>

class GraphicsObject
{

private:
	GLuint vboID;
    GLuint vaoID;
    GLuint matrixID;
    GLuint programID;
    GLuint colourBufferID;
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