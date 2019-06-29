#pragma once

#include <cstdint>

namespace Unicorn { namespace Hal
{
    class RGBStrip
    {
    public:
        RGBStrip();

    public:
        void ChangeColor(uint8_t r, uint8_t g, uint8_t b);
    };
}}