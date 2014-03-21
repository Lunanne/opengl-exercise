#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <memory>

class Graphics;
class RenderComponent;

struct Vertex
{
    float x;
    float y;
    float z;
};

struct Face
{
    short vertexIndex;
};
typedef std::shared_ptr<RenderComponent> RenderComponentPtr;
#endif