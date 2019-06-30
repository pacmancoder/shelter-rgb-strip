#include <hal/device.hpp>

#include "private/module_initializers.hpp"

using namespace Unicorn::Hal;

Device& Device::GetInstance()
{
    static Device device;
    return device;
}

void Device::Init()
{
    InitializeNvsFlash();
    rng_ = std::make_shared<Rng>();
    rgbStrip_ = std::make_shared<RGBStrip>();
    // Tcp stack should be initialized before event loop was started
    // [According to esp-idf samples]
    InitializeTcpIpStack();
    eventManager_ = std::make_shared<EventManager>();
    wifi_ = std::make_shared<Wifi>();
}

std::shared_ptr<RGBStrip> Device::GetRgbStrip() const
{
    return rgbStrip_;
}

std::shared_ptr<Rng> Device::GetRng() const
{
    return rng_;
}

std::shared_ptr<EventManager> Device::GetEventManager() const
{
    return eventManager_;
}

std::shared_ptr<Wifi> Device::GetWifi() const
{
    return wifi_;
}
