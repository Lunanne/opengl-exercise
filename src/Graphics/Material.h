#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include <GLFW/glfw3.h>
#include <assimp/scene.h>

#include "GraphicsTypes.h"

class Material
{
public:
    Material();
    Material(const aiMaterial* p_material);
    Material(const Colour p_diffColour, const std::string& p_fileName);
    ~Material();
    void SetDiffuseColour(const Colour p_colour);
    void SetDiffuseTexture(const std::string& p_fileName);
    const GLuint GetTextureID();

private:
    Colour m_difColour;
    GLuint m_textureID;
    Image m_image;
};
#endif