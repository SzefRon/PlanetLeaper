#pragma once

#include "glm/glm.hpp"

#include "entity/Entity.hpp"

class Player : public Entity
{
private:
    float border_size = 1.0f;
public:
    Player();
    BlockType render_condition(glm::vec2 pixel_pos) override;
};