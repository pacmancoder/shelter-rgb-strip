#include <model/StaticColorSampleProvider.hpp>

using namespace Model;

StaticColorSampleProvider::StaticColorSampleProvider(ColorSample sample)
    : sample_(sample) {}

ColorSamplingResult StaticColorSampleProvider::NextSample()
{
    return sample_;
}

void StaticColorSampleProvider::SetSample(ColorSample sample)
{
    sample = sample_;
}

void StaticColorSampleProvider::Process(unsigned int deltaMs) {}
