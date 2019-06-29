#pragma once

#include <memory>
#include <cstdint>

#include <exl/option.hpp>

#include <colors/ColorModels.hpp>

#include <model/error.hpp>

namespace Unicorn { namespace Model
{
    /// Provides color sample on request
    class IColorSampleProvider
    {
    public:
        using ColorSample = Colors::RgbInt24Bit;
        using SamplingResult = exl::option<ColorSample>;

    public:
        /// Returns current color sample
        virtual SamplingResult NextSample() = 0;
        /// Performs generator processing actions
        virtual void Process(uint32_t deltaMs) = 0;

    public:
        virtual ~IColorSampleProvider() = default;
    };
}}