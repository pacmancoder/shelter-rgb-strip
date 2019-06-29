#pragma once

#include <model/color_sample_provider.hpp>

namespace Unicorn { namespace Core
{
    /// Represents color sample provider which always produces the same color
    class StaticColorSampleProvider : public Model::IColorSampleProvider
    {
    public:
        /// Constructs new StaticColorSampleProvider instance
        explicit StaticColorSampleProvider(ColorSample sample);

    public:
        SamplingResult NextSample() override;
        void Process(uint32_t deltaMs) override;

    public:
        /// Changes target sample to render
        void SetSample(ColorSample sample);

    private:
        ColorSample sample_;
    };
}}