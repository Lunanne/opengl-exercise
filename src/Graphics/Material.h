#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include <GLFW\glfw3.h>
#include <gli\gli.hpp>
#include "GraphicsTypes.h"

class Material
{
public:
    void SetDiffuseColour(Colour p_colour);
    void SetDiffuseTexture(const std::string& p_fileName);
    void SetName(const std::string& p_name);
    const std::string& GetName() const;
    const GLuint GetTextureID() const;

private:
    std::string m_name;
    Colour m_difColour;
    gli::texture2D m_texture;
    GLuint m_textureID;
};
#endif