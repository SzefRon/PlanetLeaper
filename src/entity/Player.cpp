#include "entity/Player.hpp"

Player::Player()
{
    collision_size = 3.0f;
}

BlockType Player::render_condition(glm::vec2 pixel_pos)
{
    if (glm::distance(pixel_pos, pos) <= collision_size) {
        if (glm::distance(pixel_pos, pos) <= collision_size - border_size) {
            return BlockType::PLAYER_INSIDE;
        }
        return BlockType::PLAYER_BORDER;
    }
    return BlockType::AIR;
}
