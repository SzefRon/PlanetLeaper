#include "entity/Player.hpp"

Player::Player()
{
    collision_size = 3.0f;
    InputManager::subscribe(this);
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

void Player::on_input_change(Action action, bool state)
{
    switch(action) {
        case Action::JUMP: {
            velocity.y = state ? -10.0f : velocity.y;
        }
    }
}
