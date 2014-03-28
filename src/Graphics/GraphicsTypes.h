#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <memory>
#include <vector>

class Graphics;
class Material;
class RenderComponent;

struct Vertex
{
    float x;
    float y;
    float z;
};

struct TextureVertex
{
    float u;
    float v;
};

struct Face
{
    std::vector<short> vertexIndexes;
    std::vector<short> textureIndexes;
};

struct Colour
{
    float r;
    float g;
    float b;
};

typedef std::shared_ptr<RenderComponent> RenderComponentPtr;
typedef std::shared_ptr<Material>     MaterialPtr;
#endif