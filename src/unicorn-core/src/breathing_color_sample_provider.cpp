#include <core/breathing_color_sample_provider.hpp>

#include <cmath>

using namespace Unicorn::Core;
using namespace Unicorn::Model;

namespace
{
    constexpr double PI = 3.14159265358979323846;
    constexpr double SIN_PERIOD = PI * 2;
}

BreathingColorSampleProvider::BreathingColorSampleProvider(
    float speed,
    BreathingColorSampleProvider::ColorSample color
)
    : step_(0)
    , speed_(speed)
    , color_(color) {}

BreathingColorSampleProvider::SamplingResult BreathingColorSampleProvider::NextSample()
{
    auto subStep = (step_ % 1000) / 1000.0;
    auto multiplier = (std::sin(subStep * SIN_PERIOD) + 1) / 2;

    return Colors::RgbInt24Bit {
        static_cast<uint8_t>(color_.r * multiplier),
        static_cast<uint8_t>(color_.g * multiplier),
        static_cast<uint8_t>(color_.b * multiplier)
    };
}

void BreathingColorSampleProvider::Process(uint32_t deltaMs)
{
    step_ += static_cast<uint32_t>(deltaMs * speed_);
}

void BreathingColorSampleProvider::SetSpeed(float speed)
{
    speed_ = speed;
}

void BreathingColorSampleProvider::SetColor(BreathingColorSampleProvider::ColorSample color)
{
    color_ = color;
}
