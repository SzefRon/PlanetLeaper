#include "entity/Player.hpp"

BlockType Player::render_condition(glm::vec2 pixel_pos)
{
    if (glm::distance(pixel_pos, pos) <= 1.0f)
        return BlockType::CORE;
    return BlockType::AIR;
}
