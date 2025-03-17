#pragma once

#include "glm/glm.hpp"

#include "world/BlockType.hpp"

class Entity
{
public:
    glm::vec2 pos = {0.0f, 0.0f};
    glm::vec2 next_pos = {0.0f, 0.0f};
    glm::vec2 velocity = {0.0f, 0.0f};
    glm::vec2 gravity = {0.0f, 0.0f};
    
    bool buffer_on_ground = false;
    bool on_ground = false;

    float collision_size = 1.0f;

    virtual BlockType render_condition(glm::vec2 pixel_pos) = 0;

    void update_next_pos(float dt);
    void update_pos();
    virtual void update() = 0;
};