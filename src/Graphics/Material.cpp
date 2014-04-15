#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include <stdlib.h>
#include "../Tools/FileReader.h"
#include "Material.h"

Material::~Material()
{
    glDeleteTextures(1, &m_textureID);

    if (m_image.data != NULL)
        free(m_image.data);
}

Material::Material() :
m_difColour(Colour()),
m_image()
{
    m_image.data = NULL;
}

void Material::SetDiffuseColour(Colour p_colour)
{
    m_difColour = p_colour;
}

void Material::SetDiffuseTexture(const std::string& p_fileName)
{
    std::string filePath = "./Resources/" + p_fileName;
    m_image = FileReader::ReadPNG(filePath.c_str());
    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, m_image.format, m_image.width, m_image.height, 0, m_image.format, GL_UNSIGNED_BYTE, m_image.data);
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
    if (m_image.data == NULL)
    {
        SetDiffuseTexture("white.png");
    }
    return m_textureID;
}