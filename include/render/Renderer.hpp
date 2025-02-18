#pragma once

#include <sstream>

#define GLM_FORCE_SSE42
#define GLM_FORCE_ALIGNED

#include "glm/glm.hpp"

#include "world/World.hpp"
#include "render/Camera.hpp"
#include "render/Colors.hpp"
#include "render/BlockRenderDetails.hpp"
#include "render/Pixel.hpp"

class Renderer
{
private:
    int size_x, size_y;
    float half_x, half_y;
    Pixel *screen = nullptr;
public:
    Renderer(unsigned int size_x, unsigned int size_y);

    void resize(unsigned int new_size_x, unsigned int new_size_y);
    void render(const World &world, const Camera &camera);

    void display();

    bool on_screen(int x, int y);
};