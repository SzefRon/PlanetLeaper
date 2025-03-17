#pragma once

#include <chrono>

#include "world/World.hpp"
#include "render/Renderer.hpp"
#include "entity/Player.hpp"
#include "input/InputManager.hpp"

class Game
{
private:
    World world;
    Renderer renderer;
    Camera camera;
    Player player;
public:
    Game();
    void run();
};