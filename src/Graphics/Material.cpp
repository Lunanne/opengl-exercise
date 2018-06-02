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


Material::Material(const aiMaterial* p_material)
{
    aiString texturepath;
    p_material->GetTexture(aiTextureType_DIFFUSE, 0, &texturepath);
    aiColor4D diffColour(0.f, 0.f, 0.f, 0.f);
    p_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffColour);

    SetDiffuseColour(Colour(diffColour.r, diffColour.g, diffColour.b, diffColour.a));
    SetDiffuseTexture(texturepath.C_Str());
}


Material::Material(const Colour p_diffColour, const std::string& p_fileName):
m_difColour(p_diffColour)
{
    SetDiffuseTexture(p_fileName);
}

void Material::SetDiffuseColour(const Colour p_colour)
{
    m_difColour = p_colour;
}

void Material::SetDiffuseTexture(const std::string& p_fileName)
{
    std::string filePath = "../Resources/" + p_fileName;
    m_image = FileReader::ReadPNG(filePath.c_str());

    glGenTextures(1, &m_textureID);
    glBindTexture(GL_TEXTURE_2D, m_textureID);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, m_image.width, m_image.height, 0, GL_RGBA, GL_UNSIGNED_BYTE, m_image.data);

    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameterf(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);


    GLenum errCode;
    const GLubyte *errString;
    if ((errCode = glGetError()) != GL_NO_ERROR) {
        errString = gluErrorString(errCode);
        fprintf(stderr, "OpenGL Error in Rendercomponent 1: %s\n", errString);
    }
}

const GLuint Material::GetTextureID()
{
    if (m_image.data == NULL)
    {
        SetDiffuseTexture("white.png");
    }
    return m_textureID;
}