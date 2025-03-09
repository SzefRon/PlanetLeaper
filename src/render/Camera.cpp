#include "render/Camera.hpp"

void Camera::follow(glm::vec2 follow_point, float dt)
{
    position += follow_speed * dt * (follow_point - position);
}

void Camera::adapt_rotation(float final_rotation, float dt)
{
    float delta_rotation = final_rotation - rotation;
    delta_rotation = glm::mod(delta_rotation + glm::pi<float>(), 2.0f * glm::pi<float>()) - glm::pi<float>();

    rotation += rotation_speed * dt * delta_rotation;
}
