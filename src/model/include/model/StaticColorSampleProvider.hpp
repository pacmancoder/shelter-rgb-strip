#pragma once

#include <model/IColorSampleProvider.hpp>

namespace Model
{
    /// Represents color sample provider which always produces the same color
    class StaticColorSampleProvider : IColorSampleProvider
    {
    public:
        /// Constructs new StaticColorSampleProvider instance
        explicit StaticColorSampleProvider(ColorSample sample);

    public:
        ColorSamplingResult NextSample() override;
        void Process(unsigned int deltaMs) override;

    public:
        /// Changes target sample to render
        void SetSample(ColorSample sample);

    private:
        ColorSample sample_;
    };
}