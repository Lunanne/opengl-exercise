#ifndef OPENGL_EXERCISE_LIGHT_H
#define OPENGL_EXERCISE_LIGHT_H
#include <glm/glm.hpp>
#include "GraphicsTypes.h"

struct Light {
    glm::vec3 m_position;
    Colour m_diffColour;
    glm::vec3 m_direction;
    float m_exponent;
    float m_cutoff;
};
#endif //OPENGL_EXERCISE_LIGHT_H
