#pragma once

#include <sstream>

#include "world/World.hpp"
#include "render/Camera.hpp"
#include "render/Colors.hpp"
#include "render/BlockRenderDetails.hpp"

class Renderer
{
private:
    unsigned int size_x, size_y;
    float half_x, half_y;
    BlockType **view_pos_world = nullptr;
public:
    Renderer(unsigned int size_x, unsigned int size_y);

    void resize(unsigned int new_size_x, unsigned int new_size_y);
    void render(const World &world, const Camera &camera);
    bool on_screen(int x, int y);
};