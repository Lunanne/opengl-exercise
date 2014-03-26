#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else
#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>
#endif

#include "Material.h"

void Material::SetDiffuseColour(Colour p_colour)
{
    m_difColour = p_colour;
}

void Material::SetDiffuseTexture(const std::string& p_fileName)
{
    std::string filePath = "./Resources/" + p_fileName;
    /* m_texture = gli::texture2D(gli::load_dds(filePath.c_str()));
     glBindTexture(GL_TEXTURE_2D, m_textureID);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_BASE_LEVEL, 0);
     glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAX_LEVEL, m_texture.levels() - 1);
     glTexStorage2D(GL_TEXTURE_2D, m_texture.levels(), m_texture.format(), m_texture.dimensions().x, m_texture.dimensions().y);
     if (gli::is_compressed(m_texture.format()))
     {
     for (gli::texture2D::size_type level = 0; level < m_texture.levels(); ++level)
     {
     glCompressedTexSubImage2D(GL_TEXTURE_2D,
     level,
     0,
     0,
     m_texture[level].dimensions().x,
     m_texture[level].dimensions().y,
     gli::externalFormat(m_texture.format()),
     m_texture[level].size(),
     m_texture[level].data());
     }
     }
     else
     {
     for (gli::texture2D::size_type level = 0; level < m_texture.levels(); ++level)
     {
     glTexSubImage2D(GL_TEXTURE_2D,
     level,
     0,
     0,
     m_texture[level].dimensions().x,
     m_texture[level].dimensions().y,
     gli::externalFormat(m_texture.format()),
     m_texture[level].size(),
     m_texture[level].data());
     }
     }*/
}

void Material::SetName(const std::string& p_name)
{
    m_name = p_name;
}

const std::string& Material::GetName() const
{
    return m_name;
}

const GLuint Material::GetTextureID() const
{
    return m_textureID;
}