#include "world/World.hpp"

void World::generate_planet(glm::ivec2 center_pos, int radius, BlockType block_type)
{
    int r_sqr = radius * radius;
    Block block;
    block.block_type = block_type;
    for (int y = -radius; y <= radius; y++) {
        for (int x = -radius; x <= radius; x++) {
            if (x * x + y * y <= r_sqr) {
                glm::ivec2 pos = center_pos + glm::ivec2(x, y);
                world_grid[pos] = block;
            }
        }
    }
}
