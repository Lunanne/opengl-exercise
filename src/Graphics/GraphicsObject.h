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
    void CreateVBO();
    void DestroyVBO();
public:
    GraphicsObject(const GLuint &programID);
    ~GraphicsObject();
    void Render();


};
