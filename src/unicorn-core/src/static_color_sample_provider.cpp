#include <core/static_color_sample_provider.hpp>

using namespace Unicorn::Model;
using namespace Unicorn::Core;

StaticColorSampleProvider::StaticColorSampleProvider(ColorSample sample)
    : sample_(sample) {}

IColorSampleProvider::SamplingResult StaticColorSampleProvider::NextSample()
{
    return SamplingResult::make_some(sample_);
}

void StaticColorSampleProvider::Process(uint32_t deltaMs) {}

void StaticColorSampleProvider::SetSample(ColorSample sample)
{
    sample = sample_;
}
