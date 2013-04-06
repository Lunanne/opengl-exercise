#include <vector>
#include <GL/glew.h>
#include <glm/glm.hpp>
#include <string>
#include <GL/gl.h>
class GraphicsObject
{

private:
    const GLfloat vertices[9] =
    {
        -1.0f, -1.0f, 0.0f,
        1.0f, -1.0f, 0.0f,
        0.0f,  1.0f, 0.0f,
    };
    GLuint vboID;
    GLuint vaoID;
    GLuint matrixID;
    GLuint programID;
    glm::mat4 mvpMatrix;
    void CreateVBO();
    void DestroyVBO();
public:
    GraphicsObject(const GLuint &programID);
    ~GraphicsObject();
    void Render();


};
