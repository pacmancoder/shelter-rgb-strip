#include <colors/ColorModels.hpp>

using namespace Colors;

Rgb<RgbVariant::FloatNormalized>::operator Rgb<RgbVariant::Int24Bit>()
{
    return
    {
        static_cast<uint8_t>(r * 255),
        static_cast<uint8_t>(g * 255),
        static_cast<uint8_t>(b * 255)
    };
}


Hsv<HsvVariant::FloatNormalized>::operator Rgb<RgbVariant::FloatNormalized>()
{
    auto fSector = h * 6;
    if (fSector >= 6)
    {
        fSector = 0;
    }

    auto iSector = static_cast<int>(fSector);

    auto sectorPos = fSector - iSector;

    float p = v * (1.0f - s);
    float q = v * (1.0f - (s * sectorPos));
    float t = v * (1.0f - (s * (1.0f - sectorPos)));

    switch(iSector)
    {
        case 0: return { v, t, p };
        case 1: return { q, v, p };
        case 2: return { p, v, t };
        case 3: return { p, q, v };
        case 4: return { t, p, v };
        default: break;
    }

    return { v, p, q };
}

Hsv<HsvVariant::FloatNormalized>::operator Rgb<RgbVariant::Int24Bit>()
{
    return static_cast<RgbInt24Bit>(static_cast<RgbFloatNormalized>(*this));
}
