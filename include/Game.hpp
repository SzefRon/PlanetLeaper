#pragma once

#include <chrono>

#include "world/World.hpp"
#include "render/Renderer.hpp"
#include "entity/Player.hpp"

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