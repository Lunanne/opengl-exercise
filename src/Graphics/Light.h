#ifndef OPENGL_EXERCISE_LIGHT_H
#define OPENGL_EXERCISE_LIGHT_H
#include <glm/glm.hpp>

struct Light {
    glm::vec3 m_position;
    float m_intensity;
};
#endif //OPENGL_EXERCISE_LIGHT_H
