#pragma once

#include <memory>

#include <hal/rng.hpp>
#include <hal/rgb_strip.hpp>

namespace Unicorn { namespace Hal
{
    class Device
    {
    public:
        static Device& GetInstance();

    public:
        void Init();

        std::shared_ptr<RGBStrip> GetRgbStrip() const;
        std::shared_ptr<Rng> GetRng() const;

    private:
        std::shared_ptr<Rng> rng_;
        std::shared_ptr<RGBStrip> rgbStrip_;
    };
}}