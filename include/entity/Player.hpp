#pragma once

#include "glm/glm.hpp"

#include "entity/Entity.hpp"
#include "input/InputManager.hpp"
#include "input/InputObserver.hpp"
#include "lib/Math.hpp"

class Player : public Entity, public InputObserver
{
private:
    float border_size = 0.5f;

    float jump_strength = 10.0f;
    bool buffer_jump = false;

    float gravity_low = 0.5f, gravity_high = 1.0f;

    float speed = 10.0f;
    float lerp_move = 10.0f, lerp_stay = 5.0f, lerp_air = 2.5f;;
    float v_left = 0.0f, v_right = 0.0f;
public:
    Player();

    void update(float dt) override;

    BlockType render_condition(glm::vec2 pixel_pos) override;
    void on_input_change(Action action, bool state) override;

    void check_jump(bool key_state);
    void jump();
};