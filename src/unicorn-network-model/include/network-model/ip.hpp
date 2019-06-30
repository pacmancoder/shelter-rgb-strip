#pragma once

#include <cstdint>
#include <array>

namespace Unicorn { namespace NetworkModel
{
    class Ip
    {
    public:
        static constexpr size_t MAX_IP_STRING_SIZE = 16;

    public:
        using IpStringArray = std::array<char, MAX_IP_STRING_SIZE>;

    public:
        explicit Ip(uint32_t address);
        Ip(uint8_t a, uint8_t b, uint8_t c, uint8_t d);

    public:
        uint32_t ToInteger() const;
        IpStringArray ToString() const;

    public:
        Ip GetBroadcastAddress(const Ip& networkMask) const;

    private:
        uint32_t address_;
    };
}}