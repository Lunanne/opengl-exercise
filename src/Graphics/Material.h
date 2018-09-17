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
    Colour getDiffuseColour(){return m_difColour;}
    float getReflectivity(){return m_reflectivity;}
private:
    float m_reflectivity = .8f;
    Colour m_difColour;
};
#endif