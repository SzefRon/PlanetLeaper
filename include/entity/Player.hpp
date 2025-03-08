#pragma once

#include "glm/glm.hpp"

#include "entity/Entity.hpp"

class Player : public Entity
{
    BlockType render_condition(glm::vec2 pixel_pos) override;
};