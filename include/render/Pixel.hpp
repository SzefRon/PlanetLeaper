#pragma once

#include "render/Colors.hpp"

struct Pixel
{
    Pixel() = default;
    Pixel(char ch, char *color)
        : ch(ch), color(color) {}
    char ch;
    const char *color;
};