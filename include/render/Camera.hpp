#pragma once

#include "glm/glm.hpp"

class Camera
{
public:
    glm::vec2 position = {0, 0};
    float rotation = 0.0f, scale = 1.0f;
};