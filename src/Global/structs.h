#ifndef STRUCTS_H
#define STRUCTS_H

#include <vector>
#include <glm/glm.hpp>
#include <string>
struct faceStruct{
  
  glm::vec4* vertices[3];
  glm::vec3* normals[3];
  glm::vec3* texCoords[3];
};

struct objectStruct{
  
  std::string name;
  std::string material;
  std::vector<glm::vec4> vertices;
  std::vector<glm::vec3> normals;
  std::vector<glm::vec3> texCoords;
  std::vector<faceStruct> faces;
};


#endif