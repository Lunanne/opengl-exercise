#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include <GLFW/glfw3.h>
#include <assimp/scene.h>

#include "GraphicsTypes.h"

class Material
{
public:
    Material(const aiMaterial* p_material);

private:
    Colour m_difColour;
};
#endif