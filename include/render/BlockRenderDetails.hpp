#pragma once

#include <unordered_map>

#include "world/BlockType.hpp"
#include "render/Colors.hpp"

namespace Render
{

const std::unordered_map<BlockType, std::pair<char, const char*>> block_render_details =
{
    {STONE, {'#', Colors::Gray}},
    {DIRT, {'@', Colors::Brown}},
    {AIR, {' ', Colors::Empty}}
};

}