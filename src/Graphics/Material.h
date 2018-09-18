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
    Colour getSpecularColour(){return m_specularColour;}
    Colour getAmbientColour(){return m_ambientColour;}
    float getShininess(){return m_shininess;}
private:
    Colour m_difColour;
    Colour m_ambientColour ;
    Colour m_specularColour;
    float m_shininess;
};
#endif