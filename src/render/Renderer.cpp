#include "render/Renderer.hpp"

Renderer::Renderer(unsigned int size_x, unsigned int size_y)
{
    resize(size_x, size_y);
}

void Renderer::resize(unsigned int new_size_x, unsigned int new_size_y)
{
    if (view_pos_world != nullptr) {
        for (int i = 0; i < size_y; i++) {
            delete[] view_pos_world[i];
        }
        delete[] view_pos_world;
    }

    size_x = new_size_x;
    size_y = new_size_y;

    half_x = size_x * 0.5f;
    half_y = size_y * 0.5f;

    view_pos_world = new BlockType *[size_y];
    for (int i = 0; i < size_y; i++) {
        view_pos_world[i] = new BlockType[size_x];
    }
}

void Renderer::render(const World &world, const Camera &camera)
{
    auto &world_grid = world.world_grid;
    auto pixel_count = size_x * size_y;

    glm::mat4 view(1.0f);
    view = glm::translate(view, {half_x, half_y, 0.0f});
    view = glm::scale(view, {camera.scale, camera.scale, 1.0f});
    view = glm::rotate(view, camera.rotation, {0.0f, 0.0f, 1.0f});
    view = glm::translate(view, {-half_x, -half_y, 0.0f});
    view = glm::translate(view, {camera.position.x, camera.position.y, 0.0f});

    for (int y = 0; y < size_y; y++) {
        std::fill(view_pos_world[y], view_pos_world[y] + size_x, BlockType::AIR);
    }

    for (auto &[pos, block] : world_grid) {
        auto view_pos = view * glm::vec4(pos.x, pos.y, 0.0f, 1.0f);

        int f_x = glm::floor(view_pos.x);
        int f_y = glm::floor(view_pos.y);
        int r_x = glm::round(view_pos.x);
        int r_y = glm::round(view_pos.y);

        if (on_screen(f_x, f_y))
            view_pos_world[f_y][f_x] = block.block_type;
        if (on_screen(r_x, f_y))
            view_pos_world[f_y][r_x] = block.block_type;
        if (on_screen(f_x, r_y))
            view_pos_world[r_y][f_x] = block.block_type;
        if (on_screen(r_x, r_y))
            view_pos_world[r_y][r_x] = block.block_type;
    }

    std::string result;
    result.reserve(size_y * (size_x + 1) * 5);

    for (int y = 0; y < size_y; y++) {
        for (int x = 0; x < size_x; x++) {
            auto block_type = view_pos_world[y][x];
            auto &[block_char, block_color] = Render::block_render_details.at(block_type);
            result += block_color;
            result.push_back(block_char);
        }
        result.push_back('\n');
    }

    printf("\033[H%s", result.c_str());
}

bool Renderer::on_screen(int x, int y)
{
    if (x >= 0 && x < size_x &&
    y >= 0 && y < size_y) {
        return true;
    }
    return false;
}
