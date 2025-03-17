#include "entity/Player.hpp"

Player::Player()
{
    collision_size = 3.0f;
    InputManager::subscribe(this);
}

void Player::update()
{
    if (on_ground && buffer_jump) {
        jump();
    }
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
        case Action::JUMP:
            check_jump(state);
            break;
    }
}

void Player::check_jump(bool key_state)
{
    if (key_state && !on_ground) buffer_jump = true;
    if (!key_state) {
        buffer_jump = false;
        return;
    }
    if (!on_ground)
        return;
    jump();
}

void Player::jump()
{
    buffer_jump = false;
    glm::vec2 jump_dir = -glm::normalize(gravity);
    velocity += jump_strength * jump_dir;
}
