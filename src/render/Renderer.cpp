#include "render/Renderer.hpp"

Renderer::Renderer(unsigned int size_x, unsigned int size_y)
{
    resize(size_x, size_y);
}

void Renderer::resize(unsigned int new_size_x, unsigned int new_size_y)
{
    size_x = new_size_x;
    size_y = new_size_y;

    half_x = size_x * 0.5f;
    half_y = size_y * 0.5f;

    if (screen != nullptr) {
        delete[] screen;
    }
    screen = new Pixel[size_x * size_y];
}

void Renderer::render(const World &world, const Camera &camera)
{
    auto &world_grid = world.world_grid;

    glm::mat4 view(1.0f);
    view = glm::translate(view, {camera.position.x, camera.position.y, 0.0f});
    view = glm::scale(view, {camera.scale, camera.scale, 1.0f});
    view = glm::rotate(view, camera.rotation, {0.0f, 0.0f, 1.0f});
    view = glm::translate(view, {-half_x, -half_y, 0.0f});

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            glm::vec2 pos = view * glm::vec4(x, y, 0.0f, 1.0f);
            glm::ivec2 pos_sample = glm::floor(pos);

            BlockType block_type;

            if (world_grid.contains(pos_sample)) {
                block_type = world_grid.at(pos_sample).block_type;
            }
            else {
                block_type = BlockType::AIR;
            }

            for (auto &entity : world.entities) {
                BlockType entity_block_type = entity->render_condition(pos);
                if (entity_block_type != BlockType::AIR) {
                    block_type = entity_block_type;
                    break;
                }
            }

            auto &[block_char, block_color] = Render::block_render_details.at(block_type);
            
            int idx = y * size_x + x;
            screen[idx].ch = block_char;
            screen[idx].color = block_color;
        }
    }
}

bool Renderer::on_screen(int x, int y)
{
    if (x >= 0 && x < size_x &&
    y >= 0 && y < size_y) {
        return true;
    }
    return false;
}

void Renderer::display()
{
    std::string result;
    result.reserve(size_y * size_x * 11 + size_y);

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            int idx = y * size_x + x;
            auto &pixel = screen[idx];
            result += pixel.color;
            result.push_back(pixel.ch);
        }
        result.push_back('\n');
    }

    printf("\033[H%s", result.c_str());
}
