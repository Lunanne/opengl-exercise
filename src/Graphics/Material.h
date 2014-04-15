#ifndef MATERIAL_H
#define MATERIAL_H

#include <string>

#include <GLFW/glfw3.h>
#include "GraphicsTypes.h"

class Material
{
public:
    Material();
    ~Material();
    void SetDiffuseColour(Colour p_colour);
    void SetDiffuseTexture(const std::string& p_fileName);
    void SetName(const std::string& p_name);
    const std::string& GetName() const;
    const GLuint GetTextureID();

private:
    std::string m_name;
    Colour m_difColour;
    GLuint m_textureID;
    Image m_image;
};
#endif