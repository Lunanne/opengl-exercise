#include <vector>
#include <glm/glm.hpp>
#include <string>
class GraphicsObject{
  
private:
std::string name;
std::string material;
std::vector<glm::vec4> vertices;
std::vector<glm::vec3> normals;
std::vector<glm::vec3> texCoords;
std::vector<GLfloat> faces;
 
public:
  GraphicsObject();
 void Render();
 const std::vector<glm::vec4> GetVertices();
 
};