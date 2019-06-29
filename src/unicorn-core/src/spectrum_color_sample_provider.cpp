#include <core/spectrum_color_sample_provider.hpp>

using namespace Unicorn::Model;
using namespace Unicorn::Core;

SpectrumColorSampleProvider::SpectrumColorSampleProvider(float speed)
    : step_(0)
    , speed_(speed) {}

SpectrumColorSampleProvider::SamplingResult SpectrumColorSampleProvider::NextSample()
{
    return Colors::convert<Colors::RgbInt24Bit>(
        Colors::HsvFloatNormalized{ float(step_ % 1000) / 1000.f, 1.0, 1.0 }
    );
}

void SpectrumColorSampleProvider::Process(uint32_t deltaMs)
{
    step_ += static_cast<uint32_t>(deltaMs * speed_);
}

void SpectrumColorSampleProvider::SetSpeed(float speed)
{
    speed_ = speed;
}
