#ifndef GRAPHICS_TYPES_H
#define GRAPHICS_TYPES_H

#include <memory>
#include <vector>

class Graphics;
class Material;
class RenderComponent;
class Shader;

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

enum ShaderType
{
    ShaderType_Default,
};

typedef std::shared_ptr<RenderComponent> RenderComponentPtr;
typedef std::shared_ptr<Material>        MaterialPtr;
#endif