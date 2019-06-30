#pragma once

#include <memory>

#include <hal/rng.hpp>
#include <hal/rgb_strip.hpp>
#include <hal/event_manager.hpp>
#include <hal/wifi.hpp>

namespace Unicorn { namespace Hal
{
    class Device
    {
    public:
        static Device& GetInstance();

    public:
        void Init();

        std::shared_ptr<Rng> GetRng() const;
        std::shared_ptr<RGBStrip> GetRgbStrip() const;
        std::shared_ptr<EventManager> GetEventManager() const;
        std::shared_ptr<Wifi> GetWifi() const;

    private:
        std::shared_ptr<Rng> rng_;
        std::shared_ptr<RGBStrip> rgbStrip_;
        std::shared_ptr<EventManager> eventManager_;
        std::shared_ptr<Wifi> wifi_;
    };
}}