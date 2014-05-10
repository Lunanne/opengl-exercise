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

    Vertex()
    {
        x = y = z = 0;
    }

    Vertex(float p_x, float p_y, float p_z) :
        x(p_x),
        y(p_y),
        z(p_z)
    {
    }
};

struct TextureVertex
{
    float u;
    float v;

    TextureVertex()
    {
        u = v = 0;
    }

    TextureVertex(float p_u, float p_v) :
        u(p_u),
        v(p_v)
    {
    }
};

struct Face
{
    std::vector<short> vertexIndexes;
    std::vector<short> textureIndexes;
    std::vector<short> normalIndexes;
};

struct Colour
{
    float r;
    float g;
    float b;
    float a;

    Colour()
    {
        r = g = b = a = 0;
    }

    Colour(float p_r, float p_g, float p_b, float p_a) :
        r(p_r),
        g(p_g),
        b(p_b),
        a(p_a)
    {
    }

};

struct Image
{
    int width;
    int height;
    int bitDepth;
    int format;
    unsigned char* data;
};
typedef std::shared_ptr<RenderComponent> RenderComponentPtr;
typedef std::shared_ptr<Material>     MaterialPtr;
#endif