#pragma once

#include <cstdint>

namespace Colors
{
    enum class RgbModel
    {
        Bit24
    };

    template <RgbModel model>
    struct Rgb {};

    struct Rgb<RgbModel::Int24Bit>
    {
        uin32_t r, g, b;
    };

    using Rgb24 = Rgb<uint8_t>;
}