#pragma once

#include <memory>

#include <unithread/mutex.hpp>

#include <model/color_sample_provider.hpp>

namespace Unicorn { namespace Core
{
    class SharedColorSampleProvider : public Model::IColorSampleProvider
    {
    public:
        using ColorSampleProviderPtr = std::shared_ptr<Model::IColorSampleProvider>;

    public:
        void SubstituteOriginal(ColorSampleProviderPtr newOriginal);

    private:
        SamplingResult NextSample() override;
        void Process(unsigned int deltaMs) override;

    private:
        std::shared_ptr<Model::IColorSampleProvider> original_;
        Unithread::Mutex interactionMutex_;
    };
}}