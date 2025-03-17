#include "entity/Player.hpp"

Player::Player()
{
    collision_size = 3.0f;
    InputManager::subscribe(this);
}

void Player::update(float dt)
{
    if (on_ground && buffer_jump) {
        jump();
    }

    float v_final = (v_left + v_right) * speed;
    float lerp_coeff = v_final == 0.0f ? lerp_stay : lerp_move;

    glm::vec2 v_rotated = Math::get_in_new_system(velocity, gravity);

    float v_follow = glm::mix(v_rotated.x, v_final, lerp_coeff * dt);
    v_rotated.x = v_follow;

    glm::vec2 v_unrotated = Math::get_in_new_system(v_rotated, gravity);
    velocity = v_unrotated;
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
        case Action::MOVE_LEFT:
            v_left = 1.0f * (float)state;
            break;
        case Action::MOVE_RIGHT:
            v_right = -1.0f * (float)state;
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
