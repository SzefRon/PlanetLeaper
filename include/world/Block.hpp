#pragma once

#include "glm/glm.hpp"

#include "world/BlockType.hpp"

struct Block
{
public:
    Block() = default;
    ~Block() = default;
    BlockType block_type;
};