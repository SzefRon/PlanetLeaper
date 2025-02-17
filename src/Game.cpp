#include "Game.hpp"

Game::Game()
    : renderer(128, 64)
{
    world.generate_planet({0, 0}, 40, BlockType::DIRT);
    world.generate_planet({0, 0}, 30, BlockType::STONE);
    camera.position = {64, 16};
}

void Game::run()
{
    auto last_time = std::chrono::high_resolution_clock::now();

    while (true) {

        auto current_time = std::chrono::high_resolution_clock::now();
        std::chrono::duration<float> delta_time = current_time - last_time;
        last_time = current_time;
        float dt = delta_time.count();

        renderer.render(world, camera);
        camera.rotation += dt * glm::pi<float>();

        float fps = 1.0f / dt;

        printf("%f", fps);
    }
}
