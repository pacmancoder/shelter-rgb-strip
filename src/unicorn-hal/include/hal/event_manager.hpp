#pragma once

#include <memory>
#include <functional>
#include <cstdint>

#include <network-model/ip.hpp>

namespace Unicorn { namespace Hal
{
    class EventManager
    {
    public:
        using UserContext = void*;

    public:
        using EventHandle = size_t;

    public:
        // Note: Reason with index not listed in this enumeration can be generated.
        enum class WifiDisconnectReason : uint8_t
        {
            BasicRateNotSupported = 205 // Hint for switch to b/g/n
        };

        struct WifiStaStartContext {};

        struct WifiStaGotIpContext
        {
            NetworkModel::Ip ip;
            NetworkModel::Ip networkMask;
        };

        struct WifiStaDisconnectedContext
        {
            WifiDisconnectReason reason;
        };

        struct WifiApStartContext {};

    public:
        template <typename T>
        using Fn = std::function<T>;

        using WifiStaStartCallback = Fn<void(WifiStaStartContext, UserContext)>;
        using WifiStaGotIpCallback = Fn<void(WifiStaGotIpContext, UserContext)>;
        using WifiStaDisconnectedCallback = Fn<void(WifiStaDisconnectedContext, UserContext)>;

        using WifiApStartCallback = Fn<void(WifiApStartContext, UserContext)>;

    public:
        EventManager();
        ~EventManager();

    public:
        EventHandle RegisterWifiStaStartEvent(WifiStaStartCallback&&, UserContext);
        EventHandle RegisterWifiStaGotIp(WifiStaGotIpCallback&&, UserContext);
        EventHandle RegisterWifiStaDisconnect(WifiStaDisconnectedCallback&&, UserContext);

        EventHandle RegisterWifiApStart(WifiApStartCallback&&, UserContext);

        void UnregisterEvent(EventHandle);

    private:
        struct Impl;

    private:
        std::unique_ptr<Impl> impl_;
    };
}}