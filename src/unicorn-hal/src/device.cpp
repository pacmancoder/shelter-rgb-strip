#include <hal/device.hpp>

using namespace Unicorn::Hal;

Device& Device::GetInstance()
{
    static Device device;
    return device;
}

void Device::Init()
{
    rgbStrip_ = std::make_shared<RGBStrip>();
    rng_ = std::make_shared<Rng>();
}

std::shared_ptr<RGBStrip> Device::GetRgbStrip() const
{
    return rgbStrip_;
}

std::shared_ptr<Rng> Device::GetRng() const
{
    return rng_;
}
