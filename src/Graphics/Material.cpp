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


Material::Material(const aiMaterial* p_material)
{
    aiColor4D diffColour(0.f, 0.f, 0.f, 0.f);
    p_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffColour);

    m_difColour = Colour(diffColour.r, diffColour.g, diffColour.b, diffColour.a);
}

