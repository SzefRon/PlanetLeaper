#pragma once

#include "glm/glm.hpp"

#include "world/BlockType.hpp"

struct Block
{
public:
    Block() = default;
    Block(BlockType block_type);
    ~Block() = default;
    BlockType block_type;
};