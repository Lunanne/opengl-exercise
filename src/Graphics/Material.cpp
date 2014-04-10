#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <SOIL.h>
#include "Material.h"

Material::~Material()
{
    glDeleteTextures(1, &m_textureID);

    if (m_image != NULL)
        SOIL_free_image_data(m_image);
}

Material::Material() :
m_image(NULL),
m_difColour(Colour())
{
}

void Material::SetDiffuseColour(Colour p_colour)
{
    m_difColour = p_colour;
}

void Material::SetDiffuseTexture(const std::string& p_fileName)
{
    std::string filePath = "./Resources/" + p_fileName;
    int width;
    int height;
    int channels;
    m_image = SOIL_load_image(filePath.c_str(), &width, &height, &channels, SOIL_LOAD_AUTO);
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
}

void Material::SetName(const std::string& p_name)
{
    m_name = p_name;
}

const std::string& Material::GetName() const
{
    return m_name;
}

const GLuint Material::GetTextureID()
{
    if (m_image == NULL)
    {
        SetDiffuseTexture("white.png");
    }
    return m_textureID;
}