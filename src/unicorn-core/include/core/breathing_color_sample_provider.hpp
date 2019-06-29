#pragma once

#include <model/color_sample_provider.hpp>

namespace Unicorn { namespace Core
{
    class BreathingColorSampleProvider : public Model::IColorSampleProvider
    {
    public:
        explicit BreathingColorSampleProvider(float speed, ColorSample color);

    public:
        SamplingResult NextSample() override;
        void Process(uint32_t deltaMs) override;

    public:
        void SetSpeed(float speed);
        void SetColor(ColorSample color);

    private:
        uint32_t step_;
        float speed_;
        ColorSample color_;
    };
}}