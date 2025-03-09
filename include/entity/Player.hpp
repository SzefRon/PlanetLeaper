#pragma once

#include "glm/glm.hpp"

#include "entity/Entity.hpp"

class Player : public Entity
{
public:
    Player();
    BlockType render_condition(glm::vec2 pixel_pos) override;
};