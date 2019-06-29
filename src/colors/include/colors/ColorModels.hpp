#pragma once

#include <cstdint>

namespace Colors
{
    // >>> COLOR MODEL VARIANTS

    enum class RgbVariant
    {
        // 8 bit per channel (0 .. 255)
        Int24Bit,
        // Normalized float value per channel (0 .. 1.0)
        FloatNormalized
    };

    enum class HsvVariant
    {
        // Normalized float value per channel (0 .. 1.0)
        FloatNormalized
    };

    // >>> COLOR MODELS <<<

    template <RgbVariant>
    struct Rgb {};

    template<HsvVariant>
    struct Hsv {};

    // >>> SPECIALIZATIONS <<<

    template<>
    struct Rgb<RgbVariant::Int24Bit>
    {
        uint8_t r, g, b;
    };

    template<>
    struct Rgb<RgbVariant::FloatNormalized>
    {
        float r, g, b;
    };

    template<>
    struct Hsv<HsvVariant::FloatNormalized>
    {
        float h, s, v;
    };

    // >>> ALIASES <<<

    using RgbInt24Bit = Rgb<RgbVariant::Int24Bit>;
    using RgbFloatNormalized = Rgb<RgbVariant::FloatNormalized>;

    using HsvFloatNormalized = Hsv<HsvVariant::FloatNormalized>;

    // >>> Operations <<<

    template<typename Target, typename Source>
    Target convert(Source source);

    template<>
    RgbFloatNormalized convert(HsvFloatNormalized source);

    template<>
    RgbInt24Bit convert(HsvFloatNormalized source);

    template<>
    RgbInt24Bit convert(RgbFloatNormalized source);
}