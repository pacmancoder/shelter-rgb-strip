#pragma once

#include <cstdint>

namespace Unicorn { namespace Hal
{
    class Rng
    {
    public:
        using result_type = uint32_t;

        static result_type min();
        static result_type max();

        result_type operator()();
    };
}}