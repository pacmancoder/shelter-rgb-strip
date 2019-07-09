#pragma once

#include <shelter-utils/ssid_device_descriptor.hpp>

namespace Unicorn { namespace Hal
{
    class Wifi
    {
    public:
        Wifi();

    public:
        void StartOpenAp(Shelter::Utils::Ssid ssid);
    };
}}