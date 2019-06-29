#pragma once

#include <model/color_sample_provider.hpp>

namespace Unicorn { namespace Core
{
    class SpectrumColorSampleProvider : public Model::IColorSampleProvider
    {
    public:
        explicit SpectrumColorSampleProvider(float speed);

    public:
        SamplingResult NextSample() override;
        void Process(uint32_t deltaMs) override;

    public:
        void SetSpeed(float speed);

    private:
        uint32_t step_;
        float speed_;
    };
}}