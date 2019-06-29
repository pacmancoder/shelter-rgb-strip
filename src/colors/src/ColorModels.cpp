#include <colors/ColorModels.hpp>

using namespace Colors;

template<>
RgbInt24Bit Colors::convert(RgbFloatNormalized source)
{
    return
    {
            static_cast<uint8_t>(source.r * 255),
            static_cast<uint8_t>(source.g * 255),
            static_cast<uint8_t>(source.b * 255)
    };
}

template<>
RgbFloatNormalized Colors::convert(HsvFloatNormalized source)
{
    auto fSector = source.h * 6;
    if (fSector >= 6)
    {
        fSector = 0;
    }

    auto iSector = static_cast<int>(fSector);

    auto sectorPos = fSector - iSector;

    float p = source.v * (1.0f - source.s);
    float q = source.v * (1.0f - (source.s * sectorPos));
    float t = source.v * (1.0f - (source.s * (1.0f - sectorPos)));

    switch(iSector)
    {
        case 0: return { source.v, t, p };
        case 1: return { q, source.v, p };
        case 2: return { p, source.v, t };
        case 3: return { p, q, source.v };
        case 4: return { t, p, source.v };
        default: break;
    }

    return { source.v, p, q };
}

template<>
RgbInt24Bit Colors::convert(HsvFloatNormalized source)
{
    return convert<RgbInt24Bit>(convert<RgbFloatNormalized>(source));
}