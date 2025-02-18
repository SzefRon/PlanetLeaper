#include "Game.hpp"

Game::Game()
    : renderer(96, 48)
{
    world.generate_planet({0, 0}, 100, BlockType::GRASS);
    world.generate_planet({0, 0}, 98, BlockType::DIRT);
    world.generate_planet({0, 0}, 90, BlockType::STONE);
    world.generate_planet({0, 0}, 10, BlockType::CORE);

    camera.position = {0, -90};
    camera.scale = 1.0f;

    printf("\033[?25l");
}

void Game::run()
{
    auto last_time = std::chrono::high_resolution_clock::now();
    float t = 0.0f;

    while (true) {

        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta_time = current_time - last_time;
        last_time = current_time;
        float dt = delta_time.count();
        t += dt;

        renderer.render(world, camera);

        renderer.display();

        float fps = 1.0f / dt;
        printf("\n\033[38;5;255m%f %zu            ", fps, world.world_grid.size());
    }
}
