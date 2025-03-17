#pragma once

#include "glm/glm.hpp"

#include "entity/Entity.hpp"
#include "input/InputManager.hpp"
#include "input/InputObserver.hpp"

class Player : public Entity, public InputObserver
{
private:
    float border_size = 1.0f;
    float jump_strength = 20.0f;
    bool buffer_jump = false;
public:
    Player();

    void update() override;

    BlockType render_condition(glm::vec2 pixel_pos) override;
    void on_input_change(Action action, bool state) override;

    void check_jump(bool key_state);
    void jump();
};