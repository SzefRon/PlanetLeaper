#pragma once

#include <unordered_map>

#define GLM_ENABLE_EXPERIMENTAL
#include "glm/glm.hpp"
#include "glm/gtx/hash.hpp"

#include "Block.hpp"

class World
{
public:
    std::unordered_map<glm::ivec2, Block> world_grid;

    void generate_planet(glm::ivec2 center_pos, int radius, BlockType block_type);
};