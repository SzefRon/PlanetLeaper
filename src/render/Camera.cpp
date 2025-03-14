#include "render/Camera.hpp"

void Camera::follow(glm::vec2 follow_point, float dt)
{
    glm::vec2 diff = follow_point - position;
    float diff_len = glm::length(diff);

    glm::vec2 diff_norm = glm::vec2(0.0f);
    if (diff_len != 0.0f)
        diff_norm = glm::normalize(diff);

    float adjusted_follow_speed = follow_speed * diff_len;
    position += adjusted_follow_speed * dt * diff_norm;
}

void Camera::adapt_rotation(float final_rotation, float dt)
{
    float delta_rotation = final_rotation - rotation;
    delta_rotation = glm::mod(delta_rotation + glm::pi<float>(), 2.0f * glm::pi<float>()) - glm::pi<float>();

    rotation += rotation_speed * dt * delta_rotation;
}
