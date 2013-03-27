#include <vector>
#include <QString>
#include <glm/glm.hpp>
#include "../Global/structs.h"
class GraphicsObject{
  
private:
QString name;
QString material;
std::vector<glm::vec4> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> texCoords;
 std::vector<faceStruct> faces;
 
public:
  GraphicsObject(){};
 GraphicsObject(const objectStruct &object);
 void Render();
 void SetValues(const objectStruct &object);
 const std::vector<glm::vec4> GetVertices();
 
};