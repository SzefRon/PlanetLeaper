#pragma once

#include "glm/glm.hpp"
#include "glm/ext/scalar_constants.hpp"

class Camera
{
public:
    glm::vec2 position = {0, 0};
    float rotation = 0.0f, scale = 1.0f;

    float follow_speed = 2.0f;
    float rotation_speed = 2.0f;

    void follow(glm::vec2 follow_point, float dt);
    void adapt_rotation(float final_rotation, float dt);
};