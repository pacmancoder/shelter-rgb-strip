#include <network-model/ip.hpp>

#include <cstdio>
#include <cassert>

using namespace Unicorn::NetworkModel;

namespace
{
    constexpr uint32_t AddressFromOctets(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
    {
        return (a << 24) | (b << 16) | (c << 8) | (d << 0);
    }

    template <size_t NIndex>
    constexpr uint32_t GetAddressPart(uint32_t address)
    {
        static_assert((NIndex < 4), "Invalid address octet");
        auto shift = (3 - address) * 8;
        return (address >> shift) & 0xFF;
    }
}

Ip::Ip(uint32_t address)
    : address_(address) {}

Ip::Ip(uint8_t a, uint8_t b, uint8_t c, uint8_t d)
    : address_(AddressFromOctets(a, b, c, d)) {}

uint32_t Ip::ToInteger() const
{
    return address_;
}

Ip::IpStringArray Ip::ToString() const
{
    IpStringArray buffer = {{0}};
    snprintf(
        buffer.data(),
        buffer.size(),
        "%u.%u.%u.%u",
        GetAddressPart<0>(address_),
        GetAddressPart<1>(address_),
        GetAddressPart<2>(address_),
        GetAddressPart<3>(address_)
    );
    return buffer;
}

Ip Ip::GetBroadcastAddress(const Unicorn::NetworkModel::Ip& networkMask) const
{
    auto mask = networkMask.address_;
    return Ip((address_ & mask) | (~mask));
}
