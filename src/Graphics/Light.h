#ifndef OPENGL_EXERCISE_LIGHT_H
#define OPENGL_EXERCISE_LIGHT_H
#include <glm/glm.hpp>
#include "GraphicsTypes.h"

struct Light {
    glm::vec3 m_position;
    Colour m_diffColour;
    Colour m_ambColour;
    Colour m_specColour;
};
#endif //OPENGL_EXERCISE_LIGHT_H
