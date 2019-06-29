#include <core/shared_color_sample_provider.hpp>

using namespace Unicorn::Core;
using namespace Unicorn::Model;

SharedColorSampleProvider::SamplingResult SharedColorSampleProvider::NextSample()
{
    if (!original_)
    {
        return SamplingResult::make_none();
    }

    auto lock = interactionMutex_.ScopedLock();

    return original_->NextSample();
}

void SharedColorSampleProvider::Process(uint32_t deltaMs)
{
    if (!original_)
    {
        return;
    }

    auto lock = interactionMutex_.ScopedLock();

    original_->Process(deltaMs);
}

void SharedColorSampleProvider::SubstituteOriginal(ColorSampleProviderPtr newOriginal)
{
    auto lock = interactionMutex_.ScopedLock();

    original_ = std::move(newOriginal);
}
