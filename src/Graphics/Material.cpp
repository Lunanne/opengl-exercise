#ifdef __APPLE__
#include <OpenGL/gl.h>
#include <OpenGL/glu.h>
#else

#include <GL/glew.h>
#include <GL/gl.h>
#include <GL/glu.h>

#endif

#include <stdlib.h>
#include <assimp/types.h>


#include "../Tools/FileReader.h"
#include "Material.h"


Material::Material(const aiMaterial *p_material) {
    aiColor4D diffColour(0.f, 0.f, 0.f, 0.f);
    p_material->Get(AI_MATKEY_COLOR_DIFFUSE, diffColour);
    m_difColour = Colour(diffColour.r, diffColour.g, diffColour.b, diffColour.a);

    aiColor4D ambientColour(0.f, 0.f, 0.f, 0.f);
    p_material->Get(AI_MATKEY_COLOR_AMBIENT, ambientColour);
    m_ambientColour = Colour(ambientColour.r, ambientColour.g, ambientColour.b, ambientColour.a);

    aiColor4D specColour(0.f, 0.f, 0.f, 0.f);
    p_material->Get(AI_MATKEY_COLOR_SPECULAR, specColour);
    m_specularColour = Colour(specColour.r, specColour.g, specColour.b, specColour.a);

    ai_real shininess;
    p_material->Get(AI_MATKEY_SHININESS, shininess);
    m_shininess = shininess/10.f;
}
