#pragma once

#include <chrono>

#include "world/World.hpp"
#include "render/Renderer.hpp"

class Game
{
private:
    World world;
    Renderer renderer;
    Camera camera;
public:
    Game();
    void run();
};