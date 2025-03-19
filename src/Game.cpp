#include "Game.hpp"

Game::Game()
    : renderer(200, 100)
{
    InputManager::initialize();

    // world.generate_planet({0, 0}, 100, BlockType::GRASS);
    // world.generate_planet({0, 0}, 98, BlockType::DIRT);
    
    world.generate_planet({0, 0}, 8, BlockType::STONE);
    world.generate_planet({0, 0}, 3, BlockType::CORE);
    // world.world_grid.insert({{-1, -17}, Block(BlockType::STONE)});
    // world.world_grid.insert({{0, -17}, Block(BlockType::STONE)});
    // world.world_grid.insert({{1, -17}, Block(BlockType::STONE)});

    world.generate_planet({-20, -20}, 8, BlockType::STONE);
    world.generate_planet({-20, -20}, 3, BlockType::CORE);

    world.entities.insert(&player);

    camera.position = {0.5f, -12.5f};
    camera.scale = 0.25f;

    player.pos = {0.5f, -12.5f};
    player.velocity = {0.0f, 0.0f};
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
        dt = glm::clamp(dt, 0.0f, 1.0f / 60.0f);
        t += dt;

        InputManager::update();

        world.update(dt);

        camera.follow(player.pos, dt);

        if (glm::length(player.gravity) != 0.0f) {
            float angle = glm::atan(player.gravity.y, player.gravity.x) - glm::half_pi<float>();
            camera.adapt_rotation(angle, dt);
        }

        renderer.render(world, camera);
        renderer.display();

        float fps = 1.0f / dt;
        printf("\n\033[38;5;255m%f %d %f            ", fps, (int)player.on_ground, player.gravity_multiplier);
    }
}
