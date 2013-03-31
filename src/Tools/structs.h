
#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
#include <GL/gl.h>
struct objectStruct{
  
  std::string name;
  std::string material;
  std::vector<GLfloat> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> texCoords;
  std::vector<GLshort> faces;
};


#endif
