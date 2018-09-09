#ifndef CAMERA_H
#define CAMERA_H

#include <glm/glm.hpp>

struct Camera {
    glm::vec3 m_lookAtVec;
    glm::vec3 m_position;
    glm::vec3 m_up;
    float m_viewAngle;
    float m_viewRatio;
    float m_nearDistance;
    float m_farDistance;
};

#endif