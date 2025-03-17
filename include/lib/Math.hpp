#pragma once

#include "glm/glm.hpp"

namespace Math
{
    /// @return Rotated `vec` based on axis created by `axis`
    inline glm::vec2 get_in_new_system(glm::vec2 vec, glm::vec2 axis)
    {
        glm::vec2 axis_y = glm::normalize(axis);
        glm::vec2 axis_x = glm::normalize(glm::vec2(-axis.y, axis.x));

        return {glm::dot(vec, axis_x), glm::dot(vec, axis_y)};
    }
}