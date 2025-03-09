#pragma once

#include <unordered_map>

#include "world/BlockType.hpp"
#include "render/Colors.hpp"

namespace Render
{

const std::unordered_map<BlockType, std::pair<char, const char*>> block_render_details =
{
    {AIR, {' ', Colors::Empty}},
    {STONE, {'#', Colors::Gray}},
    {DIRT, {'@', Colors::Brown}},
    {GRASS, {'%', Colors::Green}},
    {CORE, {(char)(219), Colors::Red}},
    {PLAYER, {(char)(219), Colors::White}}
};

}