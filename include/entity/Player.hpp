#pragma once

#include "glm/glm.hpp"

#include "entity/Entity.hpp"
#include "input/InputManager.hpp"
#include "input/InputObserver.hpp"

class Player : public Entity, public InputObserver
{
private:
    float border_size = 1.0f;
public:
    Player();
    BlockType render_condition(glm::vec2 pixel_pos) override;
    void on_input_change(Action action, bool state) override;
};