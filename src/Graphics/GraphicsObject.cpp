#include "GraphicsObject.h"

GraphicsObject::GraphicsObject(const objectStruct &object)
{
  name = object.name;
  material = object.material;
  vertices = object.vertices;
  normals = object.normals;
  texCoords = object.texCoords;
  faces = object.faces;
  
}
void GraphicsObject::SetValues(const objectStruct &object)
{
  name = object.name;
  material = object.material;
  vertices = object.vertices;
  normals = object.normals;
  texCoords = object.texCoords;
  faces = object.faces;
  
}

const std::vector<glm::vec4> GraphicsObject::GetVertices()
{
  return vertices;
}