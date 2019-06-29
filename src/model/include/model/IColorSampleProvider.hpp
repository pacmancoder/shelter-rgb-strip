#pragma once

#include <exl/option.hpp>

#include <colors/ColorModels.hpp>

namespace Model
{
    using ColorSample = Colors::RgbInt24Bit;
    using ColorSamplingResult = exl::option<ColorSample>;

    /// Provides color sample on request
    class IColorSampleProvider
    {
    public:
        /// Returns current color sample
        virtual ColorSamplingResult NextSample() = 0;
        /// Performs generator processing actions
        virtual void Process(unsigned int deltaMs) = 0;

    public:
        ~IColorSampleProvider() = default;
    };
}